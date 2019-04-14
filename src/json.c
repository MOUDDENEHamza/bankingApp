#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"
#include "admin.h"

#define BUFFER 4096

/*
 * Update json file
 */
void write_file(Json_object json_object, Json_object json_clients) {
    FILE *fp;
    if (json_clients == NULL) {
        return;
    }
    json_object_object_add(json_object, "CLIENTS", json_clients);
    fp = fopen("data/account_list.json", "w");
    fwrite(json_object_get_string(json_object), strlen(json_object_get_string(json_object)), 1, fp);
    fclose(fp);
}

/*
 * Add data client to json file
 */
void add_client_json(Client client, Json_object json_clients) {
    size_t n_account;
    Account a = get_account(client);
    Json_object json_client = json_object_new_object();
    Json_object json_account_list = json_object_new_array();
    Json_object json_account = json_object_new_object();
    json_object_object_add(json_client, "ID", json_object_new_string(get_id(client)));
    json_object_object_add(json_client, "PASSWD", json_object_new_string(get_passwd(client)));
    json_object_object_add(json_client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(client))));
    json_object_object_add(json_client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(client))));
    json_object_object_add(json_client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(client))));
    json_object_object_add(json_client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
    json_object_object_add(json_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));

    json_object_object_add(json_account, "IDA", json_object_new_string(get_ida(a)));
    json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(a)));
    json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(a)));
    json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(a)));
    json_object_array_add(json_account_list, json_account);
    json_account = json_object_new_object();

    json_object_object_add(json_client, "ACCOUNT LIST", json_account_list);
    json_object_array_add(json_clients, json_client);
}



void modify_client(Client client, Json_object json_clients,int *nb_acc){
    if(client!=NULL){
        int *idx=malloc(sizeof(int));
        import_Client_idx_from_Json(get_id(client),idx);
        size_t n_account;
        if(nb_acc[0]<0){
            n_account=0;
        }
        else
        {
            n_account=nb_acc[0];
        }
        Json_object json_client = json_object_new_object();
        Json_object json_account_list = json_object_new_array();
        Json_object json_account = json_object_new_object();
        json_object_object_add(json_client, "ID", json_object_new_string(get_id(client)));
        json_object_object_add(json_client, "PASSWD", json_object_new_string(get_passwd(client)));
        json_object_object_add(json_client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(client))));
        json_object_object_add(json_client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(client))));
        json_object_object_add(json_client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(client))));
        json_object_object_add(json_client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
        json_object_object_add(json_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));
        if(nb_acc[0]>0){
            Account *tabAccount=malloc(absolut_value(nb_acc)*sizeof(Account));
            tabAccount[0]=new_account();
            tabAccount[0]= get_account(client);
            for(int cmpt=1; cmpt<nb_acc[0]; cmpt++){
                tabAccount[cmpt]=new_account();
                tabAccount[cmpt]=get_nextAccount(tabAccount[cmpt-1]);
            }
            for (int cmpt=0; cmpt < n_account; cmpt++) {
                json_object_object_add(json_account, "IDA", json_object_new_string(get_ida(tabAccount[cmpt])));
                json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(tabAccount[cmpt])));
                json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(tabAccount[cmpt])));
                json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(tabAccount[cmpt])));
                json_object_array_add(json_account_list, json_account);
                json_account = json_object_new_object();
            }
            json_object_object_add(json_client, "ACCOUNT LIST", json_account_list);
        }
        json_object_array_put_idx(json_clients, *idx, json_client);
    }
}


/*
 * Parse the json file containing the client data
 */
Json_object parse_json(void) {
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER);
    char str_id[64], str_passwd[64], str_last_name[64], str_first_name[64], str_birthday[64], str_mail[64], str_phone[64];
    struct json_object *parsed_json;
    struct json_object *clients;
    struct json_object *client;
    struct json_object *id, *passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone;
    size_t n_clients;
    size_t i;

    fp = fopen("data/account_list.json", "r");
    fread(buffer, BUFFER, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);

    for (i = 0; i < n_clients; i++) {
        client = json_object_array_get_idx(clients, i);
    }
    return clients;
}


