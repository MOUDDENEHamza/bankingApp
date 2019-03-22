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
	printf("\nAdd client : loading...\n");
	Client client = new_client();
	input_perso_info(client);
	printf("\nClient has been added. Come back to the administrator menu.\n");
}

/*
 *Edit the personal information of the client
 */
void edit_perso_info_client(Client client) {
	printf("\nChange the coordinates : loading...\n");
	free(get_perso_info(client));
	printf("\nthe coordinates has been edited. Come back to the administrator menu.\n");
}
