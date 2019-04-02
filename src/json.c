#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"

/*
 * Update json file
 */
void write_file(Json_object json_object, Json_object json_clients) {
    FILE *fp;
    //printf("%s\n", json_object_get_string(json_clients));
    if (json_clients == NULL) {
        return;
    }
    json_object_object_add(json_object, "CLIENTS", json_clients);
    fp = fopen("data/account_list.json", "w");
    //printf("%s\n", json_object_get_string(json_object));
    fwrite(json_object_get_string(json_object), strlen(json_object_get_string(json_object)), 1, fp);
    fclose(fp);
}

/*
 * Add data client to json file
 */
void add_client_json(Client client, Json_object json_clients) {
    size_t n_account;
    Json_object json_client = json_object_new_object();
    Json_object json_account_list = json_object_new_array();
    Json_object json_account = json_object_new_object();
    json_object_object_add(json_client, "ID", json_object_new_string(get_id(client)));
    json_object_object_add(json_client, "PASSWD", json_object_new_string(get_passwd(client)));
    json_object_object_add(json_client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(client))));
    json_object_object_add(json_client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(client))));
    json_object_object_add(json_client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(client))));
    json_object_object_add(json_client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
    json_object_object_add(json_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));
    json_object_object_add(json_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));
    json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(get_account(client))));
    json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(get_account(client))));
    json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(get_account(client))));
    json_object_array_add(json_account_list, json_account);
    json_object_object_add(json_client, "ACCOUNT LIST", json_account_list);
    //printf("%s\n", json_object_to_json_string(json_client));
    json_object_array_add(json_clients, json_client);
    //printf("%s\n", json_object_to_json_string(json_clients));
}

/*
 * Parse the json file containing the client data
 */
Json_object parse_json(void) {
    FILE *fp;
    //Client new_node = client();
    char buffer[1024];
    char str_id[64], str_passwd[64], str_last_name[64], str_first_name[64], str_birthday[64], str_mail[64], str_phone[64];
    struct json_object *parsed_json;
    struct json_object *clients;
    struct json_object *client;
    struct json_object *id, *passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone;
    size_t n_clients;
    size_t i;
    fp = fopen("data/account_list.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);
    //printf("Found %lu clients\n", n_clients);
    for (i = 0; i < n_clients; i++) {
        client = json_object_array_get_idx(clients, i);
        //printf("%s\n", json_object_get_string(client));
    }
    //printf("%s\n", json_object_get_string(clients));
    //printf("%s\n", json_object_get_string(parsed_json));
    return clients;
}