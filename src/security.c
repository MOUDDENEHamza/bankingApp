#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "security.h"

/*
 * Check if the id and the password of the client is valid
 */
int valid_client(Clients clients, char *id, char *passwd) {
    int i;
    struct json_object *client, *json_id, *json_passwd;
    size_t n_clients;
    n_clients = json_object_array_length(clients);
    for (i = 0; i < n_clients; i++) {
        client = json_object_array_get_idx(clients, i);
        json_object_object_get_ex(client, "ID", &json_id);
        json_object_object_get_ex(client, "PASSWD", &json_passwd);
        if (strcmp(id, json_object_get_string(json_id)) == 0 &&
            strcmp(passwd, json_object_get_string(json_passwd)) == 0) {
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