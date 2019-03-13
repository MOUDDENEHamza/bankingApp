#include <stdio.h>
#include<json-c/json.h>
#include "json.h"

/*--------------Getters---------------*/

/*
 * Get last name from structure
 */
void get_last_name_json(void) {
	json_object_object_get_ex(parsed_json, "last_name", &last_name);
	printf("Last name : %s\n", json_object_get_string(last_name));
}

/*
 * Get first name from structure
 */
void get_first_name_json(void) {
	json_object_object_get_ex(parsed_json, "first_name", &first_name);
	printf("First name : %s\n", json_object_get_string(first_name));
}

/*
 * Get id from structure
 */
void get_id_json(void) {
	json_object_object_get_ex(parsed_json, "id", &id);
	printf("ID : %s\n", json_object_get_string(id));
}

/*
 * Get password from structure
 */
void get_passwd_json(void) {
	json_object_object_get_ex(parsed_json, "passwd", &passwd);
	printf("Passwd : %s\n", json_object_get_string(passwd));
}

/*------------------------------------*/

/*
 * Open the file in reading mode
 */
void open_file(char *file_name, char *buffer) {
	FILE *fp;
	fp = fopen(file_name, "r");
	fread(buffer, 1024, 1, fp);
}

/*
 * Close the file
 */
 void close_file(FILE *fp, char *buffer) {
 	fclose(fp);
	parsed_json = json_tokener_parse(buffer);
 }
