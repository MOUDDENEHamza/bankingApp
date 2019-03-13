#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "displayShell.h"
#include "input.h"
#include "setting.h"
#include "security.h"

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the index of menu
 */
struct symbol{
	int flag;
    	int exit;
	int index;
}symbol;

/*---------------Setters--------------*/

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

/*---------------Getters--------------*/

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

/*
 * Define the exit feature
 */
void quit(int *exit) {
       	end_bar(); //Display the end bar.
	*exit = 0;
}

/*
 * Define the function handling the main menu
 */
void handle_menu(Symbol s, Security p, int *flag, int *exit, int *index, char *passwd, char *id) {
	switch (*flag) {
		case 1 :
			input_id(p, id);
			if (strcmp(id, "client1") == 0) {
				input_passwd(p, passwd);
				if(strcmp(passwd, "13/05/2000") == 0) {
					display_client(exit); //Dipslay the administrator menu
					choose_feature(s, index); //Choose the feature you want to run
					handle_client_menu(s, p, index, exit, index, passwd, id);
				} else { //Display an error message if the administrator input an incorrect password
                                display_error_passwd();
                        	}
			} else {
				display_error_id();//Display an error message if the user or administrator input an incorrect id
			}
			break;
		case 2 :
			input_passwd(p, passwd);
			if (!connect_admin(passwd)) {
			display_administrator(exit); //Dipslay the administrator menu
			choose_feature(s, index); //Choose the feature you want to run
			handle_administrator_menu(s, p, index, exit, index, passwd, id);
			} else { //Display an error message if the administrator input an incorrect password
				display_error_passwd();
			}
			break;
		case 3 : //Check if the user want to quit the program
			quit(exit);
			break;
		default ://Display an error message if the user input an incorrect flag
			display_error_flag(s, flag);
			choose_feature(s, flag);//Choose the feature you want to run
			break;
	}
}

/*
 * Define the function handling the client menu
 */
void handle_client_menu(Symbol s, Security p, int *flag, int *exit, int *index, char *passwd, char *id) {
 	switch(*flag) {
		case 1 :	
			printf("\nAccount management :\n\t\t- check your account balance\n\t\t- check your transaction list on a chososen periode\n\t\t- transfer\n");
			break;
		case 2 :
			printf("\nAdministration :\n\t\t- change your password\n\t\t- create a new account\n\t\t- delete an account\n");
			break;
		case 3 : //If the user want to quit the submenu
			display_menu(exit);//Display the main menu.
			choose_feature(s, flag);//Choose the feature you want to run
			return handle_menu(s, p, flag, exit, index, passwd, id);
		case 4 : //Check if the user want to quit the program
			quit(exit);
			break;
		default ://Display an error message if the user input an incorrect flag
                        display_error_flag(s, flag);
			break;
	}
}

/*
 * Define the function handling the administrator menu
 */
void handle_administrator_menu(Symbol s, Security p, int *flag, int *exit, int *index, char *passwd, char *id) {
	switch(*flag) { 
                case 1 : 
			printf("\nAccount management :\n\t\t- create an account\n\t\t- modify an account\n\t\t- delete an account\n\t\t- display the account list by type of account\n");
			break;
		case 2 :
			printf("\nClient management :\n\t\t- add a client\n\t\t- modify clients coordinates_n- display the list of holders of the account\n");
			break;
		case 3 :
	 		printf("\nAdministration :\n\t\t- Change password\n");
			break;
		case 4 : //If the user want to quit the submenu
                        display_menu(exit);//Display the main menu.
                        choose_feature(s, flag);//Choose the feature you want to run
                        return handle_menu(s, p, flag, exit, index, passwd, id);
		case 5 : //Check if the user want to quit the program
			quit(exit);
			break;
		default ://Display an error message if the user input an incorrect flag
                        display_error_flag(s, flag);
			break;
	} 
}
