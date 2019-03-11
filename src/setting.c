#include <stdio.h>
#include <stdlib.h>
#include "displayShell.h"
#include "input.h"
#include "setting.h"

/*
 * Introduce a simple structre handling the index of menu
 */
struct symbol {
	int flag;
        int exit;
	int index;
};

/*
 * Constructor of symbol structure
 */
Symbol symbol(void) {
	Symbol s = (Symbol) malloc(sizeof(Symbol));
	s->exit = 1;
	return s;
}

/*
 * Define the exit feature
 */
int quit(Symbol s) {
	printf("\nGOODBYE!\n");
       	end_bar();//Display the end bar.
       	return s->exit = 0;
}

/*
 * Define the back feature
 */
int back(Symbol s) {
	display_menu(&s->exit);//Display the main menu.
        choose_feature(&s->flag);//Choose the feature you want to run
        handle_menu(s);
}

/*
 * Define the function handling the main menu
 */
void handle_menu(Symbol s) {
	switch(s->flag) {
		case 1 :
			display_client(&s->exit);//Dipslay the administrator menu
                	choose_feature(&s->index);//Choose the feature you want to run
			handle_client_menu(s);
			break;
		case 2 :
			display_administrator(&s->exit);//Dipslay the administrator menu
			choose_feature(&s->index);//Choose the feature you want to run
			handle_administrator_menu(s);
			break;
		case 3 ://Check if the user want to quit the program
			quit(s);
			break;
	}
}

/*
 * Define the function handling the client menu
 */
void handle_client_menu(Symbol s) {
	switch(s->flag) {
                case 1 : 
			printf("\nAccount management :\n\t\t- check your account balance\n\t\t- check your transaction list on a chososen periode\n\t\t- transfer\n");
			break;
		case 2 :
		       	printf("\nAdministration :\n\t\t- change your password\n\t\t- create a new account\n\t\t- delete an account\n");
            		break;
		case 3 :
			back(s);
			break;
		case 4 ://Check if the user want to quit the program
			quit(s);
			break;
        }
}

/*
 * Define the function handling the administrator menu
 */
void handle_administrator_menu(Symbol s) {
	switch(s->flag) {
                case 1 :
			printf("\nAccount management :\n\t\t- create an account\n\t\t- modify an account\n\t\t- delete an account\n\t\t- display the account list by type of account\n");
			break;
		case 2 :printf("\nClient management :\n\t\t- add a client\n\t\t- modify clients coordinates_n- display the list of holders of the account\n");
			break;
		case 3 :
                        printf("\nAdministration :\n\t\t- Change password\n");
                        break;
                case 4 :
                        back(s);
			break;
        	case 5 ://Check if the user want to quit the program
                        quit(s);
			break;
	}
}
