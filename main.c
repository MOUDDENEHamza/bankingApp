#include<stdio.h>
#include<json-c/json.h>

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *friends;
	struct json_object *friend;
	size_t n_friends;

	size_t i;	

	fp = fopen("data/account_list.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "CLIENTS", &friends);


	n_friends = json_object_array_length(friends);
	printf("Found %lu clients\n",n_friends);

	for(i=0;i<n_friends;i++) {
		friend = json_object_array_get_idx(friends, i);
		printf("%s\n", json_object_get_string(friend));
	}
	printf("%s\n", json_object_get_string(friends));
	printf("%s\n", json_object_get_string(parsed_json));	
}
