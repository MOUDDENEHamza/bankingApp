#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "struct.h"

/**
 * Get fields from .csv file
 */
char *getfield(char line[], int n);

/**
 * To consult the balance of the client 
 */
void consult_balance(Client client);

/**
 * Get the operations list linked over a choosen period 
 */
void transaction_list(void);

/**
 * Get the transfers list associated to the client
 */
void transfer_money(Client client, Json_object json_clients);

/**
 * Pay by card
 */
void pay_by_card(Client client, Json_object json_clients);

/**
 * Make a deposit
 */
void make_deposit(Client client, Json_object json_clients);

#endif
