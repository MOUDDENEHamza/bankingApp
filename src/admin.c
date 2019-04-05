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
    Account *tabAccount=malloc(choice_type*sizeof(Account));
    tabAccount[0]=new_account();
    tabAccount[0]=get_account(client);
    for(int cmpt=1; cmpt<choice_type; cmpt++){
        tabAccount[cmpt]=new_account();
        set_nextAccount(tabAccount[cmpt],tabAccount[cmpt-1]);
    }
}


Client create_new_account(int *nb_accounts) {
    char *id=malloc(sizeof(char*));
    printf("\nEnter the client ID\n");
    scanf("%s",id);
    int *idx=malloc(sizeof(int));
    import_Client_idx_from_Json(id,idx);
    Client client=new_client();
    import_Client_from_Json(idx,client,nb_accounts);
    printf("type cleint importes = %s\n",get_type(get_account(client)));
    printf("type cleint importes = %s\n",get_type(get_nextAccount(get_account(client))));
    printf("entitled cleint importes = %s\n",get_entitled(get_account(client)));
    printf("nb_account = %d ",nb_accounts[0]);
    printf("\n\nchoose the type of account you want to create\n");
    printf("you have just to enter the number referenced! \n");
    display_choose_type();
    Client updated=input_add_account(client,nb_accounts);
    nb_accounts[0]++;
    printf("ok\n  nb_accounts = %d",nb_accounts[0]);
    return updated;
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
Client edit_account(void) {
    char *id=malloc(sizeof(char*));
    int *choice=malloc(sizeof(int));
    int *choice_type=malloc(sizeof(int));
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    Client client=new_client();
    import_Client_idx_from_Json(id,idx);
    import_Client_from_Json(idx,client,nb_accounts);
    printf("type nex = %s\n",get_type(get_nextAccount(get_account(client))));
    printf("type nex = %f\n",get_balance(get_nextAccount(get_account(client))));
    printf("\n\tchoose the type of account you want to edit\n");
    back1:
    display_typeAccounts(client,nb_accounts);
    if (scanf("%d",choice_type)==0) {
        printf("unexistant choice !\n");
        printf("retry again\n");
        choice_type=choice_type+1;
        goto back1;
    }
    back2:
    display_choose_edit();
    scanf("%d", choice);
    Account *tabAccount=malloc(choice_type[0]*sizeof(Account));
    tabAccount[0]=new_account();
    tabAccount[0]=get_account(client);
    for(int cmpt=1; cmpt<choice_type[0]; cmpt++){
        tabAccount[cmpt]=new_account();
        set_nextAccount(tabAccount[cmpt],tabAccount[cmpt-1]);
    }
    switch (*choice) {
        case 1:
            input_new_balance(tabAccount[choice_type[0]-1]);
            break;
        case 2:
            input_entitled(client,tabAccount[choice_type[0]-1]);
            break;

        default:
            printf("unexistant choice !\n");
            printf("retry again\n");
            goto back2;
    }
    return client;
}

/*
 *delete account
 */
/*
C delete_account(char *id) {
    printf("choose the acount type you want to delete\n");
    int choice_type;
    back:
    display_typeAccounts(client,nb_accounts);
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

Client edit_client_coordonates(int *nb_accounts){
    char *id=malloc(sizeof(char*));
    printf("\nEnter the client ID\n");
    scanf("%s",id);
    int *idx=malloc(sizeof(int));
    printf("ok");
    import_Client_idx_from_Json(id,idx);
    printf("ok");
    Client client=new_client();
    import_Client_from_Json(idx,client,nb_accounts);
    back:
    display_choose_coordonatesToEdit();
    int *choice=malloc(sizeof(int));
    int valid = scanf("%d",choice);
    int *t;
    while(valid =0){
        printf("\nwrong choice, try again please!  \n");
        choice=choice+1;
        valid=scanf("%d",choice);
    }
    switch (*choice)
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
