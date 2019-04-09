#include <stdio.h>
#include "displayShell.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"
#define MAGENTA "\x1B[35m"
#define YELLOW "\x1B[33m"
#define CAYAN "\x1B[36m"


/*
 * Display the init bar
 */
void init_bar(void) {
    printf("\n******************************************************************************\n");
    printf("\n\t\t\t\t"GREEN"  BANK"RESET"\t\t\t\n");
    printf("\n******************************************************************************\n\n\nStart program ...\n");
}

/*-------------------------------------DISPLAY MAIN MENU------------------------------------------*/

/*
 * Display the main menu
 */
void display_menu(int *exit) {
    *exit = 3;
    printf("\n\t\t\t\tMAIN MENU\n");
    printf(BLUE"\n1)-Client area\n2)-Adminstrator area\n"RESET""RED"%d)-Exit"RESET"\n\nIf you are a client type 1, If you are an administrator type 2, if you want to exit type %d.\n",
           *exit, *exit);
}

/*------------DISPLAY CLIENT MENU----------------*/

/*
 * Display the client menu
 */
void display_client(int *exit) {
    *exit = 4;
    printf("\n\t\t\t\tCLIENT AREA\n");
    printf(BLUE"\n1)-Account management\n2)-Administration\n3)-Sign out\n"RESET""RED"%d)-Exit\n"RESET, *exit);
}

/*
 * Display the client account management submenu
 */
void display_client_account_management(void) {
    printf("\n\t\t\t\tAccount management\n\n"BLUE"1)-Check your account balance\n2)-Get your transaction list on a chosen period\n3)-Transfer money\n4)-Pay by card\n5)-Make a deposit\n"RESET);
}

/*
 * Display the client account management submenu
 */
void display_client_administration(void) {
    printf("\n\t\t\t\tAdministration\n\n"BLUE"1)-Change your password\n2)-Create a new account\n3)-Delete account\n"RESET);
}

/*--------------DISPLAY ADMIN MENU----------------*/

/*
 * Display the administrator menu
 */
void display_administrator(int *exit) {
    *exit = 5;
    printf("\n\t\t\t\tADMINISTRATOR AREA\n");
    printf(BLUE"\n1)-Account management\n2)-Client management\n3)-Administration\n4)-Sign out\n"RESET""RED"%d)-Exit\n"RESET,
           *exit);
}

/*
 * Display the client account management submenu
 */
void display_admin_account_management(void) {
    printf("\n\t\t\t\tClient management\n\n"BLUE"1)-Create an account\n2)-Modify an account\n3)-Delete an account\n4)-Display the account list by type of account\n"RED"5)-Exit\n"RESET);
}

/*
 * Display the admin account management submenu
 */
void display_admin_client_management(void) {
    printf("\n\t\t\t\tAdministration\n\n"BLUE"1)-Add a client\n2)-Modify clients coordinates\n3)-Display the list of holders of the account\n"RED"4)-Exit\n"RESET);
}

/*
 * Display the client account management submenu
 */
void display_admin_administration(void) {
    printf("\n\t\t\t\tAdministration\n\n"BLUE"1)-Change password\n"RESET);
}

/*------------------------------------------------------------------------------------------------*/

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

/*display a list of accounts */
void display_choose_type(){
    printf("\n\t\t1: CURRENT\n");
    printf("\t\t2: SAVINGS\n");    
    printf("\t\t3: TERM\n");
    printf("\t\t4: TITLE\n");
    printf("\t\t5: INDIVIDUAL\n");
    printf("\t\t6: JOINT\n");
    printf("Enter your choice : ");
}


/*ask to edit the information of account to edit*/
void display_choose_edit() {
    printf("\n\tchoose what you want to edit\n");
    printf("\n\t1 : BALANCE");
    printf("\t2 : ENTITLED\n");
    printf("Enter your choice : \n");
}

void display_choose_coordonatesToEdit(void){
    printf("\t\nchoose what you want to edit\n");
    printf("\t1 : EMAIL\n");
    printf("\t2 : PHONE\n");
}


/*display all accounts of the client*/
void display_typeAccounts(Client client,int *nbacc) {
    Account *tabAccount=malloc(nbacc[0]*sizeof(Account));
    tabAccount[0]=new_account();
    tabAccount[0]=get_account(client);
    if (get_balance(tabAccount[0])>=0) {
        printf("\n\t1 : %s  %s ACCOUNT [solde : "GREEN"%.2f"RESET"]\n",get_entitled(tabAccount[0]),get_type(tabAccount[0]),get_balance(tabAccount[0]));
    }
    else
    {
        printf("\n\t1 : %s  %s ACCOUNT [solde : "RED"%.2f"RESET"]\n",get_entitled(tabAccount[0]),get_type(tabAccount[0]),get_balance(tabAccount[0]));
    }
    
    for(int cmpt=1; cmpt<nbacc[0]; cmpt++){
        tabAccount[cmpt]=new_account();
        tabAccount[cmpt]=get_nextAccount(tabAccount[cmpt-1]);
        if(get_balance(tabAccount[cmpt])>=0){
            printf("\n\t%d : %s  %s ACCOUNT [solde : "GREEN"%.2f"RESET"]\n",cmpt+1,get_entitled(tabAccount[cmpt]),get_type(tabAccount[cmpt]),get_balance(tabAccount[cmpt]));
        }
        else
        {
            printf("\n\t%d : %s  %s ACCOUNT [solde : "RED"%.2f"RESET"]\n",cmpt+1,get_entitled(tabAccount[cmpt]),get_type(tabAccount[cmpt]),get_balance(tabAccount[cmpt]));
        }
        
    }
}

void display_entitled(Client client, int *nbacc){
    Account *tabAccount=malloc(nbacc[0]*sizeof(Account));
    tabAccount[0]=new_account();
    tabAccount[0]=get_account(client);
    printf("\n\t1 : %s  \n",get_entitled(tabAccount[0]));
    for(int cmpt=1; cmpt<nbacc[0]; cmpt++){
        tabAccount[cmpt]=new_account();
        tabAccount[cmpt]=get_nextAccount(tabAccount[cmpt-1]);
        printf("\n\t%d : %s  \n",cmpt+1,get_entitled(tabAccount[cmpt]));
    }
}

void display_edit_succesfoul(void){
    printf(GREEN"\nok\ninformations edited successfoully !\n"RESET);
}

void display_delet_successfoul(void){
    printf(GREEN"\nok\naccount deleted successfoully !\n"RESET);
}

void display_no_account(void){
    printf(MAGENTA"\nOoup's !!!\nTHAT CLIENT HAS NOT AN ACCOUNT !\n"RESET);
}

void display_wrong(void){
    printf(CAYAN"\nWrong choice !\nretry again !\n"RESET);
}

void display_unexistant_ID(void){
    printf(CAYAN"Sorry , THAT ID DOESN'T EXIST !\n"RESET);
}
