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
 * Introduce a simple structre stocking the cooridnates of clients
 */
struct coordinates {
	char* mail;
    	char* phone;
    	char* address;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Coordinates new_coordinates(void){
	Coordinates c = malloc(sizeof(Coordinates));
	c->mail = malloc(sizeof(char *));
	c->phone = malloc(sizeof(char *));
	c->address = malloc(sizeof(char *));
	return c;
}

/*---------------Getters--------------*/

/*
 * Get the e-mail of client from the structure
 */
char* get_mail(Coordinates c){
    	return c->mail;
}

/*
 * Get the phone number of client from the structure
 */
char* get_phone(Coordinates c){
    	return c->phone;
}

/*
 * Get the address of client from the structure
 */
char* get_adress(Coordinates c){
    	return c->address;
}

/*--------------Setters---------------*/

/*
 * Set the mail of client into the structure
 */
void set_mail(Coordinates c, char* mail){
    	strcpy(c->mail, mail);
}

/*
 * Set the phone of client into the structure
 */
void set_phone(Coordinates c, char* phone){
    	strcpy(c->phone, phone);
}

/*
 * Set the address of client into the structure
 */
void set_address(Coordinates c, char* address){
    	strcpy(c->address, address);
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre stocking the personal information of clients
 */
struct perso_info{
    	char* last_name;
    	char* first_name;
    	char* birthday;
    	Coordinates coordinates;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Perso_info new_perso_info(void) {
	Perso_info p = malloc(sizeof(Perso_info));
        p->last_name = malloc(sizeof(char *));
        p->first_name = malloc(sizeof(char *));
        p->birthday = malloc(sizeof(char *));
        p->coordinates = new_coordinates();
	return p;
}

/*---------------Getters--------------*/

/*
 * Get the last name of client from the structure
 */
char* get_last_name(Perso_info p){
    	return p->last_name;
}

/*
 * Get the first name of client from the structure
 */
char* get_first_name(Perso_info p){
    	return p->first_name;
}

/*
 * Get the birthday of client from the structure
 */
char* get_birthday(Perso_info p){
    	return p->birthday;
}

/*
 * Get the the coordinates of client from the structure
 */
Coordinates get_coordinates(Perso_info p){
    	return p->coordinates;
}

/*--------------Setters---------------*/

/*
 * Set the last name of client into the structure
 */
void set_last_name(Perso_info p, char* last_name){
   	strcpy(p->last_name, last_name);
}

/*
 * Set the first name of client into the structure
 */
void set_first_name(Perso_info p, char* first_name) {
	strcpy(p->first_name, first_name);
}

/*
 * Set the birthday of client into the structure
 */
void set_birthday(Perso_info p, char* birthday){
    	strcpy(p->birthday, birthday);
}

/*
 *Set the the coordinates of client into the structure
 */
void set_coordinates(Perso_info p, Coordinates c) {
    	p->coordinates = c;
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling account client
 */
struct account {
   	char* type;
    	char* entitled;
	float balance;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Account new_account(void) {
	Account a = malloc(sizeof(Account));
        a->type = malloc(sizeof(char *));
        a->entitled = malloc(sizeof(char *));
        a->balance = 0;
        return a;
}

/*---------------Getters--------------*/

/*
 * Get the type of account from the structure
 */
char* get_type(Account a) {
	return a->type;
}

/*
 * Get the entitled of account from the structure
 */
char* get_entitled(Account a) {
	return a->type;
}

/*
 * Get the balance of account from the structure
 */
float get_balance(Account a) {
	return a->balance;
}

/*---------------Setters--------------*/

/*
 * Set the type of account into the structure
 */
void set_type(Account a, char* type) {
	strcpy(a->type, type);
}

/*
 * Set the entitled of account from the structure
 */
void set_entitled(Account a, char* entitled) {
	strcpy(a->entitled, entitled);
}

/*
 * Set the balance of account from the structure
 */
float set_balance(Account a, float *balance) {
	a->balance = *balance;
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling account owner
 */
struct account_owner {
    char* id;
    char* passwd;
    Perso_info perso_info;
    Account account_list;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Account_owner new_account_owner(void) {
	Account_owner ao = malloc(sizeof(Account_owner));
        ao->id = malloc(sizeof(char *));
        ao->passwd = malloc(sizeof(char *));
        ao->perso_info = new_perso_info();
	ao->account_list = new_account();
        return ao;
}

/*---------------Getters--------------*/

/*
 * Get the id of the account owner from the structure
 */
char* get_id(Account_owner ao) {
	return ao->id;
}

/*
 * Get the passwd of account owner from the structure
 */
char* get_passwd(Account_owner ao) {
	return ao->passwd;
}

/*
 * Get the personal information of account owner from the structure
 */
Perso_info get_perso_info(Account_owner ao) {
	return ao->perso_info;
}

/*
 * Get the account list of account owner from the structure
 */
Account get_account_list(Account_owner ao) {
	return ao->account_list;
}

/*---------------Setters--------------*/

/*
 * Set the id of the account owner into the structure
 */
void set_id(Account_owner ao, char *id) {
	strcpy(ao->id, id);
}

/*
 * Get the passwd of account owner into the structure
 */
void set_passwd(Account_owner ao, char *passwd) {
	strcpy(ao->passwd, passwd);
}

/*
 * Get the personal information of account owner into the structure
 */
void set_perso_info(Account_owner ao, Perso_info p) {
	ao->perso_info = p;
}

/*
 * Get the account list of account owner into the structure
 */
void set_account_list(Account_owner ao, Account a) {
	ao->account_list = a;
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
        fp = fopen("data/account_list.json","r");
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
