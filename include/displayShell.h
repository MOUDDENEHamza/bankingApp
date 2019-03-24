#ifndef _DISPLAYSHELL_H_
#define _DISPLAYSHELL_H_

#include "struct.h"

/*
 * Display the init bar
 */
void init_bar(void);

/*
 * Display the main menu
 */
void display_menu(int *exit);

/*
 * Display the home menu
 */
void display_client(int *exit);

/*
 * Display the settings menu
 */
void display_administrator(int *exit);

/*
 * Display the administrator submenu
 */
void display_client_management(void);

/*
 *Display an error message if the user input an incorrect flag
 */
void display_error_flag(Symbol s, int *flag) ;

/*
 *Display an error message if the user or administrator input an incorrect id
 */
void display_error_connexion_client(void);

/*
 *Display an error message if the user or administrator input an incorrect password
 */
void display_error_connexion_admin(void);

/*
 * Display a message while deleting account
 */
void display_deleting_msg(void);

/*
 * Display the end bar
 */
void end_bar(void);

/*display a list of accounts*/
void display_choose_type();

/*ask to edit the information of account to edit*/
void display_choose_edit();

/*display all accounts of the client*/
void display_typeAccounts(Client client);

#endif
