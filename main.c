#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

void main() {
	char str[1024];
        clients = json_object_new_array();
	new_client = json_object_new_array();
	json_object_array_add(new_client, json_object_new_string("1"));
	json_object_array_add(new_client, json_object_new_string("2"));
	json_object_array_add(new_client, json_object_new_string("3"));
	json_object_array_add(new_client, json_object_new_string("4"));
	json_object_array_add(new_client, json_object_new_string("5"));
        json_object_array_add(new_client, json_object_new_string("6"));
	json_object_array_add(clients, new_client);
	printf("%s\n", json_object_to_json_string(clients));
	strcpy(str, json_object_to_json_string(clients));
}
