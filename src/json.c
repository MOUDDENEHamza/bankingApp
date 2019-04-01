#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"

/*
 * Update json file
 */
void write_file(Clients object, Clients clients) {
    FILE *fp;
    if (clients == NULL) {
        return;
    }
    json_object_object_add(object, "CLIENTS", clients);
    fp = fopen("data/account_list.json", "w");
    printf("%s\n", json_object_get_string(object));
    fwrite(json_object_get_string(object), strlen(json_object_get_string(object)), 1, fp);
    fclose(fp);
}

/*
 * Add data client to json file
 */
void add_client_json(Client new_client, Clients clients) {
    Json_client client = json_object_new_object();
    Json_account_list account_list= json_object_new_array();

    json_object_object_add(client, "ID", json_object_new_string(get_id(new_client)));
    json_object_object_add(client, "PASSWD", json_object_new_string(get_passwd(new_client)));
    json_object_object_add(client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(new_client))));
    json_object_object_add(client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(new_client))));
    json_object_object_add(client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(new_client))));
    json_object_object_add(client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(new_client)))));
    json_object_object_add(client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(new_client)))));
    Account a= get_account(new_client);
    while(a!=NULL){
        json_object_array_add(account_list,json_object_new_string(get_type(a)));
        a=get_nextAccount(a);
    }
    json_object_object_add(client,"LISTES_COMPTE", account_list);
    printf("%s\n", json_object_to_json_string(client));
    json_object_array_add(clients, client);
    printf("%s\n", json_object_to_json_string(clients));
}

/*
 * Parse the json file containing the client data
 */
Clients parse_json(void) {
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *clients;
    struct json_object *client;
    size_t n_clients;
    size_t i;
    fp = fopen("data/account_list.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);
    printf("Found %lu clients\n", n_clients);
    for (i = 0; i < n_clients; i++) {
        client = json_object_array_get_idx(clients, i);
        printf("%s\n", json_object_get_string(client));
    }
    printf("%s\n", json_object_get_string(clients));
    printf("%s\n", json_object_get_string(parsed_json));
    return clients;
}