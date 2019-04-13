#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"
#include "displayShell.h"
#include "admin.h"
#include "json.h"

#define SIZE 64

/**
 * Choose the feature you want to run
 */
void choose_feature(Symbol s, int *flag) {
    printf("\nEnter your choice : ");
    scanf("%d", flag);
    set_flag(s, flag);
}

/**
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

/**
 * Generate unique id for the client
 */
char *generate_unique_id(void) {
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
    return id;
}

/**
 * Ask to client to input his id
 */
void input_id(char *id) {
    printf("\nEnter the ID of the client : ");
    scanf("%s", id);
}

/**
 * Ask to user or administrator to input the password
 */
void input_passwd(char *passwd) {
    write(STDOUT_FILENO, "\nEnter your password : ", 24);
    hide_passwd(passwd);
}

/**
 * Ask to user to create his own password
 */
char *create_passwd(void) {
    char *passwd = (char *) malloc(SIZE);
    write(STDOUT_FILENO, "\nEnter your password : ", 24);
    hide_passwd(passwd);
    return passwd;
}

/**
 * Ask to user or administrator to input her last name
 */
char *input_last_name(void) {
    char *last_name = (char *) malloc(SIZE);
    printf("\nEnter your last name : ");
    scanf("%s", last_name);
    return last_name;
}

/**
 * Ask to user or administrator to input her first name
 */
char *input_first_name(void) {
    char *first_name = (char *) malloc(SIZE);
    printf("\nEnter your first name : ");
    scanf("%s", first_name);
    return first_name;
}

/**
 * Ask to user or administrator to input his birthday
 */
char *input_birthday(void) {
    char *birthday = (char *) malloc(SIZE);
    printf("\nEnter your birthday : ");
    scanf("%s", birthday);
    return birthday;
}

/**
 * Ask to user or administrator to input his Email address
 */
char *input_mail(void) {
    char *mail = (char *) malloc(SIZE);
    printf("\nEnter your E-mail : ");
    scanf("%s", mail);
    return mail;
}

/**
 * Ask to user or administrator to input her phone number
 */
char *input_phone(void) {
    char *phone = (char *) malloc(SIZE);
    printf("\nEnter your phone : ");
    scanf("%s", phone);
    return phone;
}

/**
 * Ask the user to input an integer
 */
int input_choice(void) {
    int choice;

    printf("\nEnter your choice : ");
    scanf("%d", &choice);
    return choice;
}

/**
 * Ask to user to input the account type
 */
char *input_type(int *choice) {
    char *type = (char *) malloc(SIZE);
    back:
    switch (*choice) {
        case 1 :
            strcpy(type, "CURRENT");
            return type;
        case 2 :
            strcpy(type, "SAVINGS");
            return type;
        case 3 :
            strcpy(type, "JOINT");
            return type;
        default :
            display_error_flag();
            goto back;
    }
}

/**
 * Ask user to input the entitled of the account
 */
char *input_entitled(void) {
    char *entitled = (char *) malloc(SIZE);
    printf("\nEnter the entitled : ");
    scanf("%s", entitled);
    return entitled;
}

/**
 * Ask user to input the joint entitled of the account
 */
char *input_joint_entitled(void) {
    char *joint_entitled = (char *) malloc(SIZE);
    printf("\nEnter the joint entitled : ");
    scanf("%s", joint_entitled);
    return joint_entitled;
}

/**
 * input all personal information
 */
Client input_perso_info(Client client) {
    Account a = get_account(client);
    Perso_info p = get_perso_info(client);
    int by_default = 1;
    float init_balance = 0;

    set_id(client, generate_unique_id());
    set_passwd(client, create_passwd());
    set_last_name(p, input_last_name());
    set_first_name(p, input_first_name());
    set_birthday(p, input_birthday());
    set_mail(get_coordinates(p), input_mail());
    set_phone(get_coordinates(p), input_phone());
    printf("\nAutomatic creation of a current account\n");
    set_type(a, input_type(&by_default));
    printf("\nYour balance is initialized to 0\n");
    set_balance(a, &init_balance);
    set_entitled(a, input_entitled());

    return client;
}