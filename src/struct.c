#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling the menu
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
 * Introduce a simple structre stocking the cooridnates of clients
 */
struct coordinates {
    char *mail;
    char *phone;
    char *address;
};

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Coordinates new_coordinates(void) {
    Coordinates c = malloc(sizeof(Coordinates));
    c->mail = malloc(sizeof(char *));
    c->phone = malloc(sizeof(char *));
    c->address = malloc(sizeof(char *));
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

/*
 * Get the address of client from the structure
 */
char *get_address(Coordinates c) {
    return c->address;
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

/*
 * Set the address of client into the structure
 */
void set_address(Coordinates c, char *address) {
    strcpy(c->address, address);
}

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre stocking the personal information of clients
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
 * Introduce a simple structre handling account client
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
    return a->type;
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

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structre handling account owner
 */
struct client {
    char *id;
    char *passwd;
    Perso_info perso_info;
    Account account;
    Client next;
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
    client->next = NULL;
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

/*
 * Get the next client from the structure
 */
Client get_next_client(Client client) {
    return client->next;
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
}

/*
 * Set the next client into the structure
 */
void set_next_client(Client client, Client next) {
    client->next = next;
}

/*----------------------------------------------------------------------------*/

/*
 * Add a new node at the end of the list
 */
void append(Client head, Client new_client) {
    Client temp = NULL;
    if (head == NULL) {
        head = new_client;
    } else {
        temp = head;
        while (get_next_client(temp) != NULL) {
            temp = get_next_client(temp);
        }
        set_next_client(temp, new_client);
    }
}

/*
 * The linked list can be traversed in a while loop by using the head node as a starting reference
 */
void traverse(Client head) {
    Client current = head;
    while (current != NULL) {
        printf("\nID : %s\n", get_id(current));
        printf("\nPASSWD : %s\n", get_passwd(current));
        current = get_next_client(current);
    }
}
