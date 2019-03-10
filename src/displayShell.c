#include <stdio.h>
#include "displayShell.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

/*
 * Display the init bar
 */
void init_bar(void) {
	printf("\n******************************************************************************\n");
	printf("\n\t\t\t\t"GREEN"  BANK"RESET"\t\t\t\n");
	printf("\n******************************************************************************\n");
}

/*
 * Display the main menu
 */
void display_menu(void) {
	printf("\n\nStart program ...\n");
	printf("\n\t\t\t\tMAIN MENU\n");
	printf(BLUE"\n1)-Home\n2)-Settings\n"RESET""RED"8)-Exit\n"RESET);
}

/*
 * Display the home menu
 */
void display_home(void) {
	printf("\n\t\t\t\tWELCOME TO HOME\n");
        printf(BLUE"\n3)-Account management\n4)-Administration\n"RESET""RED"8)-Exit\n"RESET);
}
	
/*
 * Display the settings menu
 */
void display_settings() {
	printf("\n\t\t\t\tSETTINGS\n");
        printf(BLUE"\n5)-Account management\n6)-Customer management\n7)-Administration\n"RESET""RED"8)-Exit\n"RESET);
}


/*
 * Display the end bar
 */
void end_bar(void) {
	printf("\n\n\t\t\t\t"GREEN"THE END"RESET"\t\t\t\n");
        printf("\n******************************************************************************\n\n");
}
