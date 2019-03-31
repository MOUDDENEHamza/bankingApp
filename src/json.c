#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"

/*
 * Add data client to json file
 */
struct json_object *add_client_json(Client new_client, struct json_object *clients) {
        struct json_object *client;
	client = json_object_new_object();
        json_object_object_add(client, "ID", json_object_new_string(get_id(new_client)));
        json_object_object_add(client, "PASSWD", json_object_new_string(get_passwd(new_client)));
        json_object_object_add(client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(new_client))));
        json_object_object_add(client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(new_client))));
        json_object_object_add(client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(new_client))));
        json_object_object_add(client, "EMAIL", json_object_new_string(get_mail(get_coordinates(get_perso_info(new_client)))));
        json_object_object_add(client, "PHONE", json_object_new_string(get_phone(get_coordinates(get_perso_info(new_client)))));
	json_object_array_add(clients, client);
	printf("%s\n", json_object_get_string(clients));
	return clients;
}

/*
 * Parse the json file containing the client data
 */
struct json_object *parse_json(void) {
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *clients;
	struct json_object *client;
	size_t n_clients;
	size_t i;	
	long fsize = 0;
	if (!(fp = fopen("data/account_list.json", "r"))){//Check if the file exist
                if(fp != NULL) {
                        fseek(fp, 0, SEEK_END);
                        fsize= ftell(fp);
                        if (fsize == 0) {//Check if the file is empty
                                return NULL;
			}
        	}
	}
	fread(buffer, 1024, 1, fp);
	fclose(fp);
	parsed_json = json_tokener_parse(buffer);
	json_object_object_get_ex(parsed_json, "clients", &clients);
	n_clients = json_object_array_length(clients);
	printf("Found %lu friends\n",n_clients);
	for(i = 0;i < n_clients; i++) {
		client = json_object_array_get_idx(clients, i);
		printf("%s\n", json_object_get_string(client));
	}
	printf("%s\n", json_object_get_string(clients));
	printf("%s\n", json_object_get_string(parsed_json));
	return clients;
}
