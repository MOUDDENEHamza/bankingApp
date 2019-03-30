#include<stdio.h>
#include<json-c/json.h>

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *clients;
	struct json_object *client;
	struct json_object *id;
	size_t n_clients;

	size_t i;	

	fp = fopen("test.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "clients", &clients);
	printf("1\n");
	n_clients = json_object_array_length(clients);
	printf("Found %lu clients\n",n_clients);

	for(i=0;i<n_clients;i++) {
		client = json_object_array_get_idx(clients, i);
		printf("%s\n", json_object_get_string(client));
		for (int j = 0; j < 1; j++) {
			id = json_object_array_get_idx(client, j);
                	printf("%s\n", json_object_get_string(id));
		}
	}	
}
