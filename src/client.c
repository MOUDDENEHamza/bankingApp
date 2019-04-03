#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <time.h>
#include "struct.h"

#define BUFFER 1024
#define SIZE 64

/**
 * Get fields from .csv file
 */
char *getfield(char line[], int n) {
    char *tok;

    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--n) {
            return tok;
        }
    }
    return NULL;
}

/**
 * To consult the balance of the client
 */
void consult_balance(Client client) {
    printf("\nLoading...\n");
    printf("\nThe balance of your %s is : %f\n", get_type(get_account(client)), get_balance(get_account(client)));
    printf("\nCome back the client menu\n");
}

/**
 * Get the operations list linked over a choosen period
 */
void transaction_list(void) {
    FILE *fp;
    char *line = (char *) malloc(BUFFER);

    fp = fopen("data/account_data.csv", "r");
    printf("\n\nDownload transaction file : Loading...\n\n");
    while (fgets(line, 1024, fp)) {
        char *tmp = strdup(line);
        printf(" %s,%s\n", getfield(tmp, 1), getfield(tmp, 2));
        free(tmp);
    }
    printf("\n\nCome back the client menu");
}

/**
 * Get the transfers list associated to the client
 */
void transfer_money(Client client, Json_object json_clients) {
    int i, j;
    int done = 0;
    struct json_object *json_client, *json_id, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    char *str_type = (char *) malloc(SIZE), *str_entitled = (char *) malloc(SIZE);
    float amount_transfer, recipient_balance, new_balance;
    size_t n_clients, n_accounts;

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
    int i, j;
    float product_price, new_balance;
    struct json_object *json_client, *json_id, *json_account_list, *json_account, *json_type, *json_balance;
    size_t n_clients, n_accounts;

    printf("\nSecure payment\n");
    printf("\nEnter the price of the product : ");
    scanf("%f", &product_price);

    if (product_price <= get_balance(get_account(client))) {
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
                    printf("\n%s\n", json_object_get_string(json_type));
                    if (strcmp(json_object_get_string(json_type), "CURRENT") == 0) {
                        json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                        json_object_object_foreach(json_account, key, val)
                        {

                            if (strcmp(key, "BALANCE") == 0) {
                                new_balance = json_object_get_double(json_balance) - product_price;
                                json_object_object_add(json_account, key, json_object_new_double(new_balance));
                            }
                        }
                    }
                }
            }
        }
        printf("\nPayment done\n");
        return;
    }
    printf("\nyour balance is insufficient to perform this operation\n");
}

/**
 * Make a deposit
 */
void make_deposit(Client client, Json_object json_clients) {
    FILE *fp;
    int i, j;
    char *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    struct json_object *json_client, *json_id, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    float deposit, new_balance;
    size_t n_clients, n_accounts;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fp = fopen("data/ID.csv", "a+");
    printf("\nMake the deposit to your account\n");
    printf("\nYou want to make the deposit on which account\n");
    printf("\nEnter the type of the account where you want make the deposit : ");
    scanf("%s", type);
    printf("\nEnter the entitled of the account where you want make the deposit : ");
    scanf("%s", entitled);
    printf("\nPlease, enter the amount of your deposit : ");
    scanf("%f", &deposit);

    if (deposit <= 0) {
        printf("\nError while inputting the amount pf the deposit\n");
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
                if (strcmp(json_object_get_string(json_type), type) == 0 && strcmp(json_object_get_string(json_entitled), entitled) == 0) {
                    json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                    json_object_object_foreach(json_account, key, val)
                    {

                        if (strcmp(key, "BALANCE") == 0) {
                            new_balance = json_object_get_double(json_balance) + deposit;
                            set_balance(get_account(client), &new_balance);
                            json_object_object_add(json_account, key, json_object_new_double(new_balance));
                        }
                    }
                }
            }
        }
    }
    fprintf(fp, "%d/%d/%d, DEPOSIT, %f, %f\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, deposit, get_balance(get_account(client)));
    printf("\nMake a deposit done with success\n");
    fclose(fp);
}
