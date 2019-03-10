#ifndef _SETTING_H_
#define _SETTING_H_

/*
 * Define the exit feature
 */
int quit(int *flag, int *exit); 

/*
 * Define the back feature
 */
int back(int *flag, int *exit);

/*
 * Define the function handling the main menu
 */
void handle_menu(int *flag, int *exit);

/*
 * Define the function handling the client menu
 */
void handle_client_menu(int *flag, int *exit);

/*
 * Define the function handling the administrator menu
 */
void handle_administrator_menu(int *flag, int *exit);

#endif
