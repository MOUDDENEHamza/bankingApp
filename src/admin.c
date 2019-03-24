#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "struct.h"
#include "displayShell.h"
#include "input.h"

enum boolean{true,false};

/*return the account to edit */
Account choosen_account(Client client ,int choice_type){
	Account a=get_account(client);
	if(choice_type==1){
		return a;
	}
	else{
		for(int i=1; i<choice_type; i++){
			a=get_nextAccount(a);
		}
		return a;
	}
}

/*get the last added account of the client in list list of account*/
Account get_lastAccount(Client client){
	Account a=get_account(client);
	while(get_nextAccount(a)!=NULL){
		a=get_nextAccount(a);
	}
	return a;
}

/*set the next account of the last account as a real account*/
void set_nextOfLastAccout(Client client,Account account){
	Account last=get_lastAccount(client);
	set_nextAccount(last,account);
}

/*get the number of acount that have the client*/
int nb_accounts(Client client){
	Account a=get_account(client);
	int nb=0;
	while(a!=NULL){
		a=get_nextAccount(a);
		nb++;
	}
	return nb;
}

/*return true if the input of admin or user is in list of choice*/
bool in_1__nb_accounts(int choice,int nb){
	int i=1;
	while(i<=nb && i!=choice){
		i++;	
	}
	if(i<=nb){
		return true;
	}
	else
	{
		return false;
	}
	
}


/*
 *Create account to the client
 */
void create_account(Client client) {
	printf("choose the type of account you want to create\n");
	display_choose_type();
	input_create_account(client);
}
/* add another account type for the client*/
void add_account(Client client){
	printf("choose the type of account you want to add\n");
	display_choose_type();
	input_add_account(client);
}

/*
 *Edit account to the client
 */
void edit_account(Client client) {
	int choice,choice_type;
	printf("choose the type of account you want to edit\n");
	back1:
	display_typeAccounts(client);
	scanf("%d",&choice_type);
	while(!in_1__nb_accounts(choice_type,nb_accounts(client))){
		printf("unexistant choice !\n");
		printf("retry again");
		goto back1;
	}
	back2:
	display_choose_edit();
	scanf("%d",&choice);
	while(1){
		switch (choice)
		{
			case 1:
				input_new_balance(choosen_account(client,choice_type)); break;
			case 2:
				input_entitled(choosen_account(client,choice_type)); break;
	
			default:
				printf("unexistant choice !\n");
				printf("retry again\n");
				goto back2;
		}
		continue;
	}
}       


/*
 *delete account
 */
void delete_account(Client client) {
	printf("choose the acount type you want to delete\n");
	back:
	display_typeAccounts(client);
	int choice_type;
	scanf("%d",choice_type);
	while(!in_1__nb_accounts(choice_type,nb_accounts(client))){
		printf("unexistant choice !\n");
		printf("retry again\n");
		goto back;
	}
	Account temp;
	if(choice_type==1){
		temp=get_account(client);
		set_account(client,get_nextAccount(temp));
		free(temp);
	}
	else{
		if(choosen_account(client,choice_type)==get_lastAccount(client)){
			free(get_lastAccount(client));
		}
		else{
			Account a=choosen_account(client,choice_type-1);
			temp=get_nextAccount(a);
			set_nextAccount(a,get_nextAccount(temp));
			free(temp);
		}
	}
}

/*
 *Add client
 */
void add_client(void) {
	printf("\nAdd client : loading...\n");
	Client client = new_client();
	input_perso_info(client);
	printf("\nClient has been added. Come back to the administrator menu.\n");
}

/*
 *Edit the personal information of the client
 */
void edit_perso_info_client(Client client) {
	printf("\nChange the coordinates : loading...\n");
	free(get_perso_info(client));
	printf("\nthe coordinates has been edited. Come back to the administrator menu.\n");
}