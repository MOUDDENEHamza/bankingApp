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

#define SIZE 64

/*Main function*/
int main(int argc, char *argv[]) {
    /**Initialize variables**/
    Symbol s = new_symbol();
    Client client = new_client();
    Json_object json_object, json_clients;
    json_object = json_object_new_object();
    json_clients = json_object_new_array();
    int log_in;
    int exit = get_exit(s);
    int flag = get_flag(s);
    int index = get_index(s);
    int sub_index = get_sub_index(s);
    char *id = (char *) malloc(SIZE), *passwd = (char *) malloc(SIZE);

    /**Start program**/
    init_bar();///Display the init bar.
    back:
    log_in = 0;
    display_menu(&exit);///Display the main menu.
    json_clients = parse_json();///Parse the json file containing the client data
    choose_feature(s, &flag);///Choose the feature you want to run

    while (exit) {

        switch (flag) {

            case 1 :///CLIENT AREA

                if (log_in == 0) {
                    input_id(id);
                    input_passwd(passwd);
                }

                if (!valid_client(client, json_clients, id, passwd)) {
                    log_in = 1;
                    display_client(&exit);///Display the administrator menu
                    choose_feature(s, &index);///Choose the feature you want to run

                    switch (index) {

                        case 1 :
                            display_client_account_management();
                            choose_feature(s, &sub_index);///Choose the feature you want to run

                            switch (sub_index) {

                                case 1 :
                                    consult_balance(client);///To consult the balance of the client
                                    break;

                                case 2 :
                                    transaction_list(client);///Get the operations list linked over a choosen period
                                    break;

                                case 3 :
                                    transfer_money(client, json_clients);///Get the transfers list associated to the client
                                    write_file(json_object, json_clients);///Update the JSON file
                                    break;

                                case 4 :
                                    pay_by_card(client, json_clients);///Pay by card
                                    write_file(json_object, json_clients);///Update the JSON file
                                    break;

                                case 5 :
                                    make_deposit(client, json_clients); ///Make a deposit
                                    write_file(json_object, json_clients);///Update the JSON file
                                    break;

                                default :///Display an error message if the user input an incorrect flag
                                    display_error_flag(s, &sub_index);
                                    choose_feature(s, &sub_index);///Choose the feature you want to run
                                    break;
                            }

                            break;

                        case 2 :
                            display_client_administration();
                            choose_feature(s, &sub_index);///Choose the feature you want to run

                            switch (sub_index) {

                                case 1 :
                                    change_client_passwd(client, json_clients);///To permit to client to change his password
                                    write_file(json_object, json_clients);///Update the JSON file
                                    index = 3;///Sign out the session
                                    break;

                                case 2 :

                                    break;

                                case 3 :

                                    break;

                                default :///Display an error message if the user input an incorrect flag
                                    display_error_flag(s, &sub_index);
                                    choose_feature(s, &sub_index);///Choose the feature you want to run
                                    break;
                            }

                            break;

                        case 3 : ///If the user want to sign out the submenu
                            break;

                        case 4 : ///Check if the user want to quit the program
                            end_bar();///Display the end bar.
                            exit = 0;
                            break;

                        default :///Display an error message if the user input an incorrect flag
                            display_error_flag(s, &flag);
                            break;
                    }
                    break;
                } else {
                    display_error_connexion_client();///Display an error message if the user input an incorrect id or password
                    break;
                }

            case 2 :///ADMINISTRATOR AREA

                if (log_in == 0) {
                    input_passwd(passwd);
                }

                if (!connect_admin(passwd)) {
                    display_administrator(&exit); //Display the administrator menu
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
                                    add_client(client);//Add new client
                                    add_client_json(client, json_clients);
                                    client = new_client();
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
                            display_admin_administration();///Display submenu of administration
                            change_administrator_passwd();///Allow to administrator to change his password
                            index = 4;///Sign out the session
                            break;

                        case 4 :///If the user want to sign out the submenu
                            break;

                        case 5 :///Check if the user want to quit the program
                            end_bar();///Display the end bar.
                            exit = 0;
                            break;

                        default :///Display an error message if the user input an incorrect flag
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

    //write_file(json_object, json_clients);

    return 0;
}