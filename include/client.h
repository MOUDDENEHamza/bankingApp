#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "struct.h"

/**
 * To consult the balance of the client 
 */
void consult_balance(Account account);

/**
 * Get the operations list linked over a choosen period 
 */
void operations_list(void);

/**
 * Get the transfers list associated to the client
 */
void transfers_list(void);

#endif
