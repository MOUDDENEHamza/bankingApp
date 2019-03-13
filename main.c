#include<stdio.h>
#include<json-c/json.h>

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *last_name, *first_name, *id, *passwd;
	
	fp = fopen("src/file.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "last_name", &last_name);
	json_object_object_get_ex(parsed_json, "first_name", &first_name);
	json_object_object_get_ex(parsed_json, "id", &id);
	json_object_object_get_ex(parsed_json, "passwd", &passwd);

	printf("Last name : %s\n", json_object_get_string(last_name));
	printf("First name : %s\n", json_object_get_string(first_name));
	printf("ID : %s\n", json_object_get_string(id));
        printf("Passwd : %s\n", json_object_get_string(passwd));
}
