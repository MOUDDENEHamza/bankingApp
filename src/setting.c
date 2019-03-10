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
                case 2 :
                        printf("\n%d\n", *flag);
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
                case 2 :
		case 3 :
                        printf("\n%d\n", *flag);
                        break;
                case 4 :
                        back(flag, exit);
			break;
        }
}
