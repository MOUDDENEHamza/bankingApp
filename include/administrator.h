#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

typedef struct _coordonnees* coordonnees;

typedef struct _donnees_perso* donnees_perso;

typedef struct _identifient* identifient;

typedef struct _Compte* Compte;

typedef struct _Titulaire_Compte* Titulaire_Comptes;

void creer_compte(Titulaire_Comptes t);

void modifier_compte(Titulaire_Comptes t);

void supprimer_compte(Titulaire_Comptes t);

void afficher_list_comptes(Titulaire_Comptes t);

void ajouter_client();

void modifier_infos_client(Titulaire_Comptes t);

void afficher_list_titulaires(Compte c);

void changer_mot(Compte c);

#endif
