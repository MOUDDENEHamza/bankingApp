#include <stdio.h>
#include "struct.h"

/**
 * To consult the balance of the client
 */
float consult_balance(Account account);

/**
 * Get the operations list linked over a choosen period
 */
void operations_list(void);

/**
 * Get the transfers list associated to the client
 */
void transfers_list(void);

/*
 * Create client account
 */
Account create_account(void);

/*
 * Delete client account
 */
void delete_account(Account account);
