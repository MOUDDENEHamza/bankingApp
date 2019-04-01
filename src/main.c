#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include "struct.h"
#include "displayShell.h"
#include "input.h"
#include "security.h"
#include "admin.h"
#include "client.h"
#include "json.h"

#define SIZE 255

/*Main function*/
int main(int argc, char *argv[]) {
    /*Initialize variables*/
    Symbol s = new_symbol();
    Client head = NULL;
    Client new_node = new_client();
    Object object;
    Clients clients;
    object = json_object_new_object();
    clients = json_object_new_array();
    int log_in;
    int exit = get_exit(s);
    int flag = get_flag(s);
    int index = get_index(s);
    int sub_index = get_sub_index(s);
    char id[SIZE], passwd[SIZE];

    /*Start program*/
    init_bar(); //Display the init bar.
    back:
    log_in = 0;
    display_menu(&exit); //Display the main menu.
    clients = parse_json();//Parse the json file containing the client data
    choose_feature(s, &flag); //Choose the feature you want to run

    while (exit) {
        switch (flag) {

            case 1 :
                if (log_in == 0) {
                    generate_unique_id(head);
                    input_passwd(head, passwd);
                }
                if (!valid_client(head, id, passwd)) {
                    log_in = 1;
                    display_client(&exit); //Dipslay the administrator menu
                    choose_feature(s, &index); //Choose the feature you want to run
                    switch (index) {
                        case 1 :
                            display_client_account_management();
                            choose_feature(s, &sub_index); //Choose the feature you want to run
                            switch (sub_index) {
                                case 1 :
                                    consult_balance(get_account(head));//To consult the balance of the client
                                    break;
                                case 2 :
                                    transaction_list();//Get the operations list linked over a choosen period
                                    break;
                                case 3 :
                                    transfer_money();//Get the transfers list associated to the client
                                    break;
                                default ://Display an error message if the user input an incorrect flag
                                    display_error_flag(s, &sub_index);
                                    choose_feature(s, &sub_index); //Choose the feature you want to run
                                    goto restart;
                            }
                            break;
                        case 2 :
                            display_client_administration();
                            choose_feature(s, &index); //Choose the feature you want to run
                            //handle_client_administration(s, head, clients, &index, &exit, &index, passwd, id);
                            break;
                        case 3 : //If the user want to sign out the submenu
                            break;
                        case 4 : //Check if the user want to quit the program
                            end_bar(); //Display the end bar.
                            exit = 0;
                            break;
                        default ://Display an error message if the user input an incorrect flag
                            display_error_flag(s, &flag);
                            break;
                    }
                    break;
                } else {
                    display_error_connexion_client();//Display an error message if the user input an incorrect id or password
                    break;
                }

            case 2 :
                if (log_in == 0) {
                    input_passwd(head, passwd);
                }
                if (!connect_admin(passwd)) {
                    display_administrator(&exit); //Dipslay the administrator menu
                    choose_feature(s, &index); //Choose the feature you want to run
                    switch (index) {
                        case 1 :
                            display_admin_account_management();
                            break;
                        case 2 :
                            display_admin_client_management();
                            choose_feature(s, &sub_index); //Choose the feature you want to run
                        restart:
                            switch (sub_index) {
                                case 1 :
                                    add_client(new_node);//Add new client
                                    add_client_json(new_node, clients);
                                    head = append(head, new_node);
                                    new_node = new_client();
                                    break;
                                case 2 :

                                    break;
                                case 3 :
                                    break;
                                default ://Display an error message if the user input an incorrect flag
                                    display_error_flag(s, &flag);
                                    choose_feature(s, &flag); //Choose the feature you want to run
                                    goto restart;
                            }
                            break;
                        case 3 :
                            display_admin_administration();
                            break;
                        case 4 : //If the user want to sign out the submenu
                            break;
                        case 5 : //Check if the user want to quit the program
                            end_bar(); //Display the end bar.
                            exit = 0;
                            break;
                        default ://Display an error message if the user input an incorrect flag
                            display_error_flag(s, &flag);
                            break;
                    }
                    log_in = 1;
                    break;
                } else {
                    display_error_connexion_admin(); //Display an error message if the administrator input an incorrect password
                    break;
                }

            case 3 : //Check if the user want to quit the program
                end_bar();
                exit = 0;
                break;
            default ://Display an error message if the user input an incorrect flag
                display_error_flag(s, &flag);
                choose_feature(s, &flag);//Choose the feature you want to run
                break;
        }


        if ((flag == 1 && index == 3) || (flag == 2 && index == 4)) {
            goto back;//If the user want to sign out the submenu
        }

        continue;
    }
    write_file(object, clients);
    return 0;
}