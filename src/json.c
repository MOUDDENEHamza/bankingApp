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
    Json_account_list account_list = json_object_new_array();
    Account a = get_account(new_client);
    json_object_object_add(client, "ID", json_object_new_string(get_id(new_client)));
    json_object_object_add(client, "PASSWD", json_object_new_string(get_passwd(new_client)));
    json_object_object_add(client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(new_client))));
    json_object_object_add(client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(new_client))));
    json_object_object_add(client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(new_client))));
    json_object_object_add(client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(new_client)))));
    json_object_object_add(client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(new_client)))));
    while (a != NULL) {
        json_object_array_add(account_list, json_object_new_string(get_type(a)));
        a = get_nextAccount(a);
    }
    json_object_object_add(client, "ACCOUNT LIST", account_list);
    printf("%s\n", json_object_to_json_string(client));
    json_object_array_add(clients, client);
    printf("%s\n", json_object_to_json_string(clients));
}

/*
 * Parse the json file containing the client data
 */
Clients parse_json(void) {
    FILE *fp;
    //Client new_node = new_client();
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
        printf("%s\n", json_object_get_string(client));
        /*json_object_object_get_ex(client, "ID", &id);
        strcpy(str_id, json_object_get_string(id));
        set_id(new_node, str_id);
        json_object_object_get_ex(client, "PASSWD", &passwd);
        strcpy(str_passwd, json_object_get_string(passwd));
        set_passwd(new_node, str_passwd);
        json_object_object_get_ex(client, "LAST NAME", &last_name);
        strcpy(str_last_name, json_object_get_string(last_name));
        set_last_name(get_perso_info(new_node), str_last_name);
        json_object_object_get_ex(client, "FIRST NAME", &first_name);
        strcpy(str_first_name, json_object_get_string(first_name));
        set_first_name(get_perso_info(new_node), str_first_name);
        json_object_object_get_ex(client, "BIRTHDAY", &birthday);
        strcpy(str_birthday, json_object_get_string(birthday));
        set_birthday(get_perso_info(new_node), str_birthday);
        json_object_object_get_ex(client, "EMAIL", &mail);
        strcpy(str_mail, json_object_get_string(mail));
        set_mail(get_coordinates(get_perso_info(new_node)), str_mail);
        json_object_object_get_ex(client, "PHONE", &phone);
        strcpy(str_phone, json_object_get_string(phone));
        set_phone(get_coordinates(get_perso_info(new_node)), str_phone);
        append(head, new_node);
        new_node = new_client();*/
    }
    //printf("%s\n", json_object_get_string(clients));
    //printf("%s\n", json_object_get_string(parsed_json));
    return clients;
}