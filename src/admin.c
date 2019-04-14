#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int format_birthday(char* birthday){
    int size = strlen(birthday);
    if(size!=10 || birthday[2]!='/' || birthday[5]!='/'){
        return 1;
    }
    else
    {
        int good_format = 0;
        int cmpt = 0;
        while(cmpt<10 && good_format == 0){
            if(cmpt!=2 && cmpt!=5){
                if(birthday[cmpt]-'0'<0 || birthday[cmpt]-'0'>9){
                    good_format = 1;
                }
            }
            cmpt++;
        }
        return good_format;
    }
}


char *str_sub (const char *s, unsigned int start, unsigned int end){
   char *new_s = NULL;

   if (s != NULL && start < end)
   {
/* (1)*/
      new_s = malloc (sizeof (*new_s) * (end - start + 2));
      if (new_s != NULL)
      {
         int i;

/* (2) */
         for (i = start; i <= end; i++)
         {
/* (3) */
            new_s[i-start] = s[i];
         }
         new_s[i-start] = '\0';
      }
      else
      {
         fprintf (stderr, "Memoire insuffisante\n");
         exit (EXIT_FAILURE);
      }
   }
   return new_s;
}


int str_istr (char *cs, char *ct){
   int index = -1;

   if (cs != NULL && ct != NULL)
   {
      char *ptr_pos = malloc(sizeof(char*));

      ptr_pos = strstr (cs, ct);
      if (ptr_pos != NULL)
      {
        index = ptr_pos - cs;
      }
   }
   return index;
}


int absolut_value(int *i){
    if(i[0]>0){
        return i[0];
    }
    else
    {
        return -i[0];
    }
    
}

char * get_civility_entitled(Client client){
    char* civility = malloc(sizeof(char*));
    char* entitled = get_entitled(get_account(client));
    char* sub_entitled = concatenate(concatenate(get_first_name(get_perso_info(client))," "),get_last_name(get_perso_info(client)));
    int idex = str_istr(entitled,sub_entitled);
    if (idex-5>=0) {
        if (entitled[idex-5]==0 || entitled[idex-5]=='M') {
            strcpy(civility,"Mrs.");
        }
        else{
            strcpy(civility,str_sub(entitled,idex-4,idex-1));       
        }
    }
    else
    {
        strcpy(civility,str_sub(entitled,idex-4,idex-1)); 
    }
    char* civility_entitled = concatenate(civility,sub_entitled);
    return civility_entitled;
}


void lldTochar(char *s){
    long long int t=(long long int)time(NULL)*100+rand()%100;
    char *tri=malloc(sizeof(long long int));
    sprintf(tri,"%lld",t);
    strcpy(s,tri);
}

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


