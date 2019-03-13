#include <stdio.h>
#include <stdlib.h>
#include<json-c/json.h>
#include <string.h>
#include "json.h"

/*-----------------------------------Structures-------------------------------*/

/*
 * Introduce a simple structre handling the json file
 */
struct json {
	char *id;
	char *passwd;
};

/*--------------Getters---------------*/

/*
 * Get id from structure
 */
char *get_id_json(Json j) {
	return j->id;
}

/*
 * Get password from structure
 */
char* get_passwd_json(Json j) {
	return j->passwd;
}

/*------------------------------------*/

/*
 * Constructor of structure
 */
Json new_json(void) {
	FILE *fp;
	char buffer[1024];
	struct json_object *parsed_json;
	struct json_object *id, *passwd;
	
	Json j = malloc(sizeof(Json));
	j->id = malloc(sizeof(char *));
	j->id = malloc(sizeof(char *));
	j->passwd = malloc(sizeof(char *));
	fp = fopen("src/file.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);
	parsed_json = json_tokener_parse(buffer);
	json_object_object_get_ex(parsed_json, "id", &id);
	json_object_object_get_ex(parsed_json, "passwd", &passwd);
	strcpy(j->id, json_object_get_string(id));
	strcpy(j->passwd, json_object_get_string(passwd));
	return j;
}
