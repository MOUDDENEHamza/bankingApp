#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "struct.h"
#include "displayShell.h"
#include "input.h"
#include "json.h"
#include <json-c/json.h>

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



Client create_new_account(int *nb_accounts) {
    char *id=malloc(sizeof(char*));
    printf("\nEnter the client ID\n");
    scanf("%s",id);
    int *idx=malloc(sizeof(int));
    import_Client_idx_from_Json(id,idx);
    Client client=new_client();
    import_Client_from_Json(idx,client,nb_accounts);
    //printf("type cleint importes = %s\n",get_type(get_account(client)));
    //printf("type cleint importes = %s\n",get_type(get_nextAccount(get_account(client))));
    //printf("entitled cleint importes = %s\n",get_entitled(get_account(client)));
    //printf("nb_account = %d ",nb_accounts[0]);
    printf("\n\nchoose the type of account you want to create\n");
    printf("you have just to enter the number referenced! \n");
    display_choose_type();
    Client updated=input_add_account(client,nb_accounts);
    nb_accounts[0]++;
    //printf("ok\n  nb_accounts = %d",nb_accounts[0]);
    return updated;
}

/*
 *Create account to the client
 */


void display_accounts_list(void){
    char *id=malloc(sizeof(char*));
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    Client client=new_client();
    import_Client_idx_from_Json(id,idx);
    import_Client_from_Json(idx,client,nb_accounts);
    display_typeAccounts(client,nb_accounts);
}

void display_entiled(void) {
    char *id=malloc(sizeof(char*));
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    Client client=new_client();
    import_Client_idx_from_Json(id,idx);
    import_Client_from_Json(idx,client,nb_accounts);
    display_entitled(client,nb_accounts);
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
    //printf("ok");
    import_Client_idx_from_Json(id,idx);
    //printf("ok");
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


Json_object admin_delete_account(Client client, Json_object json_clients) {
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));

    int i, j;
    Account temp = get_account(client);
    struct json_object *json_client, *json_id, *json_passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    Json_object json_temp_clients = json_object_new_array();
    Json_object json_temp_client = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array();
    Json_object json_temp_account = json_object_new_object();
    size_t n_clients, n_accounts;
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    int choice;
    float init_balance = 0;

    printf("\nDelete an account\n");
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    import_Client_idx_from_Json(id,idx);
    import_Client_from_Json(idx,client,nb_accounts);
    Account *tabAccount=malloc(nb_accounts[0]*sizeof(Account));
    tabAccount[0]=new_account();
    tabAccount[0]=get_account(client);
    printf("balance 1 = %f\n",get_balance(tabAccount[0]));
    for(int j=1; j<nb_accounts[0]; j++){
        tabAccount[j]=new_account();
        tabAccount[j]=get_nextAccount(tabAccount[j-1]);
        printf("balance %d = %f\n",j+1,get_balance(tabAccount[j]));
    }
    printf("choose the acount you want to delete\n");
    int choice_type;
    back:
    display_typeAccounts(client,nb_accounts);
    if (scanf("%d", &choice_type)==0) {
        printf("unexistant choice !\n");
        printf("retry again\n");
        goto back;
    }
    int indextab=choice_type-1;

    n_clients = json_object_array_length(json_clients);
    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        if (strcmp(id, json_object_get_string(json_id)) == 0) {
            json_object_object_add(json_temp_client, "ID", json_object_new_string(get_id(client)));
            json_object_object_add(json_temp_client, "PASSWD", json_object_new_string(get_passwd(client)));
            json_object_object_add(json_temp_client, "LAST NAME",json_object_new_string(get_last_name(get_perso_info(client))));
            json_object_object_add(json_temp_client, "FIRST NAME",json_object_new_string(get_first_name(get_perso_info(client))));
            json_object_object_add(json_temp_client, "BIRTHDAY",json_object_new_string(get_birthday(get_perso_info(client))));
            json_object_object_add(json_temp_client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
            json_object_object_add(json_temp_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);
            for (j = 0; j < n_accounts; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                if (indextab!=(int)j) {
                    json_object_object_add(json_temp_account, "TYPE",json_object_new_string(get_type(tabAccount[j])));
                    json_object_object_add(json_temp_account, "ENTITLED",json_object_new_string(get_entitled(tabAccount[j])));
                    json_object_object_add(json_temp_account, "BALANCE",json_object_new_double(get_balance(tabAccount[j])));
                    json_object_array_add(json_temp_account_list, json_temp_account);
                    Json_object json_temp_account = json_object_new_object();
                }
            }
            json_object_object_add(json_temp_client, "ACCOUNT LIST", json_temp_account_list);
            json_object_array_add(json_temp_clients, json_temp_client);
        } else {
            json_object_array_add(json_temp_clients, json_client);
        }
    }

    printf("\nThe account has been deleted with success\n");
    printf("\nCome back the administrator menu\n");
    return json_temp_clients;
}


