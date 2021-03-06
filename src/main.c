#include <stdio.h>
#include <stdlib.h>
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

/**Main function**/
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
    display_menu();///Display the main menu.
    json_clients = parse_json();///Parse the json file containing the client data
    choose_feature(s, &flag);///Choose the feature you want to run
    while (exit) {
        switch (flag) {
            case 1 :///////////////////////////////////////////CLIENT AREA//////////////////////////////////////////////
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
                                    consult_balance(client, json_clients);///To consult the balance of the client
                                    break;
                                case 2 :
                                    transaction_list(client);///Get the operations list linked over a choosen period
                                    break;
                                case 3 :
                                    transfer_money(client,
                                                   json_clients);///Get the transfers list associated to the client
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 4 :
                                    pay_by_card(client, json_clients);///Pay by card
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 5 :
                                    make_deposit(client, json_clients); ///Make a deposit
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                default :
                                    display_error_flag();///Display an error message if the user input an incorrect flag
                                    choose_feature(s, &sub_index);///Choose the feature you want to run
                                    break;
                            }
                            break;
                        case 2 :
                            display_client_administration();
                            choose_feature(s, &sub_index);///Choose the feature you want to run
                            switch (sub_index) {
                                case 1 :
                                    if (change_client_passwd(client)) {///To permit to client to change his password
                                        index = 3;///Sign out the session
                                    }
                                    break;
                                case 2 :
                                    client_create_account(client, json_clients); ///Create an account
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 3 :
                                    json_clients = client_delete_account(client, json_clients); ///Delete an account
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                default :///Display an error message if the user input an incorrect flag
                                    display_error_flag();///Display the error message
                                    break;
                            }
                            break;
                        case 3 : ///If the user want to sign out the submenu
                            break;
                        case 4 : ///Check if the user want to quit the program
                            end_bar();///Display the end bar.
                            exit = 0;
                            break;
                        default :
                            display_error_flag();///Display an error message if the user input an incorrect flag
                            break;
                    }
                    break;
                } else {
                    display_error_connexion_client();///Display an error message if the user input an incorrect id or password
                    break;
                }
            case 2 :///////////////////////////////////////ADMINISTRATOR AREA///////////////////////////////////////////
                if (log_in == 0) {
                    input_passwd(passwd);
                }
                if (!connect_admin(passwd)) {
                    display_administrator(&exit);///Display the administrator menu
                    choose_feature(s, &index);///Choose the feature you want to run
                    switch (index) {
                        case 1 :
                            display_admin_account_management();///Display the admin account management menu
                            choose_feature(s, &sub_index);///Choose the feature you want to run
                        restart_admin_account_management:
                            switch (sub_index) {
                                case 1 :
                                    admin_create_account(json_clients); ///Create an account
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 2 :
                                    json_clients = admin_delete_account(json_clients); ///Delete an account
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 3 :
                                    display_account_list_by_type(
                                            json_clients);///Display the account list by type of whole client in the bank
                                    break;
                                default :
                                    display_error_flag();///Display an error message if the user input an incorrect flag
                                    choose_feature(s, &sub_index);///Choose the feature you want to run
                                    goto restart_admin_account_management;
                            }
                            break;
                        case 2 :
                            display_admin_client_management();
                            choose_feature(s, &sub_index);///Choose the feature you want to run
                        restart_admin_client_management:
                            switch (sub_index) {
                                case 1 :
                                    add_client(client);///Add new client to the structure
                                    add_client_json(client, json_clients);///Add the new client to the JSON structure
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 2 :
                                    edit_coordinates(json_clients);///Edit the coordinates of a given clients
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 3 :
                                    display_entitled_list_account(
                                            json_clients);///Display the list of entitled of a given account
                                    break;
                                default :
                                    display_error_flag();///Display an error message if the user input an incorrect flag
                                    choose_feature(s, &flag);///Choose the feature you want to run
                                    goto restart_admin_client_management;
                            }
                            break;
                        case 3 :
                            display_admin_administration();///Display submenu of administration
                            if (change_administrator_passwd()) {///Allow to administrator to change his password
                                index = 4;///Sign out the session
                            }
                            break;
                        case 4 :///If the user want to sign out the submenu
                            break;
                        case 5 :///Check if the user want to quit the program
                            end_bar();///Display the end bar.
                            exit = 0;
                            break;
                        default :
                            display_error_flag();///Display an error message if the user input an incorrect flag
                            break;
                    }
                    log_in = 1;
                    break;
                } else {
                    display_error_connexion_admin();///Display an error message if the administrator input an incorrect password
                    break;
                }
            case 3 :///Check if the user want to quit the program
                end_bar();
                exit = 0;
                break;
            default :
                display_error_flag();///Display an error message if the user input an incorrect flag
                choose_feature(s, &flag);///Choose the feature you want to run
                break;
        }
        if ((flag == 1 && index == 3) || (flag == 2 && index == 4)) {
            goto back;///If the user want to sign out the submenu
        }
        continue;
    }
    return 0;
}