int import_Client_idx_from_Json(char* id, int* idx){
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER);
    struct json_object *parsed_json;
    struct json_object *clients;
    struct json_object *client;
    struct json_object *id_json;
    size_t n_clients;
    size_t i;

    fp = fopen("data/account_list.json", "r");
    fread(buffer, BUFFER, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);

    int cmpt=0;
    int mybool=1;
    i=0;
    idx[0]=0;
    while(cmpt < n_clients && mybool==1){
        client = json_object_array_get_idx(clients, i);
        json_object_object_get_ex(client, "ID", &id_json);
        if(strcmp(json_object_get_string(id_json),id)==0){
            mybool=0;
        }
        else
        {
            idx[0]++;
        }
        cmpt++;
        i++;
    }
    return (int)n_clients;
}

int import_idx_from_json_with_IDA(char* id_client,char* ida,int*idx,int *idx_ida){
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER);
    struct json_object *parsed_json;
    struct json_object *clients;
    struct json_object *client;
    struct json_object *account_list_json;
    struct json_object *account_json;
    struct json_object *id_json;
    struct json_object *ida_json;
    size_t n_clients,n_accounts;
    size_t i,j;

    fp = fopen("data/account_list.json", "r");
    fread(buffer, BUFFER, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);

    int cmpt=0;
    int cmpt2;
    int mybool=1;
    
    i=0;
    idx[0]=0;
    while(cmpt < n_clients && mybool==1){
        client = json_object_array_get_idx(clients, i);
        json_object_object_get_ex(client, "ID", &id_json);
        json_object_object_get_ex(client, "ACCOUNT LIST", &account_list_json);
        n_accounts = json_object_array_length(account_list_json);
        cmpt2=0;
        int mybool2=1;
        j=0;
        idx_ida[0]=0;
        if(strcmp(id_client,json_object_get_string(id_json))!=0){
            while(cmpt2 < n_accounts && mybool2==1){
                account_json = json_object_array_get_idx(account_list_json,j);
                json_object_object_get_ex(account_json,"IDA",&ida_json);
                if(strcmp(json_object_get_string(ida_json),ida)==0){
                    mybool2=0;
                }
                else
                {
                    idx_ida[0]++;
                }
            cmpt2++;
            }
        }
        mybool=mybool2;
        if(mybool!=0)
        {
            idx[0]++;
        }
        cmpt++;
        i++;
    }
    return (int)n_clients;
}



