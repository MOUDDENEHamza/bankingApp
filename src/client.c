#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/*
 * Get fields from .csv file
 */
char* getfield(char line[], int n){
	char *tok;
	for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
		if (!--n) {
			return tok;
		}
	}
	return NULL;
}

/**
 * To consult the balance of the client
 */
void consult_balance(Account account) {
	printf("\n\nLoading...\n\nYour account balance : %f\n\nCome back the client menu", get_balance(account));
}

/**
 * Get the operations list linked over a choosen period
 */
void transaction_list(void) {
	FILE *fp = fopen("data/account_data.csv", "r");
	printf("\n\nDownload transaction file : Loading...\n\n");
    	char line[1024];
    	while (fgets(line, 1024, fp)) {
		char *tmp = strdup(line);
		printf(" %s,%s\n", getfield(tmp, 1), getfield(tmp, 2));
        	free(tmp);
	}
	printf("\n\nCome back the client menu");
}

/**
 * Get the transfers list associated to the client
 */
void transfer_money(void) {

}
