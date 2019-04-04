#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "admin.h"

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure handling the menu
 */
struct symbol {
    int flag;
    int exit;
    int index;
    int sub_index;
};

/*-------------Constructor------------*/

/*
 * Constructor of symbol structure
 */
Symbol new_symbol(void) {
    Symbol s = (Symbol) malloc(sizeof(Symbol));
    s->flag = 0;
    s->exit = 1;
    s->index = 0;
    s->sub_index = 0;
    return s;
}

/*---------------Getters--------------*/

/*
 *Get flag value from the structure
 */
int get_flag(Symbol s) {
    return s->flag;
}

/*
 *Get exit value from the structure
 */
int get_exit(Symbol s) {
    return s->exit;
}

/*
 *Get index value from the structure
 */
int get_index(Symbol s) {
    return s->index;
}

/*
 *Get the sub index value from the structure
 */
int get_sub_index(Symbol s) {
    return s->sub_index;
}

/*---------------Setters--------------*/

/*
 *Set value to flag in structure
 */
void set_flag(Symbol s, int *val) {
    s->flag = *val;
}

/*
 *Set value to exit in structure
 */
void set_exit(Symbol s, int *val) {
    s->exit = *val;
}

/*
 *Set value to index in structure
 */
void set_index(Symbol s, int *val) {
    s->index = *val;
}

/*
 *Set value to index in structure
 */