void import_Client_from_Json(int *idx, Client client_imported, int *nbAcc){
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER);
    struct json_object *parsed_json;
    struct json_object *clients;
    struct json_object *client;
    struct json_object *id_json;
    struct json_object *pwd_json;
    struct json_object *lname_json;
    struct json_object *fname_json;
    struct json_object *bday_json;
    struct json_object *email_json;
    struct json_object *phon_json;
    struct json_object *account_list_json;
    struct json_object *account;
    struct json_object *ida_json;
    struct json_object *type_json;
    struct json_object *entitled_json; 
    struct json_object *balance_json;
    float* bal=malloc(sizeof(float));
    size_t n_clients;
    size_t i,j;
    size_t n_accounts;

    fp = fopen("data/account_list.json", "r");
    fread(buffer, BUFFER, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);
    i=(const int)idx[0];
    client = json_object_array_get_idx(clients, i);
    json_object_object_get_ex(client, "ID", &id_json);
    json_object_object_get_ex(client, "PASSWD", &pwd_json);
    json_object_object_get_ex(client, "LAST NAME", &lname_json);
    json_object_object_get_ex(client, "FIRST NAME", &fname_json);
    json_object_object_get_ex(client, "BIRTHDAY", &bday_json);
    json_object_object_get_ex(client, "EMAIL", &email_json);
    json_object_object_get_ex(client, "PHONE", &phon_json);
    json_object_object_get_ex(client, "ACCOUNT LIST", &account_list_json);
    n_accounts = json_object_array_length(account_list_json);
    nbAcc[0]=(int)n_accounts;
    if(nbAcc[0]>0){
        Account *tabAccount=malloc(nbAcc[0]*sizeof(Account));
        tabAccount[0]=new_account();
        tabAccount[0]=get_account(client_imported);
        for(int cmpt=1; cmpt<nbAcc[0]; cmpt++){
            tabAccount[cmpt]=new_account();
            set_nextAccount(tabAccount[cmpt-1],tabAccount[cmpt]);
        }
        int j1;
        for(j=0; j<=n_accounts-1; j++){
            j1=(int)j;
            account = json_object_array_get_idx(account_list_json,j);
            json_object_object_get_ex(account, "IDA" , &ida_json);
            set_ida(tabAccount[j1],(char*)json_object_get_string(ida_json));
            json_object_object_get_ex(account, "TYPE" , &type_json);
            set_type(tabAccount[j1],(char*)json_object_get_string(type_json));
            json_object_object_get_ex(account, "ENTITLED" , &entitled_json);
            set_entitled(tabAccount[j1],(char*)json_object_get_string(entitled_json));
            json_object_object_get_ex(account, "BALANCE" , &balance_json);
            *bal=(float)json_object_get_double(balance_json);
            set_balance(tabAccount[j1],bal);
        }
    }
    else
    {
        nbAcc[0]=-1;
        char * voidchar = "@@@@@@@@@@ void @@@@@@@@@@";
        //long long int voidida = 0;
        //set_id_account(get_account(client_imported),voidida);
        set_type(get_account(client_imported),voidchar);
        set_entitled(get_account(client_imported),voidchar);
    }
    set_id(client_imported,(char*)json_object_get_string(id_json));
    set_passwd(client_imported,(char*)json_object_get_string(pwd_json));
    Perso_info p=new_perso_info();
    set_last_name(p,(char*)json_object_get_string(lname_json));
    set_first_name(p,(char*)json_object_get_string(fname_json));
    set_birthday(p,(char*)json_object_get_string(bday_json));
    set_perso_info(client_imported,p);
    Coordinates c=new_coordinates();
    set_mail(c,(char*)json_object_get_string(email_json));
    set_phone(c,(char*)json_object_get_string(phon_json));
    set_coordinates(p,c);
    set_perso_info(client_imported,p);
}

void import_Account_from_Json(int *idx, Account* tabAccount){
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER);
    struct json_object *parsed_json;
    struct json_object *clients;
    struct json_object *client;
    struct json_object *id_json;
    struct json_object *account_list_json;
    struct json_object *account;
    struct json_object *ida_json;
    struct json_object *type_json;
    struct json_object *entitled_json; 
    struct json_object *balance_json;
    float* bal=malloc(sizeof(float));
    size_t n_clients;
    size_t i,j;
    size_t n_accounts;

    fp = fopen("data/account_list.json", "r");
    fread(buffer, BUFFER, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);
    i=(const int)idx[0];
    client = json_object_array_get_idx(clients, i);
    json_object_object_get_ex(client, "ACCOUNT LIST", &account_list_json);
    n_accounts = json_object_array_length(account_list_json);
    int j1;
    for(j=0; j<=n_accounts-1; j++){
        j1=(int)j;
        account = json_object_array_get_idx(account_list_json,j);
        json_object_object_get_ex(account, "IDA" , &ida_json);
        set_ida(tabAccount[j1],(char*)json_object_get_string(ida_json));
        json_object_object_get_ex(account, "TYPE" , &type_json);
        set_type(tabAccount[j1],(char*)json_object_get_string(type_json));
        json_object_object_get_ex(account, "ENTITLED" , &entitled_json);
        set_entitled(tabAccount[j1],(char*)json_object_get_string(entitled_json));
        json_object_object_get_ex(account, "BALANCE" , &balance_json);
        *bal=(float)json_object_get_double(balance_json);
        set_balance(tabAccount[j1],bal);
    }
}
