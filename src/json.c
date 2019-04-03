#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
#include "json.h"
#include "struct.h"

#define BUFFER 4096

/*
 * Update json file
 */
void write_file(Json_object json_object, Json_object json_clients) {
    FILE *fp;
    //printf("%s\n", json_object_get_string(json_clients));
    if (json_clients == NULL) {
        return;
    }
    json_object_object_add(json_object, "CLIENTS", json_clients);
    fp = fopen("data/account_list.json", "w");
    //printf("%s\n", json_object_get_string(json_object));
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
    while (a != NULL) {
        json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(a)));
        json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(a)));
        json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(a)));
        json_object_array_add(json_account_list, json_account);
        a = get_nextAccount(a);
        json_account = json_object_new_object();
    }
    json_object_object_add(json_client, "ACCOUNT LIST", json_account_list);
    //printf("%s\n", json_object_to_json_string(json_client));
    json_object_array_add(json_clients, json_client);
    //printf("%s\n", json_object_to_json_string(json_clients));
}

void modify_client(Client client, Json_object json_clients){
    size_t n_account;
    Account a = get_account(client);
    Json_object json_client = json_object_new_object();
    Json_object json_account_list = json_object_new_array();
    Json_object json_account = json_object_new_object();
    int idx = import_Client_idx_from_Json(get_id(client));
    json_object_object_add(json_client, "ID", json_object_new_string(get_id(client)));
    json_object_object_add(json_client, "PASSWD", json_object_new_string(get_passwd(client)));
    json_object_object_add(json_client, "LAST NAME", json_object_new_string(get_last_name(get_perso_info(client))));
    json_object_object_add(json_client, "FIRST NAME", json_object_new_string(get_first_name(get_perso_info(client))));
    json_object_object_add(json_client, "BIRTHDAY", json_object_new_string(get_birthday(get_perso_info(client))));
    json_object_object_add(json_client, "EMAIL",json_object_new_string(get_mail(get_coordinates(get_perso_info(client)))));
    json_object_object_add(json_client, "PHONE",json_object_new_string(get_phone(get_coordinates(get_perso_info(client)))));
    while (a != NULL) {
        json_object_object_add(json_account, "ENTITLED", json_object_new_string(get_entitled(a)));
        json_object_object_add(json_account, "TYPE", json_object_new_string(get_type(a)));
        json_object_object_add(json_account, "BALANCE", json_object_new_double(get_balance(a)));
        json_object_array_add(json_account_list, json_account);
        a = get_nextAccount(a);
        json_account = json_object_new_object();
    }
    json_object_object_add(json_client, "ACCOUNT LIST", json_account_list);
    //printf("%s\n", json_object_to_json_string(json_client));
    json_object_array_put_idx(json_clients, idx, json_client);
    //printf("%s\n", json_object_to_json_string(json_clients));
}


/*
 * Parse the json file containing the client data
 */
Json_object parse_json(void) {
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER);
    char str_id[64], str_passwd[64], str_last_name[64], str_first_name[64], str_birthday[64], str_mail[64], str_phone[64];
    struct json_object *parsed_json=malloc(sizeof(struct json_object *));
    struct json_object *clients=malloc(sizeof(struct json_object *));
    struct json_object *client=malloc(sizeof(struct json_object *));
    struct json_object *id, *passwd, *last_name, *fist_name, *first_name, *birthday, *mail, *phone;
    size_t n_clients;
    size_t i;

    fp = fopen("data/account_list.json", "r");
    fread(buffer, BUFFER, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);
    //printf("Found %lu clients\n", n_clients);

    for (i = 0; i < n_clients; i++) {
        client = json_object_array_get_idx(clients, i);
        //printf("%s\n", json_object_get_string(client));
    }
    //printf("%s\n", json_object_get_string(clients));
    //printf("%s\n", json_object_get_string(parsed_json));
    return clients;
}


