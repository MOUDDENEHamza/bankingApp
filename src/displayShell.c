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
	printf(BLUE"\n1)-Home\n2)-Settings\n3)-Exit\n"RESET);
}

/*
 * Display the end bar
 */
void end_bar(void) {
	printf("\n\n\t\t\t\t"GREEN"THE END"RESET"\t\t\t\n");
        printf("\n******************************************************************************\n\n");
}
