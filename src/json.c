#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"

/*
 * Add data client to json file
 */
struct json_object *add_client_json(Client head, struct json_object *clients) {
	struct json_object *new_client;
        struct json_object *id, *passwd, *last_name, *first_name, *birthday, *mail, *phone;
	new_client = json_object_new_array();
	json_object_array_add(new_client, json_object_new_string(get_id(head)));
	json_object_array_add(new_client, json_object_new_string(get_passwd(head)));
	json_object_array_add(new_client, json_object_new_string(get_last_name(get_perso_info(head))));
	json_object_array_add(new_client, json_object_new_string(get_first_name(get_perso_info(head))));
	json_object_array_add(new_client, json_object_new_string(get_birthday(get_perso_info(head))));
        json_object_array_add(new_client, json_object_new_string(get_mail(get_coordinates(get_perso_info(head)))));
	json_object_array_add(new_client, json_object_new_string(get_phone(get_coordinates(get_perso_info(head)))));
	json_object_array_add(clients, new_client);
	printf("\nClients : %s\n", json_object_to_json_string(clients));
	return clients;
}

/*
 * Parse the json file containing the client data
 */
void parse_json(struct json_object *clients) {
	printf("\nDownload JSON File ...\n");
	printf("\nClients : %s\n", json_object_to_json_string(clients));
}
