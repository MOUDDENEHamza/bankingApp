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
 * Create a new account to a given client
 */
void admin_create_account(Json_object json_clients) {
    int i, j, choice;
    float init_balance = 0;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object temp_json_account = json_object_new_object(), temp_entitled = json_object_new_array();
    size_t n_clients, n_accounts;

    display_creation_account();
    input_id(id);
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
        if (strcmp(id, json_object_get_string(json_id)) == 0) {
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
Json_object admin_delete_account(Json_object json_clients) {
    int i, j, choice;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_passwd, last_name, first_name, birthday, mail, phone;
    Json_object json_account_list, json_account, json_type, json_entitled, json_balance;
    Json_object json_temp_clients = json_object_new_array();
    Json_object json_temp_client = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array();
    Json_object json_temp_account = json_object_new_object();
    Json_object json_temp_entitled = json_object_new_array();
    Json_object temp_entitled = json_object_new_array();
    size_t n_clients, n_accounts;

    display_deletion_account();
    input_id(id);
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
        json_object_object_get_ex(json_client, "PASSWD", &json_passwd);
        json_object_object_get_ex(json_client, "LAST NAME", &last_name);
        json_object_object_get_ex(json_client, "FIRST NAME", &first_name);
        json_object_object_get_ex(json_client, "BIRTHDAY", &birthday);
        json_object_object_get_ex(json_client, "EMAIL", &mail);
        json_object_object_get_ex(json_client, "PHONE", &phone);
        if (strcmp(id, json_object_get_string(json_id)) == 0) {
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
    display_success_deletion_account();
    return json_temp_clients;
}

/**
 * Display the account list by type of whole client in the bank
 */
void display_account_list_by_type(Json_object json_clients) {
    int i, j, choice;
    char *type = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    size_t n_clients, n_accounts;

    display_account_type();
    choice = input_choice();
    strcpy(type, input_type(&choice));
    printf("\nID,\t\tTYPE,\t\tENTITLED,\t\tBALANCE\n");
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
            json_object_object_get_ex(json_account, "BALANCE", &json_balance);
            if (strcmp(type, json_object_get_string(json_type)) == 0) {
                printf("\n%s,\t%s,\t%s,\t\t%f\n", json_object_get_string(json_id), json_object_get_string(json_type),
                       json_object_get_string(json_entitled), json_object_get_double(json_balance));
            }
        }
    }
    display_quit_administrator_menu();
}

/**
 * Add new client to the bank
 */
void add_client(Client client) {
    FILE *fp;
    char *str = (char *) malloc(SIZE);

    display_adding_client();
    input_perso_info(client);
    strcpy(str, "data/");
    strcat(str, get_id(client));
    strcat(str, ".csv");
    fp = fopen(str, "a+");
    fprintf(fp, "DATE,\t\tOPERATION,\t\tACCOUNT,\t\tAMOUNT,\t\tBALANCE\n");
    fclose(fp);
    display_success_adding_client();
}

/**
 * Edit the coordinates of the client
 */
void edit_coordinates(Json_object json_clients) {
    int i;
    char *id = (char *) malloc(SIZE), *mail = (char *) malloc(SIZE), *phone = (char *) malloc(SIZE);
    Json_object json_client, json_id, json_last_name, json_first_name, json_birthday, json_mail, json_phone;
    size_t n_clients;

    display_editing_client();
    input_id(id);
    printf("\nEnter your new mail : ");
    scanf("%s", mail);
    printf("\nEnter your new phone : ");
    scanf("%s", phone);
    n_clients = json_object_array_length(json_clients);
    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        json_object_object_get_ex(json_client, "EMAIL", &json_mail);
        json_object_object_get_ex(json_client, "PHONE", &json_phone);
        if (strcmp(id, json_object_get_string(json_id)) == 0) {
            json_object_object_foreach(json_client, key, val)
            {
                if (strcmp(key, "EMAIL") == 0) {
                    json_object_object_add(json_client, key, json_object_new_string(mail));
                }
                if (strcmp(key, "PHONE") == 0) {
                    json_object_object_add(json_client, key, json_object_new_string(phone));
                }
            }
            display_success_editing_client();
        }
    }
}

/**
 * Display the list of entitled of a given account
 */
void display_entitled_list_account(Json_object json_clients) {
    int i, j, choice;
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled;
    size_t n_clients, n_accounts;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE);

    display_entitled_list();
    input_id(id);
    display_account_type();
    choice = input_choice();
    strcpy(type, input_type(&choice));
    printf("\nID,\t\tTYPE,\t\tENTITLED\n");
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
                strcmp(type, json_object_get_string(json_type)) == 0) {
                printf("\n%s,\t%s,\t%s\n", id, type, json_object_get_string(json_entitled));
                display_quit_administrator_menu();
            }
        }
    }
}