#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>
#include "struct.h"
#include "displayShell.h"

#define BUFFER 4096
#define SIZE 64

/**
 * To consult the balance of the client
 */
void consult_balance(Client client, Json_object json_clients) {
    int i, j;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    size_t n_clients, n_accounts;

    printf("\nLoading...\n");
    printf("\nEnter the type of the account you want consult the balance : ");
    scanf("%s", type);
    printf("\nEnter the entitled of the account you want consult the balance : ");
    scanf("%s", entitled);

    n_clients = json_object_array_length(json_clients);

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);

        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);

            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);

                if (strcmp(type, json_object_get_string(json_type)) == 0 &&
                    strcmp(entitled, json_object_get_string(json_entitled)) == 0) {
                    printf("\nThe balance of your %s is : %f\n", json_object_get_string(json_type),
                           json_object_get_double(json_balance));
                    return;
                }
            }
        }
    }

    printf("\nWrong input, please try later\n");
    printf("\n\nCome back the client menu\n");
}

/**
 * Get the operations list over a chosen period
 */
void transaction_list(Client client) {
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER), *str = (char *) malloc(SIZE), *period = (char *) malloc(SIZE);

    printf("\nEnter the period you want to consult your operations list (for example : 5/2019) : ");
    scanf("%s", period);
    strcpy(str, "data/");
    strcat(str, get_id(client));
    strcat(str, ".csv");
    fp = fopen(str, "r");
    printf("\nDownload transaction file : Loading...\n");

    printf("\nDATE,\t\tOPERATION,\t\tACCOUNT,\t\tAMOUNT,\t\tBALANCE\n");
    fread(buffer, 1, BUFFER, fp);
    while (buffer) {
        char *nextLine = strchr(buffer, '\n');
        if (nextLine) *nextLine = '\0';
        if (strstr(buffer, period) != NULL) {
            printf("\n%s\n", buffer);
        }
        if (nextLine) *nextLine = '\n';
        buffer = nextLine ? (nextLine + 1) : NULL;
    }

    printf("\nCome back the client menu\n");
}

/**
 * Get the transfers list associated to the client
 */
void transfer_money(Client client, Json_object json_clients) {
    FILE *fp, *FP;
    int i, j;
    int done = 0;
    struct json_object *json_client, *json_id, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    char *str_type = (char *) malloc(SIZE), *str_entitled = (char *) malloc(SIZE), *str1 = (char *) malloc(
            SIZE), *str2 = (char *) malloc(SIZE);
    float amount_transfer, recipient_balance, new_balance;
    size_t n_clients, n_accounts;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nSecure payment\n");
    printf("\nPlease, enter the id of your recipient : ");
    scanf("%s", id);
    printf("\nPlease, enter the type of account of your recipient : ");
    scanf("%s", type);
    printf("\nPlease, enter the entitled of your recipient : ");
    scanf("%s", entitled);
    printf("\nPlease, enter the amount of your transaction : ");
    scanf("%f", &amount_transfer);

    if (strcmp(get_id(client), id) == 0) {
        printf("\nSorry you can't transfer money to yourself");
        return;
    }

    if (amount_transfer <= get_balance(get_account(client)) && amount_transfer > 0) {
        n_clients = json_object_array_length(json_clients);

        for (i = 0; i < n_clients; i++) {

            json_client = json_object_array_get_idx(json_clients, i);
            json_object_object_get_ex(json_client, "ID", &json_id);
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);

            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);

                if (strcmp(id, json_object_get_string(json_id)) == 0 &&
                    strcmp(type, json_object_get_string(json_type)) == 0 &&
                    strcmp(entitled, json_object_get_string(json_entitled)) == 0) {
                    json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                    json_object_object_foreach(json_account, key, val)
                    {
                        if (strcmp(key, "BALANCE") == 0) {
                            recipient_balance = json_object_get_double(json_balance) + amount_transfer;
                            json_object_object_add(json_account, key, json_object_new_double(recipient_balance));
                            done++;

                            strcpy(str2, "data/");
                            strcat(str2, json_object_get_string(json_id));
                            strcat(str2, ".csv");
                            FP = fopen(str2, "a+");
                            fprintf(FP, "%d/%d/%d, TRANSFER, +%f, %f\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                                    amount_transfer, recipient_balance);
                            fclose(FP);
                        }
                    }
                }

                if (strcmp(get_id(client), json_object_get_string(json_id)) == 0 &&
                    strcmp("CURRENT", json_object_get_string(json_type)) == 0) {
                    json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                    json_object_object_foreach(json_account, key, val)
                    {
                        if (strcmp(key, "BALANCE") == 0) {
                            new_balance = get_balance(get_account(client)) - amount_transfer;
                            set_balance(get_account(client), &new_balance);
                            json_object_object_add(json_account, key, json_object_new_double(new_balance));
                            done++;
                        }
                    }
                }

                if (done == 2) {
                    printf("\nTransfer done with success\n");

                    strcpy(str1, "data/");
                    strcat(str1, get_id(client));
                    strcat(str1, ".csv");
                    fp = fopen(str1, "a+");
                    fprintf(fp, "%d/%d/%d,\t\tTRANSFER,\t\t-%f, %f\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                            amount_transfer, get_balance(get_account(client)));
                    fclose(fp);

                    return;
                }
            }
        }
        printf("\nThe recipient data you enter is wrong. Please try later\n");
        return;
    }
    printf("\nyour balance is insufficient to perform this operation\n");
}

