#ifndef _SETTING_H_
#define _SETTING_H_

#include "struct.h"

/*
 * Define the exit feature
 */
void quit(int *exit); 

/*
 * Define the function handling the main menu
 */
void handle_menu(Symbol s, Account_owner ao, Json j, int *flag, int *exit, int *index, char *passwd, char *id, int *log_in);

/*
 * Define the function handling the client menu
 */
void handle_client_menu(Symbol s, Account_owner ao, Json j, int *flag, int *exit, int *index, char *passwd, char *id);

/*
 * Define the function handling the administrator menu
 */
void handle_administrator_menu(Symbol s, Account_owner ao, Json j, int *flag, int *exit, int *index, char *passwd, char *id);

#endif
