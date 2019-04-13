#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>
#include "struct.h"
#include "displayShell.h"
#include "input.h"

#define BUFFER 4096
#define SIZE 64
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

/**
 * To consult the balance of the client
 */
void consult_balance(Client client, Json_object json_clients) {
    int i, j, choice;
    float balance;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object temp_entitled = json_object_new_array();
    size_t n_clients, n_accounts;

    display_consulting_balance();
    display_account_type();
    choice = input_choice();
    strcpy(type, input_type(&choice));
    if (choice == 3) {
        json_object_array_add(temp_entitled, json_object_new_string(input_entitled()));
        json_object_array_add(temp_entitled, json_object_new_string(input_joint_entitled()));
        strcpy(entitled, json_object_get_string(temp_entitled));
    } else {
        strcpy(entitled, input_entitled());
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
                if (strcmp(type, json_object_get_string(json_type)) == 0 &&
                    strcmp(entitled, json_object_get_string(json_entitled)) == 0) {
                    balance = json_object_get_double(json_balance);
                    display_balance(type, &balance);
                    return;
                }
            }
        }
    }
    display_wrong_input();
}

/**
 * Get the operations list over a chosen period
 */
void transaction_list(Client client) {
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER), *str = (char *) malloc(SIZE), *period = (char *) malloc(SIZE);

    input_period(period);
    strcpy(str, "data/");
    strcat(str, get_id(client));
    strcat(str, ".csv");
    fp = fopen(str, "r");
    display_transfer_list();
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
    display_quit_client_menu();
}

/**
 * Get the transfers list associated to the client
 */
void transfer_money(Client client, Json_object json_clients) {
    FILE *fp, *FP;
    int i, j, done = 0, check = 0;
    float amount_transfer, recipient_balance, new_balance;
    char *id = (char *) malloc(SIZE), *sender_type = (char *) malloc(SIZE), *sender_entitled = (char *) malloc(
            SIZE), *recipient_type = (char *) malloc(SIZE), *recipient_entitled = (char *) malloc(SIZE),
            *str_type = (char *) malloc(SIZE), *str_entitled = (char *) malloc(SIZE), *str1 = (char *) malloc(
            SIZE), *str2 = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object temp_sender_entitled = json_object_new_array(), temp_recipient_entitled = json_object_new_array();
    size_t n_clients, n_accounts;
    Account temp = get_account(client);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nSecure transfer\n");
    printf("\nPlease, enter the type of the transmitter account : ");
    scanf("%s", sender_type);
    if (strcmp(sender_type, "JOINT") == 0) {
        printf("\nPlease, enter the entitled of the transmitter account : ");
        scanf("%s", sender_entitled);
        json_object_array_add(temp_sender_entitled, json_object_new_string(sender_entitled));
        json_object_array_add(temp_sender_entitled, json_object_new_string(input_joint_entitled()));
        strcpy(sender_entitled, json_object_get_string(temp_sender_entitled));
    } else {
        printf("\nPlease, enter the entitled of the transmitter account : ");
        scanf("%s", sender_entitled);
    }
    printf("\nPlease, enter the id of your recipient : ");
    scanf("%s", id);
    printf("\nPlease, enter the type of account of your recipient : ");
    scanf("%s", recipient_type);
    if (strcmp(recipient_type, "JOINT") == 0) {
        printf("\nPlease, enter the entitled of the transmitter account : ");
        scanf("%s", recipient_entitled);
        json_object_array_add(temp_recipient_entitled, json_object_new_string(recipient_entitled));
        json_object_array_add(temp_recipient_entitled, json_object_new_string(input_joint_entitled()));
        strcpy(recipient_entitled, json_object_get_string(temp_recipient_entitled));
    } else {
        printf("\nPlease, enter the entitled of the recipient account : ");
        scanf("%s", recipient_entitled);
    }
    printf("\nPlease, enter the amount of your transaction : ");
    scanf("%f", &amount_transfer);

    if (strcmp(get_id(client), id) == 0) {
        printf("\n"RED"FAILED : "RESET"Sorry you can't transfer money to yourself");
        printf("\nCome back the client menu\n");
        return;
    }

    traverse(temp);

    n_clients = json_object_array_length(json_clients);

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);

        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {
            check++;
        }

        if (strcmp(id, json_object_get_string(json_id)) == 0) {
            check++;
        }
    }

    if (check < 2) {
        printf("\n"RED"ERROR : "RESET"Wrong input. Please try later\n");
        printf("\nCome back the client menu\n");
        return;
    }

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
        n_accounts = json_object_array_length(json_account_list);

        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {

            while (temp != NULL) {

                for (j = 0; j < n_accounts; j++) {
                    json_account = json_object_array_get_idx(json_account_list, j);
                    json_object_object_get_ex(json_account, "TYPE", &json_type);
                    json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                    json_object_object_get_ex(json_account, "BALANCE", &json_balance);

                    if (strcmp(sender_type, get_type(temp)) == 0 &&
                        strcmp(sender_entitled, get_entitled(temp)) == 0 &&
                        strcmp(json_object_get_string(json_type), get_type(temp)) == 0 &&
                        strcmp(json_object_get_string(json_entitled), get_entitled(temp)) == 0 && done == 0) {

                        if (json_object_get_double(json_balance) < amount_transfer) {
                            printf("\n"RED"FAILED : "RESET"your balance is insufficient to perform this operation\n");
                            printf("\nCome back the client menu\n");
                            return;
                        }

                        json_object_object_foreach(json_account, key, val)
                        {

                            if (strcmp(key, "BALANCE") == 0) {
                                new_balance = get_balance(temp) - amount_transfer;
                                set_balance(temp, &new_balance);
                                json_object_object_add(json_account, key, json_object_new_double(new_balance));

                                strcpy(str1, "data/");
                                strcat(str1, get_id(client));
                                strcat(str1, ".csv");
                                fp = fopen(str1, "a+");
                                fprintf(fp, "%d/%d/%d,\t\tTRANSFER,\t\t%s,\t\t-%f,\t\t%f\n", tm.tm_mday,
                                        tm.tm_mon + 1,
                                        tm.tm_year + 1900, sender_type, amount_transfer, new_balance);
                                fclose(fp);
                                done++;
                            }
                        }
                    }
                }
                temp = get_next_account(temp);
            }
        }
    }

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
        n_accounts = json_object_array_length(json_account_list);
        if (strcmp(id, json_object_get_string(json_id)) == 0) {

            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);


                if (strcmp(recipient_type, json_object_get_string(json_type)) == 0 &&
                    strcmp(recipient_entitled, json_object_get_string(json_entitled)) == 0 && done == 1) {

                    json_object_object_foreach(json_account, key, val)
                    {
                        if (strcmp(key, "BALANCE") == 0) {
                            recipient_balance = json_object_get_double(json_balance) + amount_transfer;
                            json_object_object_add(json_account, key, json_object_new_double(recipient_balance));

                            strcpy(str2, "data/");
                            strcat(str2, json_object_get_string(json_id));
                            strcat(str2, ".csv");
                            FP = fopen(str2, "a+");
                            fprintf(FP, "%d/%d/%d,\t\tTRANSFER,\t\t%s,\t\t+%f,\t\t%f\n", tm.tm_mday, tm.tm_mon + 1,
                                    tm.tm_year + 1900, recipient_type, amount_transfer, recipient_balance);
                            fclose(FP);

                            done++;
                        }
                    }
                }
            }
        }
    }

    if (done == 2) {
        printf("\n"GREEN"DONE : "RESET"Transfer done with success\n");
        printf("\nCome back the client menu\n");
        return;
    }

    printf("\n"RED"ERROR : "RESET"The recipient data you enter is wrong. Please try later\n");
    printf("\nCome back the client menu\n");
}