void set_sub_index(Symbol s, int *val) {
    s->sub_index = *val;
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure stocking the coordinates of clients
 */
struct coordinates {
    char *mail;
    char *phone;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Coordinates new_coordinates(void) {
    Coordinates c = malloc(sizeof(Coordinates));
    c->mail = malloc(sizeof(char *));
    c->phone = malloc(sizeof(char *));
    return c;
}

/*---------------Getters--------------*/

/*
 * Get the e-mail of client from the structure
 */
char *get_mail(Coordinates c) {
    return c->mail;
}

/*
 * Get the phone number of client from the structure
 */
char *get_phone(Coordinates c) {
    return c->phone;
}

/*--------------Setters---------------*/

/*
 * Set the mail of client into the structure
 */
void set_mail(Coordinates c, char *mail) {
    strcpy(c->mail, mail);
}

/*
 * Set the phone of client into the structure
 */
void set_phone(Coordinates c, char *phone) {
    strcpy(c->phone, phone);
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure stocking the personal information of clients
 */
struct perso_info {
    char *last_name;
    char *first_name;
    char *birthday;
    Coordinates coordinates;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Perso_info new_perso_info(void) {
    Perso_info p = malloc(sizeof(Perso_info));
    p->last_name = malloc(sizeof(char *));
    p->first_name = malloc(sizeof(char *));
    p->birthday = malloc(sizeof(char *));
    p->coordinates = new_coordinates();
    return p;
}

/*---------------Getters--------------*/

/*
 * Get the last name of client from the structure
 */
char *get_last_name(Perso_info p) {
    return p->last_name;
}

/*
 * Get the first name of client from the structure
 */
char *get_first_name(Perso_info p) {
    return p->first_name;
}

/*
 * Get the birthday of client from the structure
 */
char *get_birthday(Perso_info p) {
    return p->birthday;
}

/*
 * Get the the coordinates of client from the structure
 */
Coordinates get_coordinates(Perso_info p) {
    return p->coordinates;
}

/*--------------Setters---------------*/

/*
 * Set the last name of client into the structure
 */
void set_last_name(Perso_info p, char *last_name) {
    strcpy(p->last_name, last_name);
}

/*
 * Set the first name of client into the structure
 */
void set_first_name(Perso_info p, char *first_name) {
    strcpy(p->first_name, first_name);
}

/*
 * Set the birthday of client into the structure
 */
void set_birthday(Perso_info p, char *birthday) {
    strcpy(p->birthday, birthday);
}

/*
 *Set the the coordinates of client into the structure
 */
void set_coordinates(Perso_info p, Coordinates c) {
    p->coordinates = c;
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure handling account client
 */
struct account {
    char *type;
    char *entitled;
    float balance;
    Account nextAccount;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Account new_account(void) {
    Account a = malloc(sizeof(Account));
    a->type = malloc(sizeof(char *));
    a->entitled = malloc(sizeof(char *));
    a->balance = 0;
    a->nextAccount = NULL;
    return a;
}

int account_is_empty(Account a){
    return a==new_account();
}

/*---------------Getters--------------*/

/*
 * Get the type of account from the structure
 */
char *get_type(Account a) {
    return a->type;
}

/*
 * Get the entitled of account from the structure
 */
char *get_entitled(Account a) {
    return a->entitled;
}

/*
 * Get the balance of account from the structure
 */
float get_balance(Account a) {
    return a->balance;
}

/*
 * get the next account of the same client int the account
 */
Account get_nextAccount(Account a) {
    return a->nextAccount;
}

/*get the last added account of the client in list list of account*/
Account get_lastAccount(Account a) {
    if(a==NULL){
        a=new_account();
        return a;
    }
    else{
        if(a->nextAccount==NULL){
            return a;
        }
        else
        {
            return get_lastAccount(a->nextAccount);   
        }
    }
}

Account get_ith_account_Account(Account a, int *i){
    if(*i==0){
        return a;
    }
    if(*i==1){
        a->nextAccount=new_account();
        return a->nextAccount;
    }
    else
    {
        *i--;
        Account b = a->nextAccount;
        return get_ith_account_Account(a->nextAccount,i);
    }
}

/*---------------Setters--------------*/

/*
 * Set the type of account into the structure
 */
void set_type(Account a, char *type) {
    strcpy(a->type, type);
}

/*
 * Set the entitled of account from the structure
 */
void set_entitled(Account a, char *entitled) {
    strcpy(a->entitled, entitled);
}

/*
 * Set the balance of account from the structure
 */
void set_balance(Account a, float *balance) {
    a->balance = *balance;
}

/*
 * Set the next account of the same client int the account
 */
void set_nextAccount(Account a, Account next) {
    a->nextAccount = next;
}

/*set the next account of the last account as a real account*/
void set_nextOfLastAccout_Account(Account myaccount, Account account) {
    if(myaccount->nextAccount==NULL){
        myaccount->nextAccount=account;
    }
    else
    {
        set_nextOfLastAccout_Account(myaccount->nextAccount, account);
    }
}

void set_ith_account_Account(Account myaccount,Account account, int* i){
    if(*i==0){
        myaccount=account;
    }
    if(*i==1){
        myaccount->nextAccount=account;
    }
    else
    {
        *i--;
        set_ith_account_Account(myaccount->nextAccount,account,i);
    }
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure handling account owner
 */
struct client {
    char *id;
    char *passwd;
    Perso_info perso_info;
    Account account;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Client new_client(void) {
    Client client = malloc(sizeof(Client));
    client->id = malloc(sizeof(char *));
    client->passwd = malloc(sizeof(char *));
    client->perso_info = new_perso_info();
    client->account = new_account();
    return client;
}

/*---------------Getters--------------*/

/*
 * Get the id of the account owner from the structure
 */
char *get_id(Client client) {
    return client->id;
}

/*
 * Get the passwd of account owner from the structure
 */
char *get_passwd(Client client) {
    return client->passwd;
}

/*
 * Get the personal information of account owner from the structure
 */
Perso_info get_perso_info(Client client) {
    return client->perso_info;
}

/*
 * Get the account list of account owner from the structure
 */
Account get_account(Client client) {
    return client->account;
}

Account get_ith_account(Client client, int *i){
    return get_ith_account_Account(client->account, i);
}

/*---------------Setters--------------*/

/*
 * Set the id of the account owner into the structure
 */
void set_id(Client client, char *id) {
    strcpy(client->id, id);
}

/*
 * Get the passwd of account owner into the structure
 */
void set_passwd(Client client, char *passwd) {
    strcpy(client->passwd, passwd);
}

/*
 * Get the personal information of account owner into the structure
 */
void set_perso_info(Client client, Perso_info p) {
    client->perso_info = p;
}

/*
 * Get the account list of account owner into the structure
 */
void set_account(Client client, Account a) {
    client->account = a;
    client->account->nextAccount=new_account();
}

/*set the next account of the last account as a real account*/
void set_nextOfLastAccout(Client client, Account account) {
    set_nextOfLastAccout_Account(client->account,account);
}

void set_ith_account(Client client,Account account, int* i){
    set_ith_account_Account(client->account,account,i);
}

void set_ith_account0(Client client,Account account, int* i){
    Account a = client->account;
    if(*i==0){
        client->account=account;
    }
    if(*i==1){
        client->account->nextAccount=account;
    }
    else
    {
        for(int j=0; j<= *i-1; j++){
            a=a->nextAccount;
        }
        a=account;
    }
}


/*----------------------------------------------------------------------------*/