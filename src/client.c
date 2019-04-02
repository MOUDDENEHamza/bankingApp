#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
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
    struct json_object *json_client, *json_id, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
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

    if (amount_transfer <= get_balance(get_account(client)) && amount_transfer > 0) {
        printf("1\n");
        n_clients = json_object_array_length(json_clients);

        for (i = 0; i < n_clients; i++) {
            printf("2\n");
            json_client = json_object_array_get_idx(json_clients, i);
            json_object_object_get_ex(json_client, "ID", &json_id);

            if (strcmp(id, json_object_get_string(json_id)) == 0 && strcmp(get_id(client), id) != 0) {
                printf("3\n");
                new_balance = get_balance(get_account(client)) - amount_transfer;
                set_balance(get_account(client), &new_balance);
                json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
                n_accounts = json_object_array_length(json_account_list);

                for (j = 0; j < n_accounts; j++) {
                    printf("4\n");
                    json_account = json_object_array_get_idx(json_account_list, i);
                    printf("4.1\n");
                    json_object_object_get_ex(json_account, "TYPE", &json_type);
                    printf("4.2\n");
                    json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                    printf("4.3\n");
                    if (strcmp(type, json_object_get_string(json_type)) == 0 &&
                        strcmp(entitled, json_object_get_string(json_entitled)) == 0) {
                        printf("5\n");
                        json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                        recipient_balance = json_object_get_double(json_balance) + amount_transfer;
                        set_balance(get_account(client), &recipient_balance);
                        printf("\nTransfer done with success\n");
                    }
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
void pay_by_card(Client client) {
    float product_price;

    printf("\nSecure payment\n");
    printf("\nEnter the price of the product : ");
    scanf("%f", &product_price);
    if (product_price <= get_balance(get_account(client))) {
        printf("\nPayment done\n");
        return;
    }
    printf("\nyour balance is insufficient to perform this operation\n");
}
