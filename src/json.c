#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"
#include "security.h"

#define BUFFER 4096

/**
 * Update json file
 */
void write_file(Json_object json_object, Json_object json_clients) {
    FILE *fp;
    json_object = json_object_new_object();

    if (json_clients == NULL) {
        return;
    }

    json_object_object_add(json_object, "CLIENTS", json_clients);

    fp = fopen("data/account_list.json", "w");
    fwrite(json_object_get_string(json_object), strlen(json_object_get_string(json_object)), 1, fp);
    fclose(fp);
}

/**
 * Add data client to json file
 */
void add_client_json(Client client, Json_object json_clients) {
    Account temp = get_account(client);

    Json_object json_client = json_object_new_object();
    Json_object json_account_list = json_object_new_array();
    Json_object json_account = json_object_new_object();

    json_object_object_add(json_client, "ID", json_object_new_string(get_id(client)));
    json_object_object_add(json_client, "PASSWD", json_object_new_string(encrypt_passwd(get_passwd(client))));
    json_object_object_add(json_client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(client))));
    json_object_object_add(json_client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(client))));
    json_object_object_add(json_client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(client))));
    json_object_object_add(json_client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
    json_object_object_add(json_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));

    while (temp != NULL) {
        json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(temp)));
        json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(temp)));
        json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(temp)));
        json_object_array_add(json_account_list, json_account);
        temp = get_next_account(temp);
    }

    json_object_object_add(json_client, "ACCOUNT LIST", json_account_list);
    json_object_array_add(json_clients, json_client);
}

/**
 * Parse the json file containing the client data
 */
Json_object parse_json(void) {
    FILE *fp;
    int i;
    char *buffer = (char *) malloc(BUFFER);
    Json_object parsed_json, clients, client;
    size_t n_clients;

    fp = fopen("data/account_list.json", "r");
    fread(buffer, BUFFER, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);

    for (i = 0; i < n_clients; i++) {
        client = json_object_array_get_idx(clients, i);
    }

    return clients;
}