Client* create_new_account(int *nb_accounts,int* nb_accounts_joint) {
    char *id=malloc(sizeof(char*));
    char *id_joint=malloc(sizeof(char*));
    back:
    printf("\nEnter the client ID\n");
    scanf("%s",id);
    int *idx=malloc(sizeof(int));
    int *idx_joint=malloc(sizeof(int));
    int n_clients=import_Client_idx_from_Json(id,idx);
    if (idx[0]>=n_clients) {
        display_unexistant_ID();
        goto back;
    }
    Client client=new_client();
    Client client_joint=new_client();
    Client temp_joint = new_client();
    import_Client_from_Json(idx,client,nb_accounts);
    printf("\n\nchoose the type of account you want to create\n");
    printf("you have just to enter the number referenced! \n");
    display_choose_type();
    Client updated=input_add_account(client);
    nb_accounts[0]++;
    
    if(strcmp(get_type(get_account(updated)),"JOINT")==0){
        back1:
        printf("\nyou are trying to create a new JOINT ACCOUNT for a client\nYou need to enter the client partner ID : ");
        scanf("%s",id_joint);
        printf("ok...");
        int nb_clents=import_Client_idx_from_Json(id_joint,idx_joint);
        if (idx_joint[0]>=nb_clents) {
            display_unexistant_ID();
            goto back1;
        }
        import_Client_from_Json(idx_joint,temp_joint,nb_accounts_joint);
        client_joint = input_add_account_joint(updated,temp_joint);
        nb_accounts_joint[0]++;
    }
    else
    {
        client_joint = NULL;
    }
    
    Client* tabClient = malloc(2*sizeof(Client));
    tabClient[0] = new_client();
    tabClient[1] = new_client();
    tabClient[0] = updated;
    tabClient[1] = client_joint;
    display_add_successfoul();
    return tabClient;
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

void display_accounts_list(void){
    char *id=malloc(sizeof(char*));
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    back:
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    Client client=new_client();
    int nb_clients=import_Client_idx_from_Json(id,idx);
    if (idx[0]>=nb_clients) {
        display_unexistant_ID();
        goto back;
    }
    import_Client_from_Json(idx,client,nb_accounts);
    display_typeAccounts(client,nb_accounts);
}

void display_entiled(void) {
    char *id=malloc(sizeof(char*));
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    back:
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    Client client=new_client();
    int nb_clients=import_Client_idx_from_Json(id,idx);
    if (idx[0]>=nb_clients) {
        display_unexistant_ID();
        goto back;
    }
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
    /*strcpy(str, "data/");
    strcat(get_id(client), ".csv");
    strcat(str, get_id(client));
    fp = fopen(str, "w");
    fprintf(fp, "DATE, OPERATION, AMOUNT, BALANCE");
    fclose(fp);
    printf("\nClient has been added. Come back to the administrator menu.\n");*/
}

Client add_client_and_joint(Client client, Client client_joint,int* nb_accounts){
    add_client(client);
    Client temp=new_client();
    Client client_joint1=new_client();
    int choice,nb_clients;
    char* choice_char = malloc(sizeof(char*));
    int *idx_joint = malloc(sizeof(int));
    char*id_joint = malloc(sizeof(char*));
    if (strcmp(get_type(get_account(client)),"JOINT")==0) {
        back:
        printf("\nEnter :\n1 if the client partner has already an account\n2 if he doesn't\nEnter your choice :");
        scanf("%s",choice_char);
        choice = atoi(choice_char);
        switch (choice)
        {
            case 1 :
                back1:
                printf("\nEnter the client partner id : ");
                scanf("%s",id_joint);
                nb_clients=import_Client_idx_from_Json(id_joint,idx_joint);
                if (idx_joint[0]>=nb_clients) {
                    display_unexistant_ID();
                    goto back1;
                }
                
                import_Client_from_Json(idx_joint,temp,nb_accounts);
                client_joint1 = input_add_account_joint(client,temp);
                nb_accounts[0]++;
                break;
            case 2 :
                printf("\nnow we are adding the client partber ...\n");
                input_perso_info(client_joint1);
                set_account(client_joint1,get_account(client));
                input_entitled_joint(client,client_joint1);
                nb_accounts[0]=1;
                break;
        
            default:
                display_wrong();
                goto back;
                break;
        }
        client_joint = client_joint1;
        display_add_client_successfoul();
        return client_joint;
    }
    else
    {
        free(client_joint);
        display_add_client_successfoul();
        return NULL;
    }
}


Client edit_client_coordonates(int *nb_accounts){
    char *id=malloc(sizeof(char*));
    int *idx=malloc(sizeof(int));
    int choice,nb_clients;
    char* choice_char=malloc(sizeof(char*));
    Client client=new_client();
    back0:
    printf("\nEnter the client ID\n");
    scanf("%s",id);
    nb_clients=import_Client_idx_from_Json(id,idx);
    if (idx[0]<nb_clients) {
        import_Client_from_Json(idx,client,nb_accounts);
        back1:
        display_choose_coordonatesToEdit();
        scanf("%s",choice_char);
        choice = atoi(choice_char);
        switch (choice)
        {
            case 1 :
                input_mail(client);break;
            case 2 :
                input_phone(client);
                break;
            default:
                display_wrong();
                goto back1;
        }
    }
    else
    {
        display_unexistant_ID();
        goto back0;
    }
    display_edit_succesfoul();
    return client;
}


Json_object admin_delete_account(Client client, Json_object json_clients) {
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    int i, j;
    Account temp = get_account(client);
    struct json_object *json_client, *json_id, *json_passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone, *json_account_list, *json_account_list_joint, *json_account, *json_ida, *json_type, *json_entitled, *json_balance;
    Json_object json_temp_clients = json_object_new_array();
    Json_object json_temp_client = json_object_new_object();
    Json_object json_temp_client_joint = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array();
    Json_object json_temp_account_list_joint = json_object_new_array();
    Json_object json_temp_account = json_object_new_object();
    Json_object json_temp_account_joint = json_object_new_object();
    size_t n_clients, n_accounts;
    n_clients = json_object_array_length(json_clients);
    char *id = (char *) malloc(SIZE), *type = (char *) malloc(SIZE), *entitled = (char *) malloc(SIZE);
    int choice_type,indextab;
    char * voidchar = "@@@@@@@@@@ void @@@@@@@@@@";
    float init_balance = 0;

    printf("\nDelete an account\n");
    back0:
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    import_Client_idx_from_Json(id,idx);
    import_Client_from_Json(idx,client,nb_accounts);
    Account *tabAccount=malloc(absolut_value(nb_accounts)*sizeof(Account));
    if (idx[0]<n_clients) {
        tabAccount[0]=new_account();
        tabAccount[0]=get_account(client);
        printf("balance 1 = %f\n",get_balance(tabAccount[0]));
        for(int j=1; j<nb_accounts[0]; j++){
            tabAccount[j]=new_account();
            tabAccount[j]=get_nextAccount(tabAccount[j-1]);
            printf("balance %d = %f\n",j+1,get_balance(tabAccount[j]));
        }
        
        if(nb_accounts[0]>0){
            char* choice_type_char;
            int cmpt;
            printf("choose the acount you want to delete\n");
            back1:
            choice_type_char = malloc(sizeof(char*));
            display_typeAccounts(client,nb_accounts);
            scanf("%s", choice_type_char);
            choice_type = atoi(choice_type_char);
            cmpt=1;
            while (cmpt<=nb_accounts[0] && cmpt!=choice_type) {
                cmpt++;
            }
            if (cmpt==nb_accounts[0]+1) {
                display_wrong();
                goto back1;
            }
            indextab=choice_type-1;
        }
        else
        {
            indextab=0;
        }
    }
    else
    {
        display_unexistant_ID();
        goto back0;
    }

    Client client_joint=new_client();
    char* id_joint=malloc(sizeof(char*));
    int* idx_joint=malloc(sizeof(int));
    int* idx_ida_joint=malloc(sizeof(int));
    int *nb_accounts_joint=malloc(sizeof(int));
    
    
    if(strcmp(get_type(tabAccount[choice_type-1]),"JOINT")==0){
        import_idx_from_json_with_IDA(get_id(client),get_ida(tabAccount[choice_type-1]),idx_joint,idx_ida_joint);
        printf("\nidx_joint=%d\nidx_ida_joint=%d\n",idx_joint[0],idx_ida_joint[0]);
        import_Client_from_Json(idx_joint,client_joint,nb_accounts_joint);
        printf("\ntype = %s\n",get_type(get_account(client_joint)));
    }
    else
    {
        set_id(client_joint,voidchar);
        idx_joint[0]=-1;
        idx_ida_joint[0]=-1;
    }
    Account* tabAccount_joint = malloc(absolut_value(nb_accounts_joint)*sizeof(Account));
    tabAccount_joint[0]=new_account();
    tabAccount_joint[0]=get_account(client_joint);
    printf("balance 1 = %f\n",get_balance(tabAccount_joint[0]));
    for(int j=1; j<nb_accounts[0]; j++){
        tabAccount_joint[j]=new_account();
        tabAccount_joint[j]=get_nextAccount(tabAccount_joint[j-1]);
        //printf("balance %d = %f\n",j+1,get_balance(tabAccount_joint[j]));
    }
    printf("\nok...\n");

    for (i = 0; i < n_clients; i++) {
        json_client = json_object_array_get_idx(json_clients, i);
        json_object_object_get_ex(json_client, "ID", &json_id);
        printf("\nok...\n");
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
            if(n_accounts>0){
                for (j = 0; j < n_accounts; j++) {
                    json_account = json_object_array_get_idx(json_account_list, j);
                    json_object_object_get_ex(json_account, "IDA", &json_ida);
                    json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                    json_object_object_get_ex(json_account, "TYPE", &json_type);
                    json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                    if (indextab!=(int)j) {
                        json_object_object_add(json_temp_account, "IDA",json_object_new_string(get_ida(tabAccount[j])));
                        json_object_object_add(json_temp_account, "ENTITLED",json_object_new_string(get_entitled(tabAccount[j])));
                        json_object_object_add(json_temp_account, "TYPE",json_object_new_string(get_type(tabAccount[j])));
                        json_object_object_add(json_temp_account, "BALANCE",json_object_new_double(get_balance(tabAccount[j])));
                        json_object_array_add(json_temp_account_list, json_temp_account);
                        Json_object json_temp_account = json_object_new_object();
                    }
                }
            }
            json_object_object_add(json_temp_client, "ACCOUNT LIST", json_temp_account_list);
            json_object_array_add(json_temp_clients, json_temp_client);
        }
        else {
            if (strcmp(get_id(client_joint), json_object_get_string(json_id)) == 0) {
                json_object_object_add(json_temp_client_joint, "ID", json_object_new_string(get_id(client_joint)));
                json_object_object_add(json_temp_client_joint, "PASSWD", json_object_new_string(get_passwd(client_joint)));
                json_object_object_add(json_temp_client_joint, "LAST NAME",json_object_new_string(get_last_name(get_perso_info(client_joint))));
                json_object_object_add(json_temp_client_joint, "FIRST NAME",json_object_new_string(get_first_name(get_perso_info(client_joint))));
                json_object_object_add(json_temp_client_joint, "BIRTHDAY",json_object_new_string(get_birthday(get_perso_info(client_joint))));
                json_object_object_add(json_temp_client_joint, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client_joint)))));
                json_object_object_add(json_temp_client_joint, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client_joint)))));
                json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list_joint);
                n_accounts = json_object_array_length(json_account_list_joint);
                if(n_accounts>0){
                    for (j = 0; j < n_accounts; j++) {
                        json_account = json_object_array_get_idx(json_account_list_joint, j);
                        json_object_object_get_ex(json_account, "IDA", &json_ida);
                        json_object_object_get_ex(json_account, "ENTITLED", &json_entitled);
                        json_object_object_get_ex(json_account, "TYPE", &json_type);
                        json_object_object_get_ex(json_account, "BALANCE", &json_balance);
                        if (idx_ida_joint[0]!=(int)j) {
                            json_object_object_add(json_temp_account_joint, "IDA",json_object_new_string(get_ida(tabAccount_joint[j])));
                            json_object_object_add(json_temp_account_joint, "ENTITLED",json_object_new_string(get_entitled(tabAccount_joint[j])));
                            json_object_object_add(json_temp_account_joint, "TYPE",json_object_new_string(get_type(tabAccount_joint[j])));
                            json_object_object_add(json_temp_account_joint, "BALANCE",json_object_new_double(get_balance(tabAccount_joint[j])));
                            json_object_array_add(json_temp_account_list_joint, json_temp_account_joint);
                            Json_object json_temp_account = json_object_new_object();
                        }
                    }
                }
                json_object_object_add(json_temp_client_joint, "ACCOUNT LIST", json_temp_account_list_joint);
                json_object_array_add(json_temp_clients, json_temp_client_joint);
            }
            else{
                json_object_array_add(json_temp_clients, json_client);
            }   
        }
    }
    if(nb_accounts[0]>0){
        display_delet_successfoul();
    }
    else
    {
        display_no_account();
    }
    printf("\nCome back the administrator menu\n");
    return json_temp_clients;
}


