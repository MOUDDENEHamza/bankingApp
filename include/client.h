#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "struct.h"

/**
 * To consult the balance of the client 
 */
void consult_balance(Client client);

/**
 * Get the operations list over a chosen period
 */
void transaction_list(Client client);

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
