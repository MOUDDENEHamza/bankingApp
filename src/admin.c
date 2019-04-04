#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "struct.h"
#include "displayShell.h"
#include "input.h"
#include "json.h"

#define SIZE 64

enum boolean {
    true, false
};

char* concatenate(char* str1,char* str2){
    char* str=malloc((strlen(str1)+strlen(str2))*sizeof(char));
    for(int i=0; i<strlen(str1)+strlen(str2); i++){
        if(i<strlen(str1))
            str[i]=str1[i];
        else
        {
            str[i]=str2[i-strlen(str1)];
        }
        
    }
    return str;
}

/*return the account to edit */
Account choosen_account(Client client, int choice_type) {
    Account a = get_account(client);
    if (choice_type == 1) {
        return a;
    } else {
        for (int i = 1; i < choice_type; i++) {
            a = get_nextAccount(a);
        }
        return a;
    }
}

/*get the number of acount that have the client*/
int nb_accounts(Client client) {
    Account a = get_account(client);
    int nb = 0;
    while (a != NULL) {
        a = get_nextAccount(a);
        nb++;
    }
    return nb;
}

/*return true if the input of admin or user is in list of choice*/
bool in_1__nb_accounts(int choice, int nb) {
    int i = 1;
    while (i <= nb && i != choice) {
        i++;
    }
    if (i <= nb) {
        return true;
    } else {
        return false;
    }

}


Client create_new_account(void) {
    char *id=malloc(sizeof(char*));
    printf("\nEnter the client ID\n");
    scanf("%s",id);
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    import_Client_idx_from_Json(id,idx);
    Client client=new_client();
    import_Client_from_Json(idx,client,nb_accounts);
    printf("nb_account = %d ",*nb_accounts);
    printf("\n\nchoose the type of account you want to create\n");
    printf("you have just to enter the number referenced! \n");
    display_choose_type();
    input_add_account(client,nb_accounts);
    printf("ok\n");
    return client;
}

/*
 *Create account to the client
 */
void create_account(Client client) {
    printf("\n\nchoose the type of account you want to create\n");
    printf("you have just to enter the number referenced! \n");
    display_choose_type();
    input_create_account(client);
}

/* add another account type for the client*/
/*void add_account(Client client) {
    printf("choose the type of account you want to add\n");
    display_choose_type();
    input_add_account(client,);
}*/

/*
 *Edit account to the client
 */
void edit_account(Client client) {
    int choice, choice_type;
    printf("choose the type of account you want to edit\n");
    back1:
    display_typeAccounts(client);
    scanf("%d", &choice_type);
    while (!in_1__nb_accounts(choice_type, nb_accounts(client))) {
        printf("unexistant choice !\n");
        printf("retry again");
        goto back1;
    }
    back2:
    display_choose_edit();
    scanf("%d", &choice);
    while (1) {
        switch (choice) {
            case 1:
                input_new_balance(choosen_account(client, choice_type));
                break;
            case 2:
                input_entitled(client,choosen_account(client, choice_type));
                break;

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
    int choice_type;
    back:
    display_typeAccounts(client);
    scanf("%d", &choice_type);
    while (!in_1__nb_accounts(choice_type, nb_accounts(client))) {
        printf("unexistant choice !\n");
        printf("retry again\n");
        goto back;
    }
    Account temp;
    if (choice_type == 1) {
        temp = get_account(client);
        set_account(client, get_nextAccount(temp));
        free(temp);
    } else {
        if (choosen_account(client, choice_type) == get_lastAccount(get_account(client))) {
            free(get_lastAccount(get_account(client)));
        } else {
            Account a = choosen_account(client, choice_type - 1);
            temp = get_nextAccount(a);
            set_nextAccount(a, get_nextAccount(temp));
            free(temp);
        }
    }
}

/*
 *Add client
 */
void add_client(Client client) {
    FILE *fp;
    char *str = (char *) malloc(SIZE);
    input_perso_info(client);
    create_account(client);
    strcpy(str, "data/");
    strcat(get_id(client), ".csv");
    strcat(str, get_id(client));
    fp = fopen(str, "w");
    fprintf(fp, "DATE, OPERATION, AMOUNT, BALANCE");
    fclose(fp);
    printf("\nClient has been added. Come back to the administrator menu.\n");
}

/*
 *Edit the personal information of the client
 */
Client edit_perso_info_client(void) {
    char *id=malloc(SIZE);
    printf("\nEnter the client ID");
    scanf("%s",id);
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    //scanf("%d",idx);
    import_Client_idx_from_Json(id,idx);
    Client client=new_client();
    import_Client_from_Json(idx,client,nb_accounts);
    printf("\nChange the coordinates : loading...\n");
    free(get_perso_info(client));
    printf("\nthe coordinates has been edited. Come back to the administrator menu.\n");
    return client;
}


Client edit_client_coordonates(void){
    char *id=malloc(sizeof(char*));
    printf("\nEnter the client ID\n");
    scanf("%s",id);
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
        printf("ok");

    import_Client_idx_from_Json(id,idx);
    printf("ok");
    Client client=new_client();
    import_Client_from_Json(idx,client,nb_accounts);
    back:
    display_choose_coordonatesToEdit();
    int choice;
    while(scanf("%d",&choice)==0){
        printf("\nwrong choice, try again please!  \n");
        
    }
    switch (choice)
    {
        case 1 :
            input_mail(client);break;
        case 2 :
            input_phone(client);
            break;
        default:
            printf("unexistant choice !\n");
            printf("retry again\n");
            goto back;
    }
    return client;
}
/*
void admin_management_feature(Client client,Json_object json_clients){
    int choice;
    scanf("%d",choice);
    switch (choice)
    {
        case 1 :
            add_client(client);//Add new client
            add_client_json(client, json_clients);
            client = new_client();
            break;
        case 2 :

    
        default:
            break;
    }
}
*/