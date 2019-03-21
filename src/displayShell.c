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
	printf("\n******************************************************************************\n\n\nStart program ...\n");
}

/*
 * Display the main menu
 */
void display_menu(int *exit) {
	*exit = 3;
	printf("\n\t\t\t\tMAIN MENU\n");
	printf(BLUE"\n1)-Client area\n2)-Adminstrator area\n"RESET""RED"%d)-Exit"RESET"\n\nIf you are a client type 1, If you are an administrator type 2, if you want to exit type %d.\n", *exit, *exit);
}

/*
 * Display the client menu
 */
void display_client(int *exit) {
	*exit = 4;
	printf("\n\t\t\t\tCLIENT AREA\n");
        printf(BLUE"\n1)-Account management\n2)-Administration\n3)-Sign out\n"RESET""RED"%d)-Exit\n"RESET,*exit);
}
	
/*
 * Display the administrator menu
 */
void display_administrator(int *exit) {
	*exit = 5;
	printf("\n\t\t\t\tADMINISTRATOR AREA\n");
        printf(BLUE"\n1)-Account management\n2)-Client management\n3)-Administration\n4)-Sign out\n"RESET""RED"%d)-Exit\n"RESET, *exit);
}

/*
 * Display the administrator submenu
 */
void display_client_management(void) {
	printf("\n\t\t\t\tClient management\n"BLUE"1)-Add a client\n2)-Modify clients coordinates\n3)-Display the list of holders of the account\n"RESET);
}

/*
 *Display an error message if the user input an incorrect flag
 */
void display_error_flag(Symbol s, int *flag) {
	printf(RED"\nERROR :"RESET" Wrong Choice. Please enter again.\n");
}

/*
 *Display an error message if the user input an incorrect id or password
 */
void display_error_connexion_client(void) {
	printf(RED"\nERROR :"RESET" Wrong id or password. Please try again.\n");
}

/*
 *Display an error message if the administrator input an incorrect password
 */
void display_error_connexion_admin(void) {
        printf(RED"\nERROR :"RESET" Wrong password. Please try again.\n");
}

/*
 * Display a message while deleting account
 */
void display_deleting_msg(void) {
	printf("\nAccount has been deleted.\n");
}

/*
 * Display the end bar
 */
void end_bar(void) {
	printf("\nGOODBYE!\n");
	printf("\n\n\t\t\t\t"GREEN"THE END"RESET"\t\t\t\n");
        printf("\n******************************************************************************\n\n");
}