/**
 * Pay by card
 */
void pay_by_card(Client client, Json_object json_clients) {
    FILE *fp;
    int i, j, choice;
    float product_price, new_balance;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE), *str = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object temp_entitled = json_object_new_array();
    size_t n_clients, n_accounts;
    Account temp = get_account(client);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nSecure payment\n");
    display_consulting_balance();
    display_account_type();
    choice = input_choice();
    strcpy(type, input_type(&choice));
    if (choice == 3) {
        json_object_array_add(temp_entitled, json_object_new_string(input_entitled()));
        json_object_array_add(temp_entitled, json_object_new_string(input_joint_entitled()));
        strcpy(entitled, json_object_get_string(temp_entitled));
    } else {
        strcpy(entitled, input_entitled());
    }

    if (strcmp(type, "SAVINGS") == 0) {
        printf("\n"RED"FAILED : "RESET"Sorry, you can not pay with your savings account\n");
        printf("\nCome back the client menu\n");
        return;
    }

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
                                printf("\n"RED"FAILED : "RESET"your balance is insufficient to perform this operation\n");
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

                                    printf("\n"GREEN"DONE : "RESET"Payment done with success\n");
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

    printf("\n"RED"ERROR : "RESET"Wrong input, please try later\n");
    printf("\nCome back the client menu\n");
}

/**
 * Make a deposit
 */
void make_deposit(Client client, Json_object json_clients) {
    FILE *fp;
    int i, j, choice;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE), *str = (char *) malloc(SIZE);
    float deposit, new_balance;
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object temp_entitled = json_object_new_array();
    size_t n_clients, n_accounts;
    Account temp = get_account(client);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\nMake the deposit to your account\n");
    display_account_type();
    choice = input_choice();
    strcpy(type, input_type(&choice));
    if (choice == 3) {
        json_object_array_add(temp_entitled, json_object_new_string(input_entitled()));
        json_object_array_add(temp_entitled, json_object_new_string(input_joint_entitled()));
        strcpy(entitled, json_object_get_string(temp_entitled));
    } else {
        strcpy(entitled, input_entitled());
    }
    printf("\nPlease, enter the amount of your deposit : ");
    scanf("%f", &deposit);

    if (deposit <= 0) {
        printf("\n"RED"ERROR : "RESET"Wrong inputting of the amount of the deposit\n");
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
                                    fprintf(fp, "%d/%d/%d,\t\tDEPOSIT,\t\t%s,\t\t+%f,\t\t%f\n", tm.tm_mday,
                                            tm.tm_mon + 1, tm.tm_year + 1900, type, deposit, get_balance(temp));
                                    fclose(fp);

                                    printf("\n"GREEN"DONE : "RESET"Make a deposit done with success\n");
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
    printf("\n"RED"FAILED : "RESET"Make a deposit failed, please try again\n");
    printf("\nCome back the client menu\n");
}

