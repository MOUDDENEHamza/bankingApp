#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"
#include "admin.h"
#include "json.h"

#define SIZE 64

/*
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag) {
    printf("\nEnter your choice : ");
    scanf("%d", flag);
    set_flag(s, flag);
}

/*
 * input and encrypt the password by putting * character
 */
void hide_passwd(char *passwd) {
    char *in = passwd;
    struct termios tty_orig;
    tcgetattr(STDIN_FILENO, &tty_orig);
    char c;
    struct termios tty_work = tty_orig;
    tcgetattr(STDIN_FILENO, &tty_orig);
    tty_work.c_lflag &= ~(ECHO | ICANON);
    tty_work.c_cc[VMIN] = 1;
    tty_work.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty_work);
    write(STDOUT_FILENO, "\nEnter your password : ", 24);
    while (1) {
        if (read(STDIN_FILENO, &c, sizeof c) > 0) {
            if ('\n' == c) {
                break;
            }
            *in++ = c;
            write(STDOUT_FILENO, "*", 1);
        }
    }
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty_orig);
    *in = '\0';
    fputc('\n', stdout);
}

/*
 * Generate unique id for the client
 */
void generate_unique_id(Client client) {
    srand(clock());
    char *id = (char *) malloc(SIZE);
    int t = 0;
    char *szTemp = "xxxxxxxx";
    char *szHex = "0123456789ABCDEF-";
    int nLen = strlen(szTemp);
    for (t = 0; t < nLen + 1; t++) {
        int r = rand() % 16;
        char c = ' ';
        switch (szTemp[t]) {
            case 'x' : {
                c = szHex[r];
            }
                break;
            case 'y' : {
                c = szHex[r & 0x03 | 0x08];
            }
                break;
            case '-' : {
                c = '-';
            }
                break;
            case '4' : {
                c = '4';
            }
                break;
        }
        id[t] = (t < nLen) ? c : 0x00;
    }
    write(STDOUT_FILENO, "\nAdd client : loading...\n", 25);
    printf("\ngenerate ID : %s\n", id);
    set_id(client, id);
}

/*
 * Ask to client to input his id
 */
void input_id(char *id) {
    printf("\nEnter your id : ");
    scanf("%s", id);
}

/*
 * Ask to user or administrator to input the password
 */
void input_passwd(char *passwd) {
    hide_passwd(passwd);
}

/*
 * Ask to user to create his own password
 */
void create_passwd(Client client) {
    char *passwd = (char *) malloc(SIZE);
    hide_passwd(passwd);
    set_passwd(client, passwd);
}

/*
 * Ask to user or administrator to input her last name
 */
void input_last_name(Client client) {
    char *last_name = (char *) malloc(SIZE);
    printf("\nEnter your last name : ");
    scanf("%s", last_name);
    set_last_name(get_perso_info(client), last_name);
}

/*
 * Ask to user or administrator to input her first name
 */
void input_first_name(Client client) {
    char *first_name = (char *) malloc(SIZE);
    printf("\nEnter your first name : ");
    scanf("%s", first_name);
    set_first_name(get_perso_info(client), first_name);
}

/*
 * Ask to user or administrator to input his Email address
 */
void input_mail(Client client) {
    char *mail = (char *) malloc(SIZE);
    printf("\nEnter your E-mail : ");
    scanf("%s", mail);
    set_mail(get_coordinates(get_perso_info(client)), mail);
}

/*
 * Ask to user or administrator to input her phone number
 */
void input_phone(Client client) {
    char *phone = (char *) malloc(SIZE);
    printf("\nEnter your phone : ");
    scanf("%s", phone);
    set_phone(get_coordinates(get_perso_info(client)), phone);
}

/*
 * Ask to user or administrator to input his birthday
 */
void input_birthday(Client client) {
    char *birthday = (char *) malloc(SIZE);
    printf("\nEnter your birthday : ");
    scanf("%s", birthday);
    set_birthday(get_perso_info(client), birthday);

}

/*
 * input all personnal information
 */
Client input_perso_info(Client client) {
    int by_default = 1;
    float init_balance = 0;
    generate_unique_id(client);
    create_passwd(client);
    input_last_name(client);
    input_first_name(client);
    input_birthday(client);
    input_mail(client);
    input_phone(client);
    printf("\nAutomatic creation of a current account\n");
    input_type(client, &by_default);
    printf("\nYour balance is initialized to 0\n");
    set_balance(get_account(client), &init_balance);
    input_entitled(client);
    return client;
}

/*
 * Ask to the administrator de to enter a new balance
 */
void input_new_balance(Client client) {
    float balance;
    printf("\nEnter new balance :\n");
    scanf("%f", &balance);
    set_balance(get_account(client), &balance);
}

/* input the account type choosen*/
void input_type(Client client, int *choice) {
    char *type = (char *) malloc(SIZE);
    back:
    switch (*choice) {
        case 1 :
            strcpy(type, "CURRENT ACCOUNT");
            set_type(get_account(client), type);
            break;
        case 2 :
            strcpy(type, "SAVINGS ACCOUNT");
            set_type(get_account(client), type);
            break;
        case 3 :
            strcpy(type, "TERM ACCOUNT");
            set_type(get_account(client), type);
            break;
        case 4 :
            strcpy(type, "TITLE ACCOUNT");
            set_type(get_account(client), type);
            break;
        case 5 :
            strcpy(type, "INDIVIDUAL ACCOUNT");
            set_type(get_account(client), type);
            break;
        case 6 :
            strcpy(type, "JOINT ACCOUNT");
            set_type(get_account(client), type);
            break;
        default :
            printf("\nWrong choice. Please try again\n");
            goto back;
    }
}

/*input the entitled of the account*/
void input_entitled(Client client) {
    char *entitled = (char *) malloc(SIZE);
    printf("Enter the entitled\n");
    scanf("%s", entitled);
    set_entitled(get_account(client), entitled);
}

/*input all account information*/
void input_create_account(Client client) {
    int choice;
    input_type(client, &choice);
    input_entitled(client);
    input_new_balance(client);
    set_account(client, get_account(client));
}

/*input a new account*/
void input_add_account(Client client) {
    int choice;
    input_type(client, &choice);
    input_entitled(client);
    input_new_balance(client);
    set_nextOfLastAccout(client, get_account(client));
}