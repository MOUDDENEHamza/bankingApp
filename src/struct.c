#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<json-c/json.h>
#include "struct.h"

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the menu
 */
struct symbol{
	int flag;
    	int exit;
	int index;
}symbol;

/*-------------Constructor------------*/

/*
 * Constructor of symbol structure
 */
Symbol new_symbol(void) {
        Symbol s = (Symbol) malloc(sizeof(Symbol));
        s->flag = 0;
        s->exit = 1;
        s->index = 0;
        return s;
}

/*---------------Getters--------------*/

/*
 *Get flag value from the structure
 */
int get_flag(Symbol s) {
	return s->flag;
}

/*
 *Get exit value from the structure
 */
int get_exit(Symbol s) {
	return s->exit;
}

/*
 *Get index value from the structure
 */
int get_index(Symbol s) {
	return s->index;
}

/*---------------Setters--------------*/

/*
 *Set value to flag in structure
 */
void set_flag(Symbol s ,int *val) {
	s->flag = *val;
}

/*
 *Set value to exit in structure
 */
void set_exit(Symbol s ,int *val) {
	s->exit = *val;
}

/*
 *Set value to index in structure
 */
void set_index(Symbol s, int *val) {
	s->index = *val;
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the connexion feature
 */
struct security{
        char *id;
        char *passwd;
};

/*-------------Constructor------------*/

/*
 * Constructor of the structure
 */
Security new_security(void) {
        Security p = (Security) malloc(sizeof(Security));
        p->id = malloc(sizeof(char *));
        p->passwd = malloc(sizeof(char *));
        strcpy(p->id, "");
        strcpy(p->passwd, "");
        return p;
}


/*---------------Getters--------------*/

/*
 *Get id value from the structure
 */
char* get_id(Security p) {
        return p->id;
}

/*
 *Get exit value from the structure
 */
char* get_passwd(Security p) {
        return p->passwd;
}

/*---------------Setters--------------*/

/*
 *Set value to id in structure
 */
void set_id(Security p ,char *id) {
        strcpy(p->id, id);
}

/*
 *Set value to passwd in structure
 */
void set_passwd(Security p ,char *passwd) {
        strcpy(p->passwd, passwd);
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structures-------------------------------*/

/*
 * Introduce a simple structre handling the json file
 */
struct json {
	char *id;
	char *passwd;
};

/*-------------Constructor------------*/

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
