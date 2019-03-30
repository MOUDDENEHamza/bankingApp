#include <stdio.h>
#include "struct.h"

/**
 * To consult the balance of the client
 */
void consult_balance(Account account) {
	printf("\n\nLoading...\n\nYour account balance : %f\n\nCome back the client menu\n", get_balance(account));
}

/**
 * Get the operations list linked over a choosen period
 */
void operations_list(void);

/**
 * Get the transfers list associated to the client
 */
void transfers_list(void);
