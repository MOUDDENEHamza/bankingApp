#ifndef _SETTING_H_
#define _SETTING_H_

#include "struct.h"

/*
 * Define the exit feature
 */
void quit(int *exit); 

/*-----------------------------------------HANDLE MENU--------------------------------------------*/

/*
 * Define the function handling the main menu
 */
struct json_object *handle_menu(Symbol s, Client client, struct json_object *clients, int *flag, int *exit, int *index, char *passwd, char *id, int *log_in);

/*-----------------CLIENT MENU-------------------*/

/*
 * Define the function handling the client menu
 */
void handle_client_menu(Symbol s, Client client, struct json_object *clients, int *flag, int *exit, int *index, char *passwd,char *id);

/*
 * Define the function handling the client account management menu
 */
void handle_client_account_management(Symbol s, Client client, struct json_object *clients, int *flag, int *exit, int *index, char *passwd, char *id);

/*
 * Define the function handling the client administration menu
 */
void handle_client_administration(Symbol s, Client client, struct json_object *clients, int *flag, int *exit, int *index, char *passwd, char *id);

/*-----------------ADMIN MENU-------------------*/

/*
 * Define the function handling the administrator menu
 */
struct json_object *handle_administrator_menu(Symbol s, Client client, struct json_object *clients, int *flag, int *exit, int *index, char *passwd, char *id);

/*
 * Define the function handling the administrator account management menu
 */
void handle_admin_account_management(Symbol s, Client client, struct json_object *clients, int *flag, int *exit, int *index, char *passwd, char *id);

/*
 * Define the function handling the administrator client management menu
 */
struct json_object *handle_admin_client_management(Symbol s, Client client,struct json_object *clients, int *flag, int *exit, int *index, char *passwd, char *id);

/*
 * Define the function handling the administrator administration menu
 */
void handle_admin_administration(Symbol s, Client client, struct json_object *clients, int *flag, int *exit, int *index, char *passwd, char *id);

/*------------------------------------------------------------------------------------------------*/

#endif
