#ifndef FORUM_STRUCT_H
#define FORUM_STRUCT_H

#include <stdbool.h>
#include <time.h>
typedef struct tm Date;

typedef struct Profil {
    char nom[50];
    char prenom[50];
    char adresse[100];
    char couriel[50];
    Date date_naissance;
    unsigned int num_tel;
    unsigned int num_inscrit;
} prl;

typedef struct Auteur {
    char adresse_email[50];
    char pseudo[50];
    unsigned int nbr_mesg;
    Date date_mesg1;
    Date date_mesg2;
    unsigned int prfl_num_inscrit;
    unsigned int id;
} aut;

typedef struct Message {
    unsigned int id;
    char titre[50];
    char text[100];
    Date date_pub;
    unsigned int auteur_id;
    int isResponse;
    unsigned int id_message_initial;
    struct Message* suivant;
} mesg;

typedef struct site {
    char url[50];
    struct site* suivant;
} site;

typedef struct Noeud {
    int donnee;
    struct Noeud* suivant;
} Noeud;

typedef struct Rubrique {
    Date date_creation;
    char theme[50];
    char couriel_an[50];
    unsigned int n_messages;
    unsigned int n_sites;
    site* l_sites;  // Liste des sites
    Noeud* l_mesg;  // Liste des messages
    unsigned int id;
    struct Rubrique* suivant;
} rub;

typedef struct Forum {
    char couriel_resp[50];
    char adresse_internet[50];
    unsigned int nb_rubriques;
    Noeud* rubriques;
    unsigned int id;
    struct Forum* suivant;
} frm;

#endif // FORUM_STRUCT_H

