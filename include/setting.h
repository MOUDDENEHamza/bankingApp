#ifndef _SETTING_H_
#define _SETTING_H_

/*
 * Introduce a simple structre handling the index of menu
 */

typedef struct symbol *Symbol;

/*
 * Constructor of symbol structure
 */
Symbol new_symbol(void);

/*
 * Define the exit feature
 */
int quit(Symbol s); 

/*
 * Define the back feature
 */
int back(Symbol s);

/*
 * Define the function handling the main menu
 */
void handle_menu(Symbol s);

/*
 * Define the function handling the client menu
 */
void handle_client_menu(Symbol s);

/*
 * Define the function handling the administrator menu
 */
void handle_administrator_menu(Symbol s);

void set_exit(Symbol s ,int *val);
int get_exit(Symbol s);
void set_flag(Symbol s ,int *val);
int get_flag(Symbol s);

#endif