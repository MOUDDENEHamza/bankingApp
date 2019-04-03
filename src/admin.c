#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "admin.h"
#include "struct.h"
#include "displayShell.h"
#include "input.h"

#define SIZE 64

/**
 * Add new client to the bank
 */
void add_client(Client client) {
    FILE *fp;
    char *str = (char *) malloc(SIZE);

    input_perso_info(client);

    strcpy(str, "data/");
    strcat(str, get_id(client));
    strcat(str, ".csv");
    fp = fopen(str, "a+");
    fprintf(fp, "DATE, OPERATION, AMOUNT, BALANCE\n");
    fclose(fp);

    printf("\nClient has been added. Restart the APP.\n");
}

/**
 * Create a new account to a given client
 */
void create_account(Client client, Json_object json_clients) {
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
}
