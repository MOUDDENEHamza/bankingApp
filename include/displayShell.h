#ifndef _DISPLAYSHELL_H_
#define _DISPLAYSHELL_H_

#include "struct.h"

/*
 * Display the init bar
 */
void init_bar(void);

/*-------------------------------------DISPLAY MAIN MENU------------------------------------------*/

/*
 * Display the main menu
 */
void display_menu(int *exit);

/*------------DISPLAY CLIENT MENU----------------*/

/*
 * Display the client menu
 */
void display_client(int *exit);

/*
 * Display the client account management submenu
 */
void display_client_account_management(void);

/*
 * Display the client administration submenu
 */
void display_client_administration(void);

/*--------------DISPLAY ADMIN MENU----------------*/

/*
 * Display the administrator menu
 */
void display_administrator(int *exit);

/*
 * Display the admin account management submenu
 */
void display_admin_account_management(void);

/*
 * Display the admin client management submenu
 */
void display_admin_client_management(void);

/*
 * Display the admin administration submenu
 */
void display_admin_administration(void);

/*------------------------------------------------------------------------------------------------*/

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
void display_account_type(void);

/*
 * Display the end bar
 */
void end_bar(void);

#endif
