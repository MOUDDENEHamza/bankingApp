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
 * Define the function handling the main menu
 */
int handle_menu(int *flag, int *exit) {
	if (*flag == 1) {
		display_client(exit);//Dipslay the client menu
		choose_feature(flag);//Choose the feature you want to run
	}
	if (*flag == 2) {
		display_administrator(exit);//Dipslay the administrator menu
		choose_feature(flag);//Choose the feature you want to run
	}
}
