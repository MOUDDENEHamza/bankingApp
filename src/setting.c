#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setting.h"
#include "displayShell.h"
#include "input.h"
#include "security.h"
#include "admin.h"

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
void handle_menu(Symbol s, Client client, Json j, int *flag, int *exit, int *index, char *passwd, char *id, int *log_in) {
	switch (*flag) {
		case 1 :
			if (*log_in == 0) {
				input_id(client, id);
				input_passwd(client, passwd);
			}	
			if(!valid_id_client(j, id) && !valid_passwd_client(j, passwd)) {
				*log_in = 1;
				display_client(exit); //Dipslay the administrator menu
				choose_feature(s, index); //Choose the feature you want to run
				handle_client_menu(s, client, j, index, exit, index, passwd, id);
				break;
			} else {
                        display_error_connexion_client();//Display an error message if the user input an incorrect id or password
				break;
			}
		case 2 :
			if (*log_in == 0) {
				input_passwd(client, passwd);
			}
			if (!connect_admin(passwd)) {
				display_administrator(exit); //Dipslay the administrator menu
				choose_feature(s, index); //Choose the feature you want to run
				handle_administrator_menu(s, client, j, index, exit, index, passwd, id);
				*log_in = 1;
				break;
			} else {
				display_error_connexion_admin(); //Display an error message if the administrator input an incorrect password
				break;
			}
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
void handle_client_menu(Symbol s, Client client, Json j, int *flag, int *exit, int *index, char *passwd, char *id) {
 	switch(*flag) {
		case 1 :	
			display_client_account_management();
			break;
		case 2 :
			display_client_administration();
			break;
		case 3 : //If the user want to sign out the submenu
			break;
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
void handle_administrator_menu(Symbol s, Client client, Json j, int *flag, int *exit, int *index, char *passwd, char *id) {
	switch(*flag) { 
                case 1 : 
			display_admin_account_management();
			break;
		case 2 :
			display_admin_client_management();
			choose_feature(s, index); //Choose the feature you want to run
			handle_client_management(s, client, j, index, exit, index, passwd, id);
			break;
		case 3 :
			display_admin_administration();
			break;
		case 4 : //If the user want to sign out the submenu
			break;
		case 5 : //Check if the user want to quit the program
			quit(exit);
			break;
		default ://Display an error message if the user input an incorrect flag
                        display_error_flag(s, flag);
			break;
	} 
}

/*
 * Define the function handling the client management menu
 */
void handle_client_management(Symbol s, Client client, Json j, int *flag, int *exit, int *index, char *passwd, char *id) {
	restart:
	switch(*flag) {
                case 1 :
			add_client();
        		break;
		case 2 :

                        break;
                case 3 :
                        break;
                default ://Display an error message if the user input an incorrect flag
                        display_error_flag(s, flag);
	 		choose_feature(s, flag); //Choose the feature you want to run
			goto restart;
        }
}
