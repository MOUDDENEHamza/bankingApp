#ifndef _STRUCT_H_
#define _STRUCT_H_

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure handling the menu
 */
typedef struct symbol *Symbol;

/*-------------Constructor------------*/

/*
 * Constructor of symbol structure
 */
Symbol new_symbol(void);

/*---------------Getters--------------*/

/*
 *Get flag value from the structure
 */
int get_flag(Symbol s);

/*
 *Get exit value from the structure
 */
int get_exit(Symbol s);

/*
 *Get index value from the structure
 */
int get_index(Symbol s);

/*
 *Get the sub index value from the structure
 */
int get_sub_index(Symbol s);

/*--------------Setters---------------*/

/*
 *Set value to flag in structure
 */
void set_flag(Symbol s, int *val);

/*
 *Set value to exit in structure
 */
void set_exit(Symbol s, int *val);

/*
 *Set value to index in structure
 */
void set_index(Symbol s, int *val);

/*
 *Set value to index in structure
 */
void set_sub_index(Symbol s, int *val);

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure stocking the coordinates of clients
 */
typedef struct coordinates *Coordinates;

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Coordinates new_coordinates(void);

/*---------------Getters--------------*/

/*
 * Get the mail of client from the structure
 */
char *get_mail(Coordinates c);

/*
 * Get the phone number of client from the structure
 */
char *get_phone(Coordinates c);

/*--------------Setters---------------*/

/*
 * Set the mail of client into the structure
 */
void set_mail(Coordinates c, char *mail);

/*
 * Set the phone of client into the structure
 */
void set_phone(Coordinates c, char *phone);

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure stocking the personal information of clients
 */
typedef struct perso_info *Perso_info;

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Perso_info new_perso_info(void);

/*---------------Getters--------------*/

/*
 * Get the last name of client from the structure
 */
char *get_last_name(Perso_info p);

/*
 * Get the first name of client from the structure
 */
char *get_first_name(Perso_info p);

/*
 * Get the birthday of client from the structure
 */
char *get_birthday(Perso_info p);

/*
 *Get the the coordinates of client from the structure
 */
Coordinates get_coordinates(Perso_info p);

/*--------------Setters---------------*/

/*
 * Set the last name of client into the structure
 */
void set_last_name(Perso_info p, char *last_name);

/*
 * Set the first name of client into the structure
 */
void set_first_name(Perso_info p, char *first_name);

/*
 * Set the birthday of client into the structure
 */
void set_birthday(Perso_info p, char *birthday);

/*
 *Set the the coordinates of client into the structure
 */
void set_coordinates(Perso_info p, Coordinates c);

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

typedef struct entit *Entitled;

Entitled new_intitled(void);

char* get_ida_in_entit(Entitled i);

char* get_entitled_in_entit(Entitled i);

void set_ida_in_entit(Entitled i, char *n);

void set_entitled_in_entit(Entitled i, char* entitled);


/*
 * Introduce a simple structure handling account client
 */

typedef struct account *Account;

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Account new_account(void);


/*---------------Getters--------------*/

char* get_ida(Account a);

/*
 * Get the type of account from the structure
 */
char *get_type(Account a);

/*
 * Get the entitled of account from the structure
 */
char *get_entitled(Account a);

/*
 * Get the balance of account from the structure
 */
float get_balance(Account a);

/*
 * Get the next account of the same client
 */
Account get_nextAccount(Account a);

/*get the last added account of the client in list list of account*/
Account get_lastAccount(Account a) ;

Account get_ith_account_Account(Account a, int *i);

void copy(Account* account,int *i,int *nb_accounts, Account* myaccount);

/*---------------Setters--------------*/

void set_ida(Account a, char *ida);

/*
 * Set the type of account into the structure
 */
void set_type(Account a, char *type);

/*
 * Set the entitled of account from the structure
 */
void set_entitled(Account a, char *entitled);

/*
 * Set the balance of account from the structure
 */
void set_balance(Account a, float *balance);

/*set the next account of the same client  */
void set_nextAccount(Account a, Account next);

void set_nextOfLastAccout_Account(Account myaccount, Account account);

void set_ith_account_Account(Account myaccount,Account account, int* i);

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure handling account owner
 */
typedef struct client *Client;

/*--------------Constructor---------------*/

/*
 *Constructor of the structure
 */
Client new_client(void);

/*---------------Getters--------------*/

/*
 * Get the id of the account owner from the structure
 */
char *get_id(Client client);

/*
 * Get the passwd of account owner from the structure
 */
char *get_passwd(Client client);

/*
 * Get the personal information of account owner from the structure
 */
Perso_info get_perso_info(Client client);

/*
 * Get the account list of account owner from the structure
 */
Account get_account(Client client);

Account get_ith_account(Client client, int *i);


/*---------------Setters--------------*/

/*
 * Set the id of the account owner into the structure
 */
void set_id(Client client, char *id);

/*
 * Get the passwd of account owner into the structure
 */
void set_passwd(Client client, char *passwd);

/*
 * Get the personal information of account owner into the structure
 */
void set_perso_info(Client client, Perso_info p);

/*
 * Get the account list of account owner into the structure
 */
void set_account(Client client, Account a);


/*set the next account of the last account as a real account*/
void set_nextOfLastAccout(Client client, Account account);

void set_ith_account(Client client,Account account, int* i);

void set_ith_account0(Client client,Account account, int* i);

/*----------------------------------------------------------------------------*/

/*-----------------------------------Structure--------------------------------*/

/*
 * Introduce a simple structure handling account owner
 */
typedef struct json_object *Json_object;

/*----------------------------------------------------------------------------*/

#endif