/**
 * Pay by card
 */
void pay_by_card(Client client, Json_object json_clients) {
    FILE *fp;
    int i, j;
    float product_price, new_balance;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE), *str = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    size_t n_clients, n_accounts;
    Account temp = get_account(client);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nSecure payment\n");
    printf("\nPlease, enter the type of the account with what you want to pay : ");
    scanf("%s", type);

    if (strcmp(type, "SAVINGS") == 0) {
        printf("\nSorry, you can not pay with your savings account\n");
        printf("\nCome back the client menu\n");
        return;
    }

    printf("\nPlease, enter the entitled of the account with what you want to pay : ");
    scanf("%s", entitled);
    printf("\nEnter the price of the product : ");
    scanf("%f", &product_price);


    n_clients = json_object_array_length(json_clients);

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);

        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);

            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);

                if (strcmp(type, json_object_get_string(json_type)) == 0 &&
                    strcmp(entitled, json_object_get_string(json_entitled)) == 0) {

                    while (temp != NULL) {

                        if (strcmp(get_type(temp), type) == 0 && strcmp(get_entitled(temp), entitled) == 0) {

                            if (product_price > json_object_get_double(json_balance)) {
                                printf("\nyour balance is insufficient to perform this operation\n");
                                printf("\nCome back the client menu\n");
                                return;
                            }

                            json_object_object_foreach(json_account, key, val)
                            {

                                if (strcmp(key, "BALANCE") == 0) {
                                    new_balance = json_object_get_double(json_balance) - product_price;
                                    json_object_object_add(json_account, key, json_object_new_double(new_balance));
                                    set_balance(temp, &new_balance);

                                    strcpy(str, "data/");
                                    strcat(str, get_id(client));
                                    strcat(str, ".csv");
                                    fp = fopen(str, "a+");
                                    fprintf(fp, "%d/%d/%d,\t\tPAYMENT,\t\t%s,\t\t-%f,\t\t%f\n", tm.tm_mday,
                                            tm.tm_mon + 1, tm.tm_year + 1900, type, product_price, get_balance(temp));
                                    fclose(fp);

                                    printf("\nPayment done\n");
                                    printf("\nCome back the client menu\n");
                                    return;
                                }
                            }
                        }

                        temp = get_next_account(temp);
                    }
                }
            }
        }
    }

    printf("\nWrong input, please try later\n");
    printf("\nCome back the client menu\n");
}

/**
 * Make a deposit
 */
void make_deposit(Client client, Json_object json_clients) {
    FILE *fp;
    int i, j;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE), *str = (char *) malloc(SIZE);
    float deposit, new_balance;
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    size_t n_clients, n_accounts;
    Account temp = get_account(client);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nMake the deposit to your account\n");
    printf("\nYou want to make the deposit on which account\n");
    printf("\nEnter the type of the account where you want make the deposit : ");
    scanf("%s", type);
    printf("\nEnter the entitled of the account where you want make the deposit : ");
    scanf("%s", entitled);
    printf("\nPlease, enter the amount of your deposit : ");
    scanf("%f", &deposit);

    if (deposit <= 0) {
        printf("\nError while inputting the amount of the deposit\n");
        printf("\nCome back the client menu\n");
        return;
    }

    n_clients = json_object_array_length(json_clients);

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);

        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);

            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);

                if (strcmp(json_object_get_string(json_type), type) == 0 &&
                    strcmp(json_object_get_string(json_entitled), entitled) == 0) {

                    while (temp != NULL) {

                        if (strcmp(get_type(temp), type) == 0 && strcmp(get_entitled(temp), entitled) == 0) {
                            json_object_object_foreach(json_account, key, val)
                            {

                                if (strcmp(key, "BALANCE") == 0) {
                                    new_balance = json_object_get_double(json_balance) + deposit;
                                    set_balance(temp, &new_balance);
                                    json_object_object_add(json_account, key, json_object_new_double(new_balance));

                                    strcpy(str, "data/");
                                    strcat(str, get_id(client));
                                    strcat(str, ".csv");
                                    fp = fopen(str, "a+");
                                    fprintf(fp, "%d/%d/%d,\t\tDEPOSIT,\t\t%s,\t\t+%f,\t\t%f\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, type, deposit, get_balance(temp));
                                    fclose(fp);

                                    printf("\nMake a deposit done with success\n");
                                    printf("\nCome back the client menu\n");
                                    return;
                                }
                            }
                        }

                        temp = get_next_account(temp);
                    }
                }
            }
        }
    }
    printf("\nMake a deposit failed, please try again\n");
    printf("\nCome back the client menu\n");
}

