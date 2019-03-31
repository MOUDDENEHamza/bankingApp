#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "struct.h"
#include "displayShell.h"
#include "input.h"
#include "setting.h"
#include "security.h"
#include "json.h"

#define SIZE 255

/*Main function*/
int main(int argc, char *argv[]) {
	/*Initialize variables*/
	FILE *fp;
	Symbol s = new_symbol();
	Client head = NULL;
	struct json_object *clients;
	clients = json_object_new_array();
	int log_in;
	int exit = get_exit(s);
   	int flag = get_flag(s);
	int index = get_index(s);
	char id[SIZE], passwd[SIZE];
	
	/*Start program*/	
	fp = fopen("data/account_list.json", "a+");
   	char ch;
	if (fp == NULL) {
      		perror("Error while opening the file.\n");
      		return -1;
   	}
	while((ch = fgetc(fp)) != EOF)
      		printf("%c", ch);
	init_bar(); //Display the init bar.
	back:
	log_in = 0;
	display_menu(&exit); //Display the main menu.
	parse_json(clients);//Parse the json file containing the client data
	choose_feature(s, &flag); //Choose the feature you want to run
	while (exit){
		handle_menu(s, head, clients, &flag, &exit, &index, passwd, id, &log_in); //Define the function handling the main menu
		if ((flag == 1 && index == 3) || (flag == 2 && index == 4)) {
			goto back;//If the user want to sign out the submenu
		} 
		continue;
	}
	//strcpy(buffer, json_object_to_json_string(clients));
	fwrite(json_object_to_json_string(clients), 1, strlen(json_object_to_json_string(clients)), fp);
	fclose(fp);
	return 0;
}
