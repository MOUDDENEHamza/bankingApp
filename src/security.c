#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "security.h"

#define SIZE 64

/*
 * Check if the id and the password of the client is valid
 */
int valid_client(Client client, Json_object json_clients, char *id, char *passwd) {
    int i;
    int j;
    float f;
    char *str_last_name = (char *) malloc(SIZE), *str_first_name = (char *) malloc(SIZE), *str_birthday = (char *) malloc(SIZE),
    *str_mail = (char *) malloc(SIZE), *str_phone = (char *) malloc(SIZE), *str_type = (char *) malloc(SIZE), *str_entitled = (char *) malloc(SIZE);
    struct json_object *json_client, *json_account_list, *json_account, *json_id, *json_passwd, *last_name, *first_name,
            *birthday, *mail, *phone, *type, *entitled, *balance;
    size_t n_clients;
    size_t n_accounts;
    n_clients = json_object_array_length(json_clients);
    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        json_object_object_get_ex(json_client, "PASSWD", &json_passwd);
        if (strcmp(id, json_object_get_string(json_id)) == 0 &&
            strcmp(passwd, json_object_get_string(json_passwd)) == 0) {
            set_id(client, id);
            set_passwd(client, passwd);
            json_object_object_get_ex(json_client, "LAST NAME", &last_name);
            strcpy(str_last_name, json_object_get_string(last_name));
            set_last_name(get_perso_info(client), str_last_name);
            json_object_object_get_ex(json_client, "FIRST NAME", &first_name);
            strcpy(str_first_name, json_object_get_string(first_name));
            set_first_name(get_perso_info(client), str_first_name);
            json_object_object_get_ex(json_client, "BIRTHDAY", &birthday);
            strcpy(str_birthday, json_object_get_string(birthday));
            set_birthday(get_perso_info(client), str_birthday);
            json_object_object_get_ex(json_client, "EMAIL", &mail);
            strcpy(str_mail, json_object_get_string(mail));
            set_mail(get_coordinates(get_perso_info(client)), str_mail);
            json_object_object_get_ex(json_client, "PHONE", &phone);
            strcpy(str_phone, json_object_get_string(phone));
            set_phone(get_coordinates(get_perso_info(client)), str_phone);
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);
            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &type);
                strcpy(str_type, json_object_get_string(type));
                set_type(get_account(client), str_type);
                json_object_object_get_ex(json_account, "ENTITLED", &entitled);
                strcpy(str_entitled, json_object_get_string(entitled));
                set_entitled(get_account(client), str_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &balance);
                f = json_object_get_double(balance);
                set_balance(get_account(client), &f);
            }
            return 0;
        }
    }
    return 1;
}

/*
 * Allow to administrator to connect to the application
 */
int connect_admin(char *passwd) {
    if (strcmp(passwd, "admin") == 0) {
        return 0;
    }
    return 1;
}

/*
 * Change the client password
 */
void change_client_password(void);

/*
 * Change the administrator password
 */
void change_administrator_password(void) {}