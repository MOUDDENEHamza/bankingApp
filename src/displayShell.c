#include <stdio.h>
#include "displayShell.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

/**
 * Display the init bar
 */
void init_bar(void) {
    printf("\n*****************************************************************************************************\n");
    printf("\n\t\t\t\t\t"GREEN"M&K BANK"RESET"\n");
    printf("\n*****************************************************************************************************\n");
    printf("\n\nStart program ...\n");
}

/**-------------------------------------DISPLAY MAIN MENU------------------------------------------**/

/**
 * Display the main menu
 */
void display_menu(void) {
    printf("\n\t\t\t\tMAIN MENU\n");
    printf("\n"BLUE"1)-Client area"RESET);
    printf("\n"BLUE"2)-Administrator area"RESET);
    printf("\n"RED"3)-Exit"RESET);
    printf("\n\nIf you are a client type 1, If you are an administrator type 2, if you want to exit type 3.\n");
}

/**------------DISPLAY CLIENT MENU----------------**/

/**
 * Display the client menu
 */
void display_client(int *exit) {
    *exit = 4;
    printf("\n\t\t\t\tCLIENT AREA\n");
    printf("\n"BLUE"1)-Account management"RESET);
    printf("\n"BLUE"2)-Administration"RESET);
    printf("\n"BLUE"3)-Sign out"RESET);
    printf("\n"RED"%d)-Exit\n"RESET, *exit);
}

/**
 * Display the client account management submenu
 */
void display_client_account_management(void) {
    printf("\n\t\t\t\tAccount management\n");
    printf("\n"BLUE"1)-Check your account balance"RESET);
    printf("\n"BLUE"2)-Get your transaction list on a chosen period"RESET);
    printf("\n"BLUE"3)-Transfer money"RESET);
    printf("\n"BLUE"4)-Pay by card"RESET);
    printf("\n"BLUE"5)-Make a deposit\n"RESET);
}

/**
 * Display the client account management submenu
 */
void display_client_administration(void) {
    printf("\n\t\t\t\tAdministration\n");
    printf("\n"BLUE"1)-Change your password"RESET);
    printf("\n"BLUE"2)-Create a new account"RESET);
    printf("\n"BLUE"3)-Delete account\n"RESET);
}

/**--------------DISPLAY ADMIN MENU----------------**/

/**
 * Display the administrator menu
 */
void display_administrator(int *exit) {
    *exit = 5;
    printf("\n\t\t\t\tADMINISTRATOR AREA\n");
    printf("\n"BLUE"1)-Account management"RESET);
    printf("\n"BLUE"2)-Client management"RESET);
    printf("\n"BLUE"3)-Administration"RESET);
    printf("\n"BLUE"4)-Sign out"RESET);
    printf("\n"RED"%d)-Exit\n"RESET, *exit);
}

/**
 * Display the client account management submenu
 */
void display_admin_account_management(void) {
    printf("\n\t\t\t\tClient management\n");
    printf("\n"BLUE"1)-Create an account"RESET);
    printf("\n"BLUE"2)-Delete an account"RESET);
    printf("\n"BLUE"3)-Display the account list by type of account\n"RESET);
}

/**
 * Display the admin account management submenu
 */
void display_admin_client_management(void) {
    printf("\n\t\t\t\tAdministration\n");
    printf("\n"BLUE"1)-Add a client"RESET);
    printf("\n"BLUE"2)-Modify clients coordinates"RESET);
    printf("\n"BLUE"3)-Display the list of holders of the account\n"RESET);
}

/**
 * Display the client account management submenu
 */
void display_admin_administration(void) {
    printf("\n\t\t\t\tAdministration\n");
    printf("\n"BLUE"Change password :"RESET" Loading...\n");
}

/**------------------------------------------------------------------------------------------------**/

/**--------------------------------DISPLAY CLIENT&ADMIN MESSAGE------------------------------------**/

/**
 *Display an error message if the user input an incorrect flag
 */
void display_error_flag(void) {
    printf(RED"\nERROR :"RESET" Wrong Choice. Please enter again.\n");
}

