#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

void main() {
	/*FILE *fp;
	struct json_object *my_object, *clients;
	struct json_object *client, *new_client;
	
	my_object = json_object_new_object();
	
	clients = json_object_new_array();

	new_client = json_object_new_object();
	json_object_object_add(new_client, "ID", json_object_new_string("ID"));
	json_object_object_add(new_client, "PASSWD", json_object_new_string("PASSWD"));
	json_object_object_add(new_client, "LAST NAME", json_object_new_string("LAST NAME"));
	json_object_object_add(new_client, "FIRST NAME", json_object_new_string("FIRST NAME"));
	json_object_object_add(new_client, "BIRTHDAY", json_object_new_string("BIRTHDAY"));
	json_object_array_add(clients, new_client);
	json_object_object_add(my_object, "clients", clients);
	printf("%s\n", json_object_to_json_string(my_object));
	
	fp = fopen("data/account_list.json","w");
	fwrite(json_object_to_json_string(my_object), 1, strlen(json_object_to_json_string(my_object)), fp);
        fclose(fp);
	*/
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *clients;
	struct json_object *client;
	size_t n_clients;
	size_t i;	
	fp = fopen("data/account_list.json","r");
	long fsize = 0;
        if (!(fp = fopen("data/account_list.json", "r"))){//Check if the file exist
                if(fp != NULL) {
                        fseek(fp, 0, SEEK_END);
                        fsize= ftell(fp);
                        if (fsize == 0) {//Check if the file is empty
                                return;
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
}
