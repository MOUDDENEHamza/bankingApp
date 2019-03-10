#include <stdio.h>
#include "setting.h"
#include "displayShell.h"
#include "input.h"

/*
 * Define the exit feature
 */
int quit(int *flag) {
	if (*flag == 8) {
		printf("\nGOODBYE!\n");
        	end_bar();//Display the end bar.
        	return 0;
	}
	return 1;
}

/*
 * Define the function handling the main menu
 */
int handle_menu(int *flag) {
	if (*flag == 1) {
		display_home();//Dipslay the home menu
		choose_feature(flag);//Choose the feature you want to run
	}
	if (*flag == 2) {
		display_settings();//Dipslay the settings menu
		choose_feature(flag);//Choose the feature you want to run
	}
}