/**
 * Create a new account to a given client
 */
void client_create_account(Client client, Json_object json_clients) {
    int i;
    Account temp = get_account(client);
    Account new_node = new_account();
    struct json_object *json_client, *json_id, *json_account_list, *json_type, *json_entitled, *json_balance;
    Json_object json_account = json_object_new_object();
    size_t n_clients, n_accounts;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    int choice;
    float init_balance = 0;

    printf("\nCreate a new account\n");

    display_account_type();
    printf("\nEnter your choice : ");
    scanf("%d", &choice);

    back:
    switch (choice) {
        case 1 :
            strcpy(type, "CURRENT");
            set_type(new_node, type);
            break;
        case 2 :
            strcpy(type, "SAVINGS");
            set_type(new_node, type);
            break;
        case 3 :
            strcpy(type, "JOINT");
            set_type(new_node, type);
            break;
        default :
            printf("\nWrong choice. Please try again\n");
            goto back;
    }

    printf("\nEnter the entitled : ");
    scanf("%s", entitled);
    set_entitled(new_node, entitled);

    set_balance(new_node, &init_balance);

    while (get_next_account(temp) != NULL) {
        temp = get_next_account(temp);
    }

    set_next_account(temp, new_node);

    n_clients = json_object_array_length(json_clients);

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);

        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);

            json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(new_node)));
            json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(new_node)));
            json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(new_node)));
            json_object_array_add(json_account_list, json_account);
        }
    }

    printf("\nThe account has been created with success\n");
}

/**
 * delete a new account to a given client
 */
Json_object client_delete_account(Client client, Json_object json_clients) {
    int i, j;
    Account temp = get_account(client);
    struct json_object *json_client, *json_id, *json_passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    Json_object json_temp_clients = json_object_new_array();
    Json_object json_temp_client = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array();
    Json_object json_temp_account = json_object_new_object();
    size_t n_clients, n_accounts;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    int choice;
    float init_balance = 0;

    printf("\nDelete an account\n");
    printf("\nEnter the type : ");
    scanf("%s", type);
    printf("\nEnter the entitled : ");
    scanf("%s", entitled);

    n_clients = json_object_array_length(json_clients);
    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {

            json_object_object_add(json_temp_client, "ID", json_object_new_string(get_id(client)));
            json_object_object_add(json_temp_client, "PASSWD", json_object_new_string(get_passwd(client)));
            json_object_object_add(json_temp_client, "LAST NAME",
                                   json_object_new_string(get_last_name(get_perso_info(client))));
            json_object_object_add(json_temp_client, "FIRST NAME",
                                   json_object_new_string(get_first_name(get_perso_info(client))));
            json_object_object_add(json_temp_client, "BIRTHDAY",
                                   json_object_new_string(get_birthday(get_perso_info(client))));
            json_object_object_add(json_temp_client, "EMAIL",
                                   json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
            json_object_object_add(json_temp_client, "PHONE",
                                   json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);
            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                if (strcmp(json_object_get_string(json_type), type) != 0 ||
                    strcmp(json_object_get_string(json_entitled), entitled) != 0) {

                    json_object_object_add(json_temp_account, "TYPE",
                                           json_object_new_string(json_object_get_string(json_type)));
                    json_object_object_add(json_temp_account, "ENTITLED",
                                           json_object_new_string(json_object_get_string(json_entitled)));
                    json_object_object_add(json_temp_account, "BALANCE",
                                           json_object_new_double(json_object_get_double(json_balance)));
                    json_object_array_add(json_temp_account_list, json_temp_account);
                    Json_object json_temp_account = json_object_new_object();
                }
            }
            json_object_object_add(json_temp_client, "ACCOUNT LIST", json_temp_account_list);
            json_object_array_add(json_temp_clients, json_temp_client);
        } else {
            json_object_array_add(json_temp_clients, json_client);
        }
    }

    printf("\nThe account has been deleted with success\n");
    return json_temp_clients;
}