/**
 *Display an error message if the user input an incorrect id or password
 */
void display_error_connexion_client(void) {
    printf(RED"\nERROR :"RESET" Wrong id or password. Please try again.\n");
}

/**
 *Display an error message if the administrator input an incorrect password
 */
void display_error_connexion_admin(void) {
    printf(RED"\nERROR :"RESET" Wrong password. Please try again.\n");
}

/**
 * Display a message while deleting account
 */
void display_account_type(void) {
    printf("\nPlease, specify the type of account you want handle :\n");
    printf("\n\t"BLUE"1)-CURRENT"RESET);
    printf("\n\t"GREEN"2)-SAVINGS"RESET);
    printf("\n\t"RED"3)-JOINT\n"RESET);
}

/**
 * Display a message while editing consulting the balance of the client
 */
void display_consulting_balance(void) {
    printf("\nConsult the balance : LOADING...\n");
}

/**
 * Display a message while consulting the transfer list of the client in a given period
 */
void display_transfer_list(void) {
    printf("\nDownload transaction file : LOADING...\n");
    printf("\nDATE,\t\t\tOPERATION,\t\tACCOUNT,\t\tAMOUNT,\t\t\tBALANCE\n");
}

/**
 * Display a the balance of a given account
 */
void display_balance(char *type, float *balance) {
    printf("\nThe balance of your %s account is : "GREEN"+%f€"RESET"\n", type, *balance);
}

/**
 * Display a message of creating account
 */
void display_creation_account(void) {
    printf("\nCreate a new account : LOADING...\n");
}

/**
 * Display a message while creating account
 */
void display_success_creation_account(void) {
    printf("\n"GREEN"DONE : "RESET"The account has been created with success\n");
    printf("\nCome back the precedent menu\n");
}

/**
 * Display a message while creating account failed
 */
void display_failed_creation_account(void) {
    printf("\n"RED"FAILED : "RESET"You can not create an account with the same entitled of an existent account\n");
    printf("\nCome back the precedent menu\n");
}

/**
 * Display a message while is about wrong input
 */
void display_wrong_input(void) {
    printf("\n"RED"ERROR : "RESET"Wrong input, please try again\n");
    printf("\nCome back the precedent menu\n");
}

/**
 * Display a message of deleting account
 */
void display_deletion_account(void) {
    printf("\nDelete an existing account : LOADING...\n");
}

/**
 * Display a message while deleting account
 */
void display_success_deletion_account(void) {
    printf("\n"GREEN"DONE : "RESET"The account has been deleted with success\n");
    printf("\nCome back the administrator menu\n");
}

/**
 * Display a message while quiting administrator menu
 */
void display_quit_administrator_menu(void) {
    printf("\nCome back the administrator menu\n");
}

/**
 * Display a message while quiting client menu
 */
void display_quit_client_menu(void) {
    printf("\nCome back the client menu\n");
}

/**
 * Display a message of adding client
 */
void display_adding_client(void) {
    printf("\nAdd a new client : LOADING...\n");
}

/**
 * Display a message while adding client
 */
void display_success_adding_client(void) {
    printf("\n"GREEN"DONE : "RESET"Client has been added\n");
    printf("\nCome back the administrator menu\n");
}

/**
 * Display a message while editing coordinates of the client
 */
void display_editing_client(void) {
    printf("\nEdit client coordinates : LOADING...\n");
}

/**
 * Display a message while editing coordinates of client
 */
void display_success_editing_client(void) {
    printf("\n"GREEN"DONE : "RESET"The account has been edited with success\n");
    printf("\nCome back the administrator menu\n");
}

/**
 * Display entitled list of a given account
 */
void display_entitled_list(void) {
    printf("\nDisplay the entitled list of an account : LOADING...\n");
}

/**------------------------------------------------------------------------------------------------**/

/**
 * Display the end bar
 */
void end_bar(void) {
    printf("\nGOODBYE!\n");
    printf("\n\n\t\t\t\t\t"GREEN"THE END"RESET"\t\t\t\n");
    printf("\n*****************************************************************************************************\n");
}