/*
 *Edit account to the client
 */
Json_object edit_account(Client client, Json_object json_clients) {
    char *id=malloc(sizeof(char*));
    int choice, choice_type;
    int *idx=malloc(sizeof(int));
    int *nb_accounts=malloc(sizeof(int));
    char * new_entitled=malloc(sizeof(char*));
    char * voidchar = "@@@@@@@@@@ void @@@@@@@@@@";
    int i, j;
    struct json_object *json_client, *json_id, *json_passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone, *json_account_list, *json_account_list_joint, *json_account, *json_ida, *json_type, *json_entitled, *json_balance;
    Json_object json_temp_clients = json_object_new_array();
    Json_object json_temp_client = json_object_new_object();
    Json_object json_temp_client_joint = json_object_new_object();
    Json_object json_temp_account_list = json_object_new_array();
    Json_object json_temp_account_list_joint = json_object_new_array();
    Json_object json_temp_account = json_object_new_object();
    Json_object json_temp_account_joint = json_object_new_object();

    size_t n_clients, n_accounts;
    n_clients = json_object_array_length(json_clients);
    char  *type = malloc(sizeof(char*)) , *entitled = malloc(sizeof(char*));
    Account *tabAccount=malloc(absolut_value(nb_accounts)*sizeof(Account));

    back0:
    printf("\nEnter the client ID  :");
    scanf("%s",id);
    printf("\nok...\n");
    import_Client_idx_from_Json(id,idx);
    printf("\nok...\n");
    if (idx[0]<n_clients) {
        import_Client_from_Json(idx,client,nb_accounts);
        tabAccount[0]=new_account();
        tabAccount[0]=get_account(client);
        for(int j=1; j<nb_accounts[0]; j++){
            tabAccount[j]=new_account();
            tabAccount[j]=get_nextAccount(tabAccount[j-1]);
        }

        if(nb_accounts[0]>0){
            int cmpt;
            char* choice_char;
            char* choice_type_char;
            printf("\n\tchoose the type of account you want to edit\n");
            back1:
            choice_type_char = malloc(sizeof(char*));
            display_typeAccounts(client,nb_accounts);
            scanf("%s",choice_type_char);
            choice_type = atoi(choice_type_char);
            cmpt=1;
            while (cmpt<=nb_accounts[0] && cmpt!=choice_type) {
                cmpt++;
            }
            if (cmpt==nb_accounts[0]+1) {
                display_wrong();
                goto back1;
            }

            back2:
            choice_char = malloc(sizeof(char*));
            display_choose_edit();
            scanf("%s", choice_char);
            choice = atoi(choice_char);     
            switch (choice) 
            {
                case 1:
                    input_new_balance(tabAccount[choice_type-1]);
                    printf("new balance = %f",get_balance(tabAccount[choice_type-1]));
                    break;
                case 2:
                    input_entitled(client,tabAccount[choice_type-1]);
                    break;

                default:
                    display_wrong();
                    goto back2;
            }
        }
        else{
            display_no_account();
        }
    }
    else
    {
        display_unexistant_ID();
        goto  back0;
    }

    Client client_joint=new_client();
    char* id_joint=malloc(sizeof(char*));
    int* idx_joint=malloc(sizeof(int));
    int* idx_ida_joint=malloc(sizeof(int));
    int *nb_accounts_joint=malloc(sizeof(int));

    if(strcmp(get_type(tabAccount[choice_type-1]),"JOINT")==0){
        import_idx_from_json_with_IDA(get_id(client),get_ida(tabAccount[choice_type-1]),idx_joint,idx_ida_joint);
        printf("\nidx_joint=%d\nidx_ida_joint=%d\n",idx_joint[0],idx_ida_joint[0]);
        import_Client_from_Json(idx_joint,client_joint,nb_accounts_joint);
        printf("\ntype = %s\n",get_type(get_account(client_joint)));
    }
    else
    {
        set_id(client_joint,voidchar);
        idx_joint[0]=-1;
        idx_ida_joint[0]=-1;
    }


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
            if (n_accounts>0) {
                json_object_object_add(json_temp_account, "IDA",json_object_new_string(get_ida(tabAccount[choice_type-1])));
                json_object_object_add(json_temp_account, "ENTITLED",json_object_new_string(get_entitled(tabAccount[choice_type-1])));
                json_object_object_add(json_temp_account, "TYPE",json_object_new_string(get_type(tabAccount[choice_type-1])));
                json_object_object_add(json_temp_account, "BALANCE",json_object_new_double(get_balance(tabAccount[choice_type-1])));
                json_object_array_add(json_temp_account_list, json_temp_account);
                json_object_array_put_idx(json_account_list,choice_type-1,json_temp_account);
                Json_object json_temp_account = json_object_new_object();
            }
            json_object_object_add(json_temp_client, "ACCOUNT LIST", json_account_list);
            json_object_array_add(json_temp_clients, json_temp_client);
        }
        else {
            if (strcmp(get_id(client_joint),json_object_get_string(json_id))==0) {
                json_object_object_add(json_temp_client_joint, "ID", json_object_new_string(get_id(client_joint)));
                json_object_object_add(json_temp_client_joint, "PASSWD", json_object_new_string(get_passwd(client_joint)));
                json_object_object_add(json_temp_client_joint, "LAST NAME",json_object_new_string(get_last_name(get_perso_info(client_joint))));
                json_object_object_add(json_temp_client_joint, "FIRST NAME",json_object_new_string(get_first_name(get_perso_info(client_joint))));
                json_object_object_add(json_temp_client_joint, "BIRTHDAY",json_object_new_string(get_birthday(get_perso_info(client_joint))));
                json_object_object_add(json_temp_client_joint, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client_joint)))));
                json_object_object_add(json_temp_client_joint, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client_joint)))));
                json_object_object_get_ex(json_client, "ACCOUNT LIST", &json_account_list_joint);
                n_accounts = json_object_array_length(json_account_list_joint);
                if (n_accounts>0) {
                    json_object_object_add(json_temp_account_joint, "IDA",json_object_new_string(get_ida(tabAccount[choice_type-1])));
                    json_object_object_add(json_temp_account_joint, "ENTITLED",json_object_new_string(get_entitled(tabAccount[choice_type-1])));
                    json_object_object_add(json_temp_account_joint, "TYPE",json_object_new_string(get_type(tabAccount[choice_type-1])));
                    json_object_object_add(json_temp_account_joint, "BALANCE",json_object_new_double(get_balance(tabAccount[choice_type-1])));
                    json_object_array_add(json_temp_account_list_joint, json_temp_account_joint);
                    json_object_array_put_idx(json_account_list_joint,*idx_ida_joint,json_temp_account_joint);
                    Json_object json_temp_account_joint = json_object_new_object();
                }
                json_object_object_add(json_temp_client_joint, "ACCOUNT LIST", json_account_list_joint);
                json_object_array_add(json_temp_clients, json_temp_client_joint);
            }
            else{
                json_object_array_add(json_temp_clients, json_client);
            }   
        }
    }
    if (n_accounts>0) {
        display_edit_succesfoul();
    }
    return  json_temp_clients;
}

Json_object edit_account_and_joint(Client client,Json_object json_clients){
    json_clients = edit_account(client,json_clients);
}
