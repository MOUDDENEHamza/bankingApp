#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "security.h"

/*
 * Check if the id and the password of the client is valid
 */
int valid_client(Client client, Json_object json_clients, char *id, char *passwd) {
    int i;
    char str_last_name[64], str_first_name[64], str_birthday[64], str_mail[64], str_phone[64];
    struct json_object *json_client, *json_id, *json_passwd, *last_name, *first_name, *birthday, *mail, *phone;
    size_t n_clients;
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