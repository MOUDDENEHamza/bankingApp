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
void admin_create_account(Client client, Json_object json_clients) {
    int i;
    Account temp = get_account(client);
    Account new_node = new_account();
    struct json_object *json_client, *json_id, *json_account_list, *json_type, *json_entitled, *json_balance;
    Json_object json_account = json_object_new_object();
    size_t n_clients, n_accounts;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    int choice;
    float init_balance = 0;

    printf("\nCreate a new account\n");

    printf("\nEnter the ID of the client : ");
    scanf("%s", id);
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

        if (strcmp(id, json_object_get_string(json_id)) == 0) {
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);

            json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(new_node)));
            json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(new_node)));
            json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(new_node)));
            json_object_array_add(json_account_list, json_account);
            printf("\nThe account has been created with success\n");
            printf("\nCome back the administrator menu\n");
            return;
        }
    }


}

/**
 * delete a new account to a given client
 */
Json_object admin_delete_account(Client client, Json_object json_clients) {
    int i, j;
    Account temp = get_account(client);
    struct json_object *json_client, *json_id, *json_passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    Json_object json_temp_clients = json_object_new_array();
    Json_object json_temp_client = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array();
    Json_object json_temp_account = json_object_new_object();
    size_t n_clients, n_accounts;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    int choice;
    float init_balance = 0;

    printf("\nDelete an account\n");
    printf("\nEnter the ID of the client : ");
    scanf("%s", id);
    printf("\nEnter the type : ");
    scanf("%s", type);
    printf("\nEnter the entitled : ");
    scanf("%s", entitled);

    n_clients = json_object_array_length(json_clients);
    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        if (strcmp(id, json_object_get_string(json_id)) == 0) {

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
    printf("\nCome back the administrator menu\n");
    return json_temp_clients;
}

/**
 * Display the account list by type of whole client in the bank
 */
void display_account_list_by_type(Json_object json_clients) {
    int i, j;
    Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled, json_balance;
    size_t n_clients, n_accounts;
    char *type = (char *) malloc(SIZE);

    printf("\nEnter the type : ");
    scanf("%s", type);
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
                printf("\nCome back the administrator menu\n");
            }
        }
    }
}

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
    fprintf(fp, "\nDATE,\t\tOPERATION,\t\tACCOUNT,\t\tAMOUNT,\t\tBALANCE\n");
    fclose(fp);

    printf("\nClient has been added\n");
    printf("\nCome back the administrator menu\n");
}

/**
 * Edit the coordinates of the client
 */
 void edit_coordinates(Json_object json_clients) {
    int i;
    Json_object json_client, json_id, json_last_name, json_first_name, json_birthday, json_mail, json_phone;
    size_t n_clients;
    char  *id = (char *) malloc(SIZE), *mail = (char *) malloc(SIZE), *phone = (char *) malloc(SIZE);

    printf("\nEdit account\n");
    printf("\nEnter the ID of the client : ");
    scanf("%s", id);
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
            printf("\nThe account has been edited with success\n");
            printf("\nCome back the administrator menu\n");
        }
    }
 }

 /**
  * Display the list of entitled of a given account
  */
  void display_entitled_list_account(Json_object json_clients) {
     int i, j;
     Json_object json_client, json_id, json_account_list, json_account, json_type, json_entitled;
     size_t n_clients, n_accounts;
     char  *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE);

     printf("\nDisplay the entitled list of an account\n");
     printf("\nEnter the ID of the client : ");
     scanf("%s", id);
     printf("\nEnter the type : ");
     scanf("%s", type);
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
                 printf("\nCome back the administrator menu\n");
             }
         }
     }
  }