int import_Client_idx_from_Json(char* ID){
    FILE *fp;
    char *buffer = (char *) malloc(BUFFER);
    struct json_object *parsed_json=malloc(sizeof(struct json_object *));
    struct json_object *clients=malloc(sizeof(struct json_object *));
    struct json_object *client=malloc(sizeof(struct json_object *));
    struct json_object *id_json=malloc(sizeof(struct json_object *));
    struct json_object *account_list=malloc(sizeof(struct json_object *));

    size_t n_clients;
    size_t i;
    fp = fopen("data/account_list.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    n_clients = json_object_array_length(clients);
    int idx=0;
    const char* IDS=ID;
    for(i=0; i < n_clients; i++){
        client = json_object_array_get_idx(clients, i);
        json_object_object_get_ex(client, "ID", &id_json);
        const char* id=json_object_get_string(id_json);
        int j=0;
        if(strlen(id)!=strlen(ID)){
            return -1;
        }
        else
        {
            while(j<strlen(id) && id[j]==ID[j]){
                j++;
            }
            if(j==strlen(id)){
                break;
            }
            else
            {
                idx++;
            }
            return idx;
        }
        
        
    }
}



Client import_Client_from_Json(int idx){
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json=malloc(sizeof(struct json_object *));
    struct json_object *clients=malloc(sizeof(struct json_object *));
    struct json_object *client=malloc(sizeof(struct json_object *));
    struct json_object *id_json=malloc(sizeof(struct json_object *));
    struct json_object *pwd_json=malloc(sizeof(struct json_object *));
    struct json_object *lname_json=malloc(sizeof(struct json_object *));
    struct json_object *fname_json=malloc(sizeof(struct json_object *));
    struct json_object *bday_json=malloc(sizeof(struct json_object *));
    struct json_object *email_json=malloc(sizeof(struct json_object *));
    struct json_object *phon_json=malloc(sizeof(struct json_object *));
    struct json_object *account_list_json=malloc(sizeof(struct json_object *));
    struct json_object *type_json=malloc(sizeof(struct json_object *));
    struct json_object *entitled_json=malloc(sizeof(struct json_object *));
    struct json_object *balance_json=malloc(sizeof(struct json_object *));

    
    Client client_imported = new_client();
    size_t n_clients;
    size_t i=idx;
    fp = fopen("data/account_list.json", "r");
    fread(buffer, 1024, 1, fp);
    fclose(fp);
    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "CLIENTS", &clients);
    client = json_object_array_get_idx(clients, i);
    json_object_object_get_ex(client, "ID", &id_json);
    json_object_object_get_ex(client, "PASSWD", &pwd_json);
    json_object_object_get_ex(client, "LAST NAME", &lname_json);
    json_object_object_get_ex(client, "FIRST NAME", &fname_json);
    json_object_object_get_ex(client, "BIRTHDAY", &bday_json);
    json_object_object_get_ex(client, "EMAIL", &email_json);
    json_object_object_get_ex(client, "PHONE", &phon_json);
    json_object_object_get_ex(client, "ACCOUNTS LIST", &account_list_json);
    json_object_object_get_ex(account_list_json, "TYPE" , &type_json);
    json_object_object_get_ex(account_list_json, "ENTITLED" , &entitled_json);
    json_object_object_get_ex(account_list_json, "BALANCE" , &balance_json);

    char* id=(char*)json_object_get_string(id_json);
    char* pwd=(char*)json_object_get_string(pwd_json);
    char* lname=(char*)json_object_get_string(lname_json);
    char* fname=(char*)json_object_get_string(fname_json);
    char* bday=(char*)json_object_get_string(bday_json);
    char* email=(char*)json_object_get_string(email_json);
    char* phon=(char*)json_object_get_string(phon_json);
    char* type=(char*)json_object_get_string(type_json);
    char* entitled=(char*)json_object_get_string(entitled_json);
    float balance_c=(float)json_object_get_double(balance_json);
    float* balance=malloc(sizeof(float));
    *balance=balance_c;

    set_id(client_imported,id);
    set_passwd(client_imported,pwd);
    Perso_info p=new_perso_info();
    set_last_name(p,lname);
    set_first_name(p,fname);
    set_birthday(p,bday);
    set_perso_info(client_imported,p);
    Coordinates c=new_coordinates();
    set_mail(c,email);
    set_phone(c,phon);
    set_coordinates(p,c);
    set_perso_info(client_imported,p);
    Account a=new_account();
    set_type(a,type);
    set_entitled(a,entitled);
    set_balance(a,balance);
    set_account(client_imported,a);
    return client_imported;
}
