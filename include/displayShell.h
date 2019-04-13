#ifndef _DISPLAYSHELL_H_
#define _DISPLAYSHELL_H_

#include "struct.h"

/**
 * Display the init bar
 */
void init_bar(void);

/**-------------------------------------DISPLAY MAIN MENU------------------------------------------**/

/**
 * Display the main menu
 */
void display_menu(void);

/**------------DISPLAY CLIENT MENU----------------**/

/**
 * Display the client menu
 */
void display_client(int *exit);

/**
 * Display the client account management submenu
 */
void display_client_account_management(void);

/**
 * Display the client administration submenu
 */
void display_client_administration(void);

/**--------------DISPLAY ADMIN MENU----------------**/

/**
 * Display the administrator menu
 */
void display_administrator(int *exit);

/**
 * Display the admin account management submenu
 */
void display_admin_account_management(void);

/**
 * Display the admin client management submenu
 */
void display_admin_client_management(void);

/**
 * Display the admin administration submenu
 */
void display_admin_administration(void);

/**------------------------------------------------------------------------------------------------**/

/**
 *Display an error message if the user input an incorrect flag
 */
void display_error_flag(void) ;

/**
 *Display an error message if the user or administrator input an incorrect id
 */
void display_error_connexion_client(void);

/**
 *Display an error message if the user or administrator input an incorrect password
 */
void display_error_connexion_admin(void);

/**
 * Display a message while deleting account
 */
void display_account_type(void);

/**
 * Display a message of creating account
 */
void display_creation_account(void);

/**
 * Display a message while creating account
 */
void display_success_creation_account(void);

/**
 * Display a message while creating account failed
 */
void display_failed_creation_account(void);

/**
 * Display a message while is about wrong input
 */
void display_wrong_input(void);

/**
 * Display a message of deleting account
 */
void display_deletion_account(void);

/**
 * Display a message while deleting account
 */
void display_success_deletion_account(void);

/**
 * Display a message while quiting administrator menu
 */
void display_quit_administrator_menu(void);

/**
 * Display a message of adding client
 */
void display_adding_client(void);

/**
 * Display a message while adding client
 */
void display_success_adding_client(void);

/**
 * Display a message while editing coordinates of the client
 */
void display_editing_client(void);

/**
 * Display a message while editing coordinates of client
 */
void display_success_editing_client(void);

/**
 * Display entitled list of a given account
 */
void display_entitled_list(void);

/**
 * Display the end bar
 */
void end_bar(void);

#endif