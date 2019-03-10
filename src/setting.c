#include <stdio.h>
#include "setting.h"
#include "displayShell.h"
#include "input.h"

/*
 * Define the exit feature
 */
int quit(int *flag, int *exit) {
	if (*flag == *exit) {
		printf("\nGOODBYE!\n");
        	end_bar();//Display the end bar.
        	return 0;
	}
	return 1;
}

/*
 * Define the back feature
 */
int back(int *flag, int *exit) {
	display_menu(exit);//Display the main menu.
                choose_feature(flag);//Choose the feature you want to run
                handle_menu(flag, exit);
}

/*
 * Define the function handling the main menu
 */
void handle_menu(int *flag, int *exit) {
	switch(*flag) {
		case 1 :
			display_client(exit);//Dipslay the administrator menu
                	choose_feature(flag);//Choose the feature you want to run
			handle_client_menu(flag, exit);
			break;
		case 2 :
			display_administrator(exit);//Dipslay the administrator menu
			choose_feature(flag);//Choose the feature you want to run
			handle_administrator_menu(flag, exit);
			break;
	}
}

/*
 * Define the function handling the client menu
 */
void handle_client_menu(int *flag, int *exit) {
       	switch(*flag) {
                case 1 : 
			printf("\nAccount management :\n\t\t- check your account balance\n\t\t- check your transaction list on a chososen periode\n\t\t- transfer\n");
			break;

		case 2 :
		       	printf("\nAdministration :\n\t\t- change your password\n\t\t- create a new account\n\t\t- delete an account\n");
            		break;
		case 3 :
			back(flag, exit);
			break;
        }
}

/*
 * Define the function handling the administrator menu
 */
void handle_administrator_menu(int *flag, int *exit) {
        switch(*flag) {
                case 1 :
			printf("\nAccount management :\n\t\t- create an account\n\t\t- modify an account\n\t\t- delete an account\n\t\t- display the account list by type of account\n");
			break;
		case 2 :printf("\nClient management :\n\t\t- add a client\n\t\t- modify clients coordinates_n- display the list of holders of the account\n");
			break;
		case 3 :
                        printf("\nAdministration :\n\t\t- Change password\n");
                        break;
                case 4 :
                        back(flag, exit);
			break;
        }
}
