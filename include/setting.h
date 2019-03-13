#ifndef _SETTING_H_
#define _SETTING_H_

#include "security.h"

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the index of menu
 */
typedef struct symbol *Symbol;

/*---------------Setters--------------*/

/*
 *Get flag value from the structure
 */
int get_flag(Symbol s);

/*
 *Get exit value from the structure
 */
int get_exit(Symbol s);

/*
 *Get index value from the structure
 */
int get_index(Symbol s);

/*--------------Getters---------------*/

/*
 *Set value to flag in structure
 */
void set_flag(Symbol s ,int *val);

/*
 *Set value to exit in structure
 */
void set_exit(Symbol s ,int *val);

/*
 *Set value to index in structure
 */
void set_index(Symbol s, int *val);

/*----------------------------------------------------------------------------*/

/*
 * Constructor of symbol structure
 */
Symbol new_symbol(void);

/*
 * Define the exit feature
 */
void quit(int *exit); 

/*
 * Define the function handling the main menu
 */
void handle_menu(Symbol s, Security p, int *flag, int *exit, int *index, char *passwd);

/*
 * Define the function handling the client menu
 */
void handle_client_menu(Symbol s, Security p, int *flag, int *exit, int *index, char *passwd);

/*
 * Define the function handling the administrator menu
 */
void handle_administrator_menu(Symbol s, Security p, int *flag, int *exit, int *index, char *passwd);

#endif
