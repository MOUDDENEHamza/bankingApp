#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "struct.h"

/*
 * Get fields from .csv file
 */
char* getfield(char line[], int n);

/**
 * To consult the balance of the client 
 */
void consult_balance(Account account);

/**
 * Get the operations list linked over a choosen period 
 */
void transaction_list(void);

/**
 * Get the transfers list associated to the client
 */
void transfer_money(void);

#endif
