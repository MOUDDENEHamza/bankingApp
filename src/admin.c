#include <stdio.h>
#include <stdlib.h>
#include "admin.h"
#include "struct.h"
#include "displayShell.h"
#include "input.h"

/*
 *Create account to the client
 */
void create_account(Client client) {
	//TODO
}

/*
 *Edit account to the client
 */
void edit_account(Client client) {
	//TODO
}

/*
 *delete account
 */
void delete_account(Client client) {
	free(client);
	display_deleting_msg();
}

/*
 *Add client
 */
void add_client(void) {
	Client client = new_client();
	input_perso_info(client);
}

/*
 *Edit the personal information of the client
 */
void edit_perso_info_client(Client client) {
	//TODO
}