/**
 * Create a new account to a given client
 */
void client_create_account(Client client, Json_object json_clients) {
    int i, j, choice;
    float init_balance = 0;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object temp_json_account = json_object_new_object(), temp_entitled = json_object_new_array();
    Account temp = get_account(client), new_node = new_account();
    size_t n_clients, n_accounts;

    display_creation_account();
    display_account_type();
    choice = input_choice();
    strcpy(type, input_type(&choice));
    if (choice == 3) {
        json_object_array_add(temp_entitled, json_object_new_string(input_entitled()));
        json_object_array_add(temp_entitled, json_object_new_string(input_joint_entitled()));
        strcpy(entitled, json_object_get_string(temp_entitled));
    } else {
        strcpy(entitled, input_entitled());
    }
    set_type(new_node, type);
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
            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                if (strcmp(json_object_get_string(json_type), type) == 0 &&
                    strcmp(json_object_get_string(json_entitled), entitled) == 0) {
                    display_failed_creation_account();
                    return;
                }
            }
            json_object_object_add(temp_json_account, "TYPE", json_object_new_string(type));
            json_object_object_add(temp_json_account, "ENTITLED", json_object_new_string(entitled));
            json_object_object_add(temp_json_account, "BALANCE", json_object_new_double(init_balance));
            json_object_array_add(json_account_list, temp_json_account);
            display_success_creation_account();
            return;
        }
    }
}

/**
 * delete a new account to a given client
 */
Json_object client_delete_account(Client client, Json_object json_clients) {
    int i, j, choice;
    float init_balance = 0;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_passwd, last_name, first_name, birthday, mail, phone;
    Json_object json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object json_temp_clients = json_object_new_array(), json_temp_client = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array(), json_temp_account = json_object_new_object();
    Json_object temp_entitled = json_object_new_array();
    Account temp = new_account(), a = get_account(client), b = get_account(client);
    size_t n_clients, n_accounts;

    display_deletion_account();
    display_account_type();
    choice = input_choice();
    strcpy(type, input_type(&choice));
    if (choice == 3) {
        json_object_array_add(temp_entitled, json_object_new_string(input_entitled()));
        json_object_array_add(temp_entitled, json_object_new_string(input_joint_entitled()));
        strcpy(entitled, json_object_get_string(temp_entitled));
    } else {
        strcpy(entitled, input_entitled());
    }
    set_type(temp, type);
    set_entitled(temp, entitled);
    set_balance(temp, &init_balance);
    n_clients = json_object_array_length(json_clients);
    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        json_object_object_get_ex(json_client, "PASSWD", &json_passwd);
        json_object_object_get_ex(json_client, "LAST NAME", &last_name);
        json_object_object_get_ex(json_client, "FIRST NAME", &first_name);
        json_object_object_get_ex(json_client, "BIRTHDAY", &birthday);
        json_object_object_get_ex(json_client, "EMAIL", &mail);
        json_object_object_get_ex(json_client, "PHONE", &phone);
        if (strcmp(get_id(client), json_object_get_string(json_id)) == 0) {
            json_object_object_add(json_temp_client, "ID", json_id);
            json_object_object_add(json_temp_client, "PASSWD", json_passwd);
            json_object_object_add(json_temp_client, "LAST NAME", last_name);
            json_object_object_add(json_temp_client, "FIRST NAME", first_name);
            json_object_object_add(json_temp_client, "BIRTHDAY", birthday);
            json_object_object_add(json_temp_client, "EMAIL", mail);
            json_object_object_add(json_temp_client, "PHONE", phone);
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);
            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                if (strcmp(json_object_get_string(json_type), type) != 0 ||
                    strcmp(json_object_get_string(json_entitled), entitled) != 0) {
                    json_object_object_add(json_temp_account, "TYPE", json_type);
                    json_object_object_add(json_temp_account, "ENTITLED", json_entitled);
                    json_object_object_add(json_temp_account, "BALANCE", json_balance);
                    json_object_array_add(json_temp_account_list, json_temp_account);
                    json_temp_account = json_object_new_object();
                }
            }
            json_object_object_add(json_temp_client, "ACCOUNT LIST", json_temp_account_list);
            json_object_array_add(json_temp_clients, json_temp_client);
        } else {
            json_object_array_add(json_temp_clients, json_client);
        }
    }
    delete_node(get_account(client), temp);
    display_success_deletion_account();
    return json_temp_clients;
}