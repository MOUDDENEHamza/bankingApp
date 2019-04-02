#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/**
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
void consult_balance(Client client) {
	printf("\nLoading...\n");
	printf("\nThe balance of your %s is : %f\n", get_type(get_account(client)), get_balance(get_account(client)));
	printf("\nCome back the client menu\n");
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

/**
 * Pay by card
 */
void pay_by_card(Client client) {
    float product_price;
    printf("\nSecure payment\n");
    printf("\nEnter the price of the product : ");
    scanf("%f", &product_price);
    if (product_price <= get_balance(get_account(client))) {
        printf("\nPayment done\n");
        return;
    }
    printf("\nyour balance is insufficient to perform this operation\n");
}