/*
 *Edit account to the client
 */
Json_object edit_account(Client client, Json_object json_clients) {
    char *id=malloc(sizeof(char*));
    int choice;
    int choice_type;
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    float new_balance;
    char * new_entitled=malloc(sizeof(char*));
    char * voidchar = "@@@@@@@@@@ void @@@@@@@@@@";
    int i, j;
    Account temp = get_account(client);
    struct json_object *json_client, *json_id, *json_passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone, *json_account_list, *json_account, *json_type, *json_entitled, *json_balance;
    Json_object json_temp_clients = json_object_new_array();
    Json_object json_temp_client = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array();
    Json_object json_temp_account = json_object_new_object();
    size_t n_clients, n_accounts;
    char  *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    float init_balance = 0;

    Account *tabAccount=malloc(nb_accounts[0]*sizeof(Account));
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    import_Client_idx_from_Json(id,idx);
    import_Client_from_Json(idx,client,nb_accounts);
    //printf("type nex = %s\n",get_type(get_nextAccount(get_account(client))));
    //printf("type nex = %f\n",get_balance(get_nextAccount(get_account(client))));

    printf("\n\tchoose the type of account you want to edit\n");
    back1:
    display_typeAccounts(client,nb_accounts);
    if (scanf("%d",&choice_type)==0) {
        printf("unexistant choice !\n");
        printf("retry again\n");
        choice_type=choice_type+1;
        goto back1;
    }
    int indextab = choice_type-1;

    back2:
    display_choose_edit();
    scanf("%d", &choice);
    tabAccount[0]=new_account();
    tabAccount[0]=get_account(client);
    printf("balance 1 = %f\n",get_balance(tabAccount[0]));
    for(int j=1; j<nb_accounts[0]; j++){
        tabAccount[j]=new_account();
        tabAccount[j]=get_nextAccount(tabAccount[j-1]);
        printf("balance %d = %f\n",j+1,get_balance(tabAccount[j]));
    }
    back:
        
    //printf("on est entré !!!\n");
    switch (choice) 
    {
        case 1:
            //set_entitled(updated,old_entitled);
            //printf("old balance = %f",old_balance);
            input_new_balance(tabAccount[choice_type-1]);
            printf("new balance = %f",get_balance(tabAccount[choice_type-1]));
            break;
        case 2:
            //set_balance(tabAccount[choice_type-1],&old_balance);
            //printf("old inttiled = %s",old_entitled);
            input_entitled(client,tabAccount[choice_type-1]);
            break;

        default:
            printf("unexistant choice !\n");
            printf("retry again\n");
            goto back2;
    }
    printf("on est entré !!!\n");
    printf("on est entré !!!%s\n",get_type(get_account(client)));
    printf("on est entré !!!%s\n",get_type(tabAccount[choice_type-1]));
    
    n_clients = json_object_array_length(json_clients);
    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        if (strcmp(id, json_object_get_string(json_id)) == 0) {
            json_object_object_add(json_temp_client, "ID", json_object_new_string(get_id(client)));
            json_object_object_add(json_temp_client, "PASSWD", json_object_new_string(get_passwd(client)));
            json_object_object_add(json_temp_client, "LAST NAME",json_object_new_string(get_last_name(get_perso_info(client))));
            json_object_object_add(json_temp_client, "FIRST NAME",json_object_new_string(get_first_name(get_perso_info(client))));
            json_object_object_add(json_temp_client, "BIRTHDAY",json_object_new_string(get_birthday(get_perso_info(client))));
            json_object_object_add(json_temp_client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
            json_object_object_add(json_temp_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));
            json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list);
            n_accounts = json_object_array_length(json_account_list);
            for (j = 0; j < nb_accounts[0]; j++) {
                json_account = json_object_array_get_idx(json_account_list, j);
                json_object_object_get_ex(json_account, "TYPE", &json_type);
                json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                if (n_accounts>0) {
                    json_object_object_add(json_temp_account, "TYPE",json_object_new_string(get_type(tabAccount[j])));
                    json_object_object_add(json_temp_account, "ENTITLED",json_object_new_string(get_entitled(tabAccount[j])));
                    json_object_object_add(json_temp_account, "BALANCE",json_object_new_double(get_balance(tabAccount[j])));
                    json_object_array_add(json_temp_account_list, json_temp_account);
                    Json_object json_temp_account = json_object_new_object();
                }
            }
            json_object_object_add(json_temp_client, "ACCOUNT LIST", json_temp_account_list);
            json_object_array_add(json_temp_clients, json_temp_client);
        } else {
            json_object_array_add(json_temp_clients, json_client);
        }
    }
    return  json_temp_clients;
}