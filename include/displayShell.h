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
 * Display the end bar
 */
void end_bar(void);

#endif
