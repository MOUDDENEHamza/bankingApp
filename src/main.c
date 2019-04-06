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
    Client client = new_client();
    Json_object json_object = json_object_new_object();
    Json_object json_clients = json_object_new_array();
    int log_in;
    int exit = get_exit(s);
    int flag = get_flag(s);
    int index = get_index(s);
    int sub_index = get_sub_index(s);
    char id[SIZE], passwd[SIZE];

    int *idx=malloc(sizeof(int));
    int *nb_acc1=malloc(sizeof(int));
    int *nb_acc2=malloc(sizeof(int));

    /*Start program*/
    init_bar(); //Display the init bar.
    back:
    log_in = 0;
    display_menu(&exit); //Display the main menu.
    json_clients = parse_json();//Parse the json file containing the client data
    choose_feature(s, &flag); //Choose the feature you want to run
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
                                    transaction_list();///Get the operations list linked over a choosen period
                                    break;

                                case 3 :
                                    transfer_money(client, json_clients);///Get the transfers list associated to the client
                                    break;

                                case 4 :
                                    pay_by_card(client, json_clients);///Pay by card
                                    break;

                                case 5 :
                                    make_deposit(client, json_clients); ///Make a deposit
                                    break;

                                default :///Display an error message if the user input an incorrect flag
                                    display_error_flag(s, &sub_index);
                                    choose_feature(s, &sub_index);///Choose the feature you want to run
                                    goto restart;
                            }
                            break;


                        case 2 :
                            display_client_administration();
                            choose_feature(s, &index);///Choose the feature you want to run
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
                            choose_feature(s, &sub_index);
                            restart0:
                            switch (sub_index) {
                                case 1 :
                                    client=create_new_account(nb_acc1);
                                    modify_client(client,json_clients,nb_acc1);
                                    write_file(json_object, json_clients);
                                    break;
                                case 2 :
                                    client = edit_account(client);
                                    modify_client(client,json_clients,nb_acc1);
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 3 :
                                    json_clients = admin_delete_account(client, json_clients); ///Delete an account
                                    write_file(json_object, json_clients);///Update the JSON file
                                    json_clients = parse_json();///Parse the json file containing the client data
                                    break;
                                case 4 :
                                    display_accounts_list();
                                    break;

                                case 5 :
                                    end_bar(); //Display the end bar.
                                    exit = 0;
                                    break;

                                default ://Display an error message if the user input an incorrect flag
                                    display_error_flag(s, &flag);
                                    choose_feature(s, &flag); //Choose the feature you want to run
                                    goto restart0;
                            }
                            break;
                        case 2 :
                            display_admin_client_management();
                            choose_feature(s, &sub_index); //Choose the feature you want to run
                            restart:
                            switch (sub_index) {
                                case 1 :
                                    add_client(client);//Add new client
                                    add_client_json(client, json_clients);
                                    write_file(json_object, json_clients);
                                    client = new_client();
                                    break;
                                case 2 :
                                    client = edit_client_coordonates(nb_acc1);
                                    modify_client(client,json_clients,nb_acc1);
                                    write_file(json_object, json_clients);
                                    client=new_client();
                                    break;
                                case 3 :
                                    display_entiled();
                                    break;
                                case 4 :
                                    end_bar(); //Display the end bar.
                                    exit = 0;
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
    return 0;
}