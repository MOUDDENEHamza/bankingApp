#include <stdio.h>
#include <stdlib.h>
#include "../include/administrateur.h"

typedef struct _coordonnees
{
    char* mail;
    char* telnumber;
    char* adresses;
}_coordonnees;

typedef struct _donnees_perso
{
    char* nom;
    char* prenom;
    char date_de_naissance[10];
    _coordonnees* coordonnees;
}_donnees_perso;

typedef struct _identifient
{
    int id;
}_identifient;


typedef struct _Compte
{
    identifient id;
    char* type;
    char* intitule;
    _donnees_perso* titulaires;
}_Compte;

typedef struct _Titulaire_Comptes
{
    _donnees_perso* donnees;
    _Compte* list_comptes;
}_Titulaire_Comptes;

void creer_compte(Titulaire_Comptes t){
    
}

void modifier_compte(Titulaire_Comptes t){

}

void supprimer_compte(Titulaire_Comptes t){
    free(t);
}

void afficher_list_comptes(Titulaire_Comptes t){

}

void ajouter_client(){

}

void modifier_infos_client(Titulaire_Comptes t){

}

void afficher_list_titulaires(Compte c){

}

void changer_mot(Compte c){
    
}

