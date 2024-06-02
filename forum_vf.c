#include "Forum_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
unsigned int dernier_id_forum = 0;
unsigned int dernier_id_rubrique = 0;
unsigned int dernier_id_message = 0;
unsigned int dernier_id_auteur = 0;
unsigned int dernier_id_profil = 0;

// Function to input a date
Date saisie_date() {
    Date date_creation;
    printf("Jour : ");
    scanf("%d", &date_creation.tm_mday);
    printf("Mois : ");
    scanf("%d", &date_creation.tm_mon);
    printf("Ann%ce : ",130);
    scanf("%d", &date_creation.tm_year);
    return date_creation;
}
//concernant la structure profil

		// Function to display a profile
		void afficher_profil(prl* profil) {
		    printf("Num%cro d'inscription : %u\n",130, profil->num_inscrit);
		    printf("Nom : %s\n", profil->nom);
		    printf("Pr%cnom : %s\n",130, profil->prenom);
		    printf("Adresse : %s\n", profil->adresse);
		    printf("Courriel : %s\n", profil->couriel);
		    printf("Date de naissance : %d/%d/%d\n", profil->date_naissance.tm_mday,
		           profil->date_naissance.tm_mon, profil->date_naissance.tm_year);
		    printf("Num%cro de t%cl%cphone : %u\n",130,130,138, profil->num_tel);
		}
		
		// Function to input a profile and save it to the file
		prl* saisie_profil(unsigned int num_inscrit) {
		    prl* nouveau_profil = (prl*)malloc(sizeof(prl));
		    if (nouveau_profil == NULL) {
		        fprintf(stderr, "Allocation m%cmoire pour le profil a %cchou%c.\n",130,130,130);
		        exit(EXIT_FAILURE);
		    }
		
		    nouveau_profil->num_inscrit = num_inscrit;
		
		    printf("Nom : ");
		    scanf("%s", nouveau_profil->nom);
		
		    printf("Pr%cnom : ",130);
		    scanf("%s", nouveau_profil->prenom);
		
		    printf("Adresse : ");
		    scanf("%s", nouveau_profil->adresse);
		
		    printf("Courriel : ");
		    scanf("%s", nouveau_profil->couriel);
		
		    printf("Donnez la date de naissance :\n");
		    nouveau_profil->date_naissance = saisie_date();
		
		    printf("Num%cro de t%cl%cphone : ",130,130,130);
		    scanf("%u", &nouveau_profil->num_tel);
		
		    return nouveau_profil;
		}
		//fonction our sauvegarder un profil dans un fichier
		void sauvegarder_profil(FILE* fichier, prl* profil) {
		    if (profil != NULL) {
		        fseek(fichier, 0, SEEK_END);  // Se déplacer à la fin du fichier
		        int result = fprintf(fichier, "%u %s %s %s %s %d %d %d %u\n",
		                             profil->num_inscrit, profil->nom, profil->prenom,
		                             profil->adresse, profil->couriel,
		                             profil->date_naissance.tm_mday,
		                             profil->date_naissance.tm_mon,
		                             profil->date_naissance.tm_year,
		                             profil->num_tel);
		
		        if (result < 0) {
		            fprintf(stderr, "Erreur lors de l'écriture du profil dans le fichier.\n");
		            exit(EXIT_FAILURE);
		        }
		    } else {
		        fprintf(stderr, "Le profil est NULL, impossible de le sauvegarder dans le fichier.\n");
		        exit(EXIT_FAILURE);
		    }
		}
		
		// Function to load a profile from the file
		prl* charger_profil(FILE* fichier) {
		    prl* profil = (prl*)malloc(sizeof(prl));
		    if (profil == NULL) {
		        fprintf(stderr, "Allocation m%cmoire pour le profil a %cchou%c.\n",130,130,130);
		        exit(EXIT_FAILURE);
		    }
		
		    if (fscanf(fichier, "%u %s %s %s %s %d %d %d %u",
		               &profil->num_inscrit, profil->nom,
		               profil->prenom, profil->adresse,
		               profil->couriel,
		               &profil->date_naissance.tm_mday,
		               &profil->date_naissance.tm_mon,
		               &profil->date_naissance.tm_year,
		               &profil->num_tel) != 9) {
		        free(profil);
		        return NULL;  // Échec de la lecture du profil
		    }
		
		    return profil;
		}
		
		// Function to display all profiles from the file
		void afficher_liste_profils(FILE* fichier) {
		    fseek(fichier, 0, SEEK_SET);  // Move to the beginning of the file
		
		    prl* profil = charger_profil(fichier);
			int i;
		    while (profil != NULL) {
		    	i++;
		    	printf("------------------------------------\n");
		    	printf("profil num%cro %d\n\n",130,i);
		    
		        afficher_profil(profil);
		        free(profil);  // Libérer la mémoire allouée pour le profil
		        profil = charger_profil(fichier);  // Charger le prochain profil
		
		        // Vérifier ici si la lecture a réussi avant d'afficher le profil
		        if (profil == NULL) {
		            break;
		        }
		    }
		}
		
		 //function to extract profile from profiles_list
		prl* extraire_profil(FILE* fichier, unsigned int num_inscrit) {
		    fseek(fichier, 0, SEEK_SET);  // Revenir au début du fichier
		
		    prl* profil = charger_profil(fichier);
		
		    while (profil != NULL) {
		        if (profil->num_inscrit == num_inscrit) {
		            return profil;  // Profil trouvé, le renvoyer
		        }
		 
		        free(profil);  // Libérer la mémoire allouée pour le profil
		        profil = charger_profil(fichier);  // Charger le prochain profil
		    }
		
		    return NULL;  // Le profil n'a pas été trouvé
		}
   
      
//concernant la structure auteur        

		//fonction pour saisir un auteur
		aut* saisie_auteur(unsigned int dernierID,FILE* fichier_profils) {
		    unsigned int i;
		    bool T1;
		    prl* profil = (prl*)malloc(sizeof(prl));
		    aut* auteur = (aut*)malloc(sizeof(aut));
		
		    if (auteur == NULL) {
		        fprintf(stderr, "Allocation mémoire pour l'auteur a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    auteur->id = dernierID;
		    
		    printf("Donner le pseudo : ");
		    scanf("%s", auteur->pseudo);
		
		    printf("Donner le nombre de messages : ");
		    scanf("%u", &auteur->nbr_mesg);
		
		    printf("Donnez la date du premier message:\n");
		    auteur->date_mesg1 = saisie_date();
		
		    printf("Donnez la date du deuxième message:\n");
		    auteur->date_mesg2 = saisie_date();
		
		
		    printf("Est-ce que cet auteur a un profil existant ? (1 pour oui, 0 pour non) : ");
		    scanf("%d", &T1);
		
		    if (T1) {
		        do {
		            printf("Donner le num%cro d'inscription du profil associ%c : ",130,130);
		            scanf("%u", &i);
		            if (i < 0 || i > dernier_id_profil) {
		                printf("Num%cro d'inscription invalide !!\n",130);
		            }
		        } while (i < 0 || i > dernier_id_profil);
		
		        auteur->prfl_num_inscrit = i;
		        profil=extraire_profil(fichier_profils,auteur->prfl_num_inscrit);
		        strcpy(auteur->adresse_email, profil->couriel);
		    } else {
		        printf("Saisir le profil associ%c :\n",130);
		        dernier_id_profil++;
		        profil = saisie_profil(dernier_id_profil);
		        auteur->prfl_num_inscrit=dernier_id_profil;
		        sauvegarder_profil(fichier_profils, profil);
				printf("profil ajout%c avec succ%cs!\n",130,130);
		        strcpy(auteur->adresse_email, profil->couriel);
		    }
		
		    fclose(fichier_profils);
		    return auteur;
		}
		
		void afficher_auteur(aut* auteur) {
			printf("profil num%cro %u)\n",130,auteur->id);
		    printf("ID : %u\n", auteur->id);
		    printf("Adresse email : %s\n", auteur->adresse_email);
		    printf("Pseudo : %s\n", auteur->pseudo);
		    printf("Nombre de messages : %u\n", auteur->nbr_mesg);
		    printf("Date du premier message : %d/%d/%d\n", auteur->date_mesg1.tm_mday,
		           auteur->date_mesg1.tm_mon, auteur->date_mesg1.tm_year);
		    printf("Date du deuxi%cme message : %d/%d/%d\n",138, auteur->date_mesg2.tm_mday,
		           auteur->date_mesg2.tm_mon, auteur->date_mesg2.tm_year);
		   
		    // Nom du fichier de profils
		    const char* nom_fichier_profils = "Profils";
		    // Open the file for reading and writing
		    FILE* fichier_profils = fopen(nom_fichier_profils, "a+");
		    printf("Profil associ%c :\n",130);
		    afficher_profil(extraire_profil(fichier_profils, auteur->prfl_num_inscrit));
		    fclose(fichier_profils);
		    }
		
		//fonction pour sauvegarder un auteur dans un fichier
		void sauvegarder_auteur(FILE* fichier, aut* auteur) {
		    if (auteur != NULL) {
		        fseek(fichier, 0, SEEK_END);  // Se déplacer à la fin du fichier
		        int result = fprintf(fichier, "%u %s %s %u %d %d %d %d %d %d %u\n",
		                             auteur->id, 
									 auteur->adresse_email, 
									 auteur->pseudo,
		                             auteur->nbr_mesg,
		                             auteur->date_mesg1.tm_mday,
		                             auteur->date_mesg1.tm_mon,
		                             auteur->date_mesg1.tm_year,
		                             auteur->date_mesg2.tm_mday,
		                             auteur->date_mesg2.tm_mon,
		                             auteur->date_mesg2.tm_year,
		                             auteur->prfl_num_inscrit);
		
		        if (result < 0) {
		            fprintf(stderr, "Erreur lors de l'%ccriture du profil dans le fichier.\n",130);
		            exit(EXIT_FAILURE);
		        }
		    } else {
		        fprintf(stderr, "Le profil est NULL, impossible de le sauvegarder dans le fichier.\n");
		        exit(EXIT_FAILURE);
		    }
		}
		
		// Function to load an auteur from the file
		aut* charger_auteur(FILE* fichier) {
		    aut* auteur = (aut*)malloc(sizeof(aut));
		    if (auteur == NULL) {
		        fprintf(stderr, "Allocation m%cmoire pour le profil a %chou%c.\n",130,130);
		        exit(EXIT_FAILURE);
		    }
		
		    if (fscanf(fichier, "%u %s %s %u %d %d %d %d %d %d %u\n",
		                             &auteur->id, 
									 auteur->adresse_email, 
									 auteur->pseudo,
		                             &auteur->nbr_mesg,
		                             &auteur->date_mesg1.tm_mday,
		                             &auteur->date_mesg1.tm_mon,
		                             &auteur->date_mesg1.tm_year,
		                             &auteur->date_mesg2.tm_mday,
		                             &auteur->date_mesg2.tm_mon,
		                             &auteur->date_mesg2.tm_year,
		                             &auteur->prfl_num_inscrit) != 11) {
		        free(auteur);
		        return NULL;  // Échec de la lecture du profil
		    }
		
		    return auteur;
		}
		
		// Function to display all auteurs from the file
		void afficher_liste_auteurs(FILE* fichier) {
		    fseek(fichier, 0, SEEK_SET);  // Move to the beginning of the file
		
		    aut* auteur = charger_auteur(fichier);
			int i;
		    while (auteur != NULL) {
		    	i++;
		    	printf("------------------------------------\n");
		    	printf("auteur num%cro %d)\n\n\n",130,i);
		    	
		    	
		        afficher_auteur(auteur);
		        free(auteur);  // Libérer la mémoire allouée pour le profil
		        auteur = charger_auteur(fichier);  // Charger le prochain profil
		
		        // Vérifier ici si la lecture a réussi avant d'afficher le profil
		        if (auteur == NULL) {
		            break;
		        }
		    }
		}
		
		 //function to extract auteur from auteurs_list
		aut* extraire_auteur(FILE* fichier, unsigned int id) {
		    fseek(fichier, 0, SEEK_SET);  // Revenir au début du fichier
		
		    aut* auteur = charger_auteur(fichier);
		
		    while (auteur != NULL) {
		        if (auteur->id == id) {
		            return auteur;  // auteur trouvé, le renvoyer
		        }
		 
		        free(auteur);  // Libérer la mémoire allouée pour le profil
		        auteur = charger_auteur(fichier);  // Charger le prochain profil
		    }
		
		    return NULL;  // Le profil n'a pas été trouvé
		}
		// Fonction pour extraire un auteur à partir de son pseudo
		aut* extraire_auteur_par_pseudo(FILE* fichier_auteurs, const char* pseudo) {
		    fseek(fichier_auteurs, 0, SEEK_SET);  // Revenir au début du fichier
		
		    aut* auteur_courant = charger_auteur(fichier_auteurs);
		
		    while (auteur_courant != NULL) {
		        if (strcmp(auteur_courant->pseudo, pseudo) == 0) {
		            return auteur_courant;  // auteur trouvé, le renvoyer
		        }
		
		        free(auteur_courant);  // Libérer la mémoire allouée pour l'auteur
		        auteur_courant = charger_auteur(fichier_auteurs);  // Charger le prochain auteur
		    }
		
		    return NULL;  // L'auteur n'a pas été trouvé
		}


//concernant la structure message

		// Fonction de saisie d'un message
		mesg* saisie_message(unsigned int id) {
		    unsigned int i;
		    bool T;
		    mesg* message = (mesg*)malloc(sizeof(mesg));
			aut* auteur1 = (aut*)malloc(sizeof(aut)) ;
			prl* profil = (prl*)malloc(sizeof(prl));
		    if (message == NULL) {
		        fprintf(stderr, "Allocation mémoire pour le message a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    // Saisie des informations du message
		    message->id = id;
		
		    printf("Saisir le titre du message : ");
		    scanf("%s", message->titre);
		
		    printf("Saisir le texte du message : ");
		    scanf("%s", message->text);
		
		    printf("Saisir la date de publication du message :\n");
		    message->date_pub = saisie_date();
			printf("associ%cr un auteur deja existant %c cet message? (1 si oui 0 sinon)",130,133);
			scanf("%d",&T);
		    if(T){
				    do {
				        printf("Donner l'id de l'auteur associ%c : ",130);
				        scanf("%u", &i);
				        if (i < 0 || i > dernier_id_auteur) {
				            printf("id invalide !!\n"); 
						
				        }	
						
				    } while (i < 0 || i > dernier_id_auteur);
				   	message->auteur_id = i;
			
			
			}else{
					printf("saisie de l'auteur: \n");
					FILE* fichier_auteurs=fopen("Auteurs","a+");
					dernier_id_auteur++;
					FILE* fichier_profils=fopen("Profils","a+");
					auteur1=saisie_auteur(dernier_id_auteur, fichier_profils);
					message->auteur_id=dernier_id_auteur;
					//profil=extraire_profil(fichier1,auteur->prfl_num_inscrit);
					
					sauvegarder_auteur(fichier_auteurs, auteur1);
					
					printf("auteur ajout%c avec succ%cs!\n",130,130);
					fclose(fichier_auteurs);
					fclose(fichier_profils);	
				}
		
		    printf("Ce message est-il une r%cponse (1 pour oui, 0 pour non) : ",130);
		    scanf("%d", &message->isResponse);
		
		    if (message->isResponse) {
		        do {
		            printf("Donner l'ID du message initial : ");
		            scanf("%u", &i);
		            if (i < 0 || i > dernier_id_message) {
		                printf("id invalide !!\n");
		            }
		        } while (i < 0 || i > dernier_id_message);
		        message->id_message_initial = i;
		    } else {
		        message->id_message_initial = 0;
		    }
		
		    return message;
		}
		
		// Fonction pour afficher un message
		void afficher_message(mesg* message) {
		    printf("message id: %u\n", message->id);
		    printf("Titre de message: %s\n", message->titre);
		    printf("Texte de message: %s\n", message->text);
		    printf("Date de publication du message : %d/%d/%d\n", message->date_pub.tm_mday,
		           message->date_pub.tm_mon, message->date_pub.tm_year);
		    printf("Auteur de message :\n");
		
		    // Open the file for reading 
		    FILE* fichier = fopen("Auteurs", "r+");
		    afficher_auteur(extraire_auteur(fichier, message->auteur_id));
		    fclose(fichier);
		
		    if (message->isResponse) {
		        printf("Ce message est une r%cponse au message num%cro : %d\n",130,130, message->id_message_initial);
		    } else {
		        printf("C'est un message initial.\n");
		    }
		}
		
		// Fonction pour sauvegarder un message dans un fichier
		void sauvegarder_message(FILE* fichier, mesg* message) {
		    fprintf(fichier, "%u %s %s %d %d %d %u %u %u\n",
					message->id,
		            message->titre,
		            message->text,
		            message->date_pub.tm_mday,
		            message->date_pub.tm_mon,
		            message->date_pub.tm_year,
		            message->auteur_id,
		            message->isResponse,
		            message->id_message_initial);
		}
		
		// Fonction pour charger un message depuis un fichier
		mesg* charger_message(FILE* fichier) {
		    mesg* message = (mesg*)malloc(sizeof(mesg));
		
		    if (message == NULL) {
		        fprintf(stderr, "Allocation mémoire pour le message a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    if (fscanf(fichier, "%u %s %s %d %d %d %u %u %u",
		               &message->id,
		               message->titre,
		               message->text,
		               &message->date_pub.tm_mday,
		               &message->date_pub.tm_mon,
		               &message->date_pub.tm_year,
		               &message->auteur_id,
		               &message->isResponse,
		               &message->id_message_initial) != 9) {
		        free(message);
		        return NULL;  // Échec de la lecture du message
		    }
		
		    return message;
		}
		
		// Fonction pour afficher tous les messages dans un fichier
		void afficher_liste_messages(FILE* fichier_messages) {
		    fseek(fichier_messages, 0, SEEK_SET);  // Move to the beginning of the file
		
		    mesg* message = charger_message(fichier_messages);
			int i;
		    while (message != NULL) {
		    	i++;
		    	printf("------------------------------------\n");
		    	printf("message num%cro %d)\n\n\n\n",130,i);
		        afficher_message(message);
		        free(message);  // Libérer la mémoire allouée pour le message
		        message = charger_message(fichier_messages);  // Charger le prochain message
		
		        // Vérifier ici si la lecture a réussi avant d'afficher le message
		        if (message == NULL) {
		            break;
		        }
		    }
		}
		
		// Fonction pour extraire un message à partir du titre
		mesg* extraire_message_par_titre(FILE* fichier_messages, const char* titre) {
		    fseek(fichier_messages, 0, SEEK_SET);  // Revenir au début du fichier
		
		    mesg* message = charger_message(fichier_messages);
		
		    while (message != NULL) {
		        if (strcmp(message->titre, titre) == 0) {
		            return message;  // Message trouvé, le renvoyer
		        }
		
		        free(message);  // Libérer la mémoire allouée pour le message
		        message = charger_message(fichier_messages);  // Charger le prochain message
		    }
		
		    return NULL;  // Le message n'a pas été trouvé
		}
		
		// Fonction pour extraire un message à partir de l id
		mesg* extraire_message(FILE* fichier_messages, unsigned int id) {
		    fseek(fichier_messages, 0, SEEK_SET);  // Revenir au début du fichier
		
		    mesg* message = charger_message(fichier_messages);
		
		    while (message != NULL) {
		        if (message->id == id) {
		            return message;  // message trouvé, le renvoyer
		        }
		
		        free(message);  // Libérer la mémoire allouée pour le message
		        message = charger_message(fichier_messages);  // Charger le prochain message
		    }
			fclose(fichier_messages);
		    return NULL;  // Le message n'a pas été trouvé
		}
		
		// Fonction pour afficher tous les messages en réponse à un message donné
		void afficher_messages_reponse(FILE* fichier_messages, unsigned int id_message_initial) {
		    fseek(fichier_messages, 0, SEEK_SET);  // Revenir au début du fichier
			unsigned int i=0;
		    mesg* message = charger_message(fichier_messages);
		    bool found = false;
		
		    while (message != NULL) {
		        if (message->isResponse && message->id_message_initial == id_message_initial) {
		        	i++;
		            if (!found) {
		                printf("Messages en r%cponse au message #%u :\n",130, id_message_initial);
		                found = true;
		            }
		
		            printf("\nR%cponse #%u :\n",130, i);
		            afficher_message(message);
		        }
		
		        free(message);  // Libérer la mémoire allouée pour le message
		        message = charger_message(fichier_messages);  // Charger le prochain message
		    }
		
		    if (!found) {
		        printf("Aucune réponse trouvée pour le message #%u.\n", id_message_initial);
		    }
		}
		// Fonction pour afficher tous les messages d'une date donnée
		void afficher_messages_par_date(FILE* fichier_messages, struct tm date_recherche) {
		    fseek(fichier_messages, 0, SEEK_SET);  // Revenir au début du fichier
		
		    mesg* message = charger_message(fichier_messages);
		    bool found = false;
		
		    printf("Messages de la date %d/%d/%d :\n", date_recherche.tm_mday, date_recherche.tm_mon, date_recherche.tm_year);
		
		    while (message != NULL) {
		        if (compare_dates(message->date_pub, date_recherche) == 0) {
		            if (!found) {
		                found = true;
		            }
		
		            printf("\nMessage #%u :\n", message->id);
		            afficher_message(message);
		        }
		
		        free(message);  // Libérer la mémoire allouée pour le message
		        message = charger_message(fichier_messages);  // Charger le prochain message
		    }
		
		    if (!found) {
		        printf("Aucun message trouvé pour la date %d/%d/%d.\n", date_recherche.tm_mday, date_recherche.tm_mon, date_recherche.tm_year);
		    }
		}
		
		
		// Fonction pour comparer deux structures tm (dates)
		int compare_dates(struct tm date1, struct tm date2) {
		    if (date1.tm_year < date2.tm_year) return -1;
		    if (date1.tm_year > date2.tm_year) return 1;
		    if (date1.tm_mon < date2.tm_mon) return -1;
		    if (date1.tm_mon > date2.tm_mon) return 1;
		    if (date1.tm_mday < date2.tm_mday) return -1;
		    if (date1.tm_mday > date2.tm_mday) return 1;
		    return 0;  // Les dates sont égales
		}
		// Fonction de comparaison pour les dates de création des messages
		int comparer_dates_creation(const void* a, const void* b) {
		    const mesg* message1 = *(const mesg**)a;
		    const mesg* message2 = *(const mesg**)b;
		
		    // Comparaison des dates de création
		    if (message1->date_pub.tm_year != message2->date_pub.tm_year) {
		        return message1->date_pub.tm_year - message2->date_pub.tm_year;
		    } else if (message1->date_pub.tm_mon != message2->date_pub.tm_mon) {
		        return message1->date_pub.tm_mon - message2->date_pub.tm_mon;
		    } else {
		        return message1->date_pub.tm_mday - message2->date_pub.tm_mday;
		    }
		}
		// Fonction pour afficher tous les messages d'un auteur à partir de son pseudo
		void afficher_messages_par_auteur(FILE* fichier_messages, FILE* fichier_auteurs, aut* auteur) {
		    if (fichier_messages == NULL || fichier_auteurs == NULL) {
		        fprintf(stderr, "Erreur : pointeur de fichier invalide.\n");
		        return;
		    }
		
		    fseek(fichier_messages, 0, SEEK_SET);  // Revenir au début du fichier
		
		    mesg* message = charger_message(fichier_messages);
		    bool found = false;
		
		    printf("Messages de l'auteur \"%s\" :\n", auteur->pseudo);
			unsigned int i;
		    for (i = 1; message != NULL; ++i) {
		        if (message->auteur_id == auteur->id) {
		            if (!found) {
		                found = true;
		            }
		
		            printf("\nMessage #%u :\n", i);
		            afficher_message(message);
		        }
		
		        free(message);  // Libérer la mémoire allouée pour le message
		        message = charger_message(fichier_messages);  // Charger le prochain message
		    }
		
		    if (!found) {
		        printf("Aucun message trouvé pour l'auteur \"%s\".\n", auteur->pseudo);
		    }
		}
		
		// Fonction pour afficher tous les messages d'un profil à partir de son numéro d'inscription
		void afficher_messages_par_profil(FILE* fichier_messages, FILE* fichier_auteurs, FILE* fichier_profils, unsigned int num_inscrit) {
		    fseek(fichier_profils, 0, SEEK_SET);  // Revenir au début du fichier
		
		    prl* profil_recherche = extraire_profil(fichier_profils, num_inscrit);
		
		    if (profil_recherche == NULL) {
		        fprintf(stderr, "Profil avec le numéro d'inscription #%u introuvable.\n", num_inscrit);
		        return;
		    }
		
		    fseek(fichier_messages, 0, SEEK_SET);  // Revenir au début du fichier
		
		    mesg* message = charger_message(fichier_messages);
		    bool found = false;
		    unsigned int i=0;
		
		    printf("Messages du profil #%u :\n", num_inscrit);
		
		    while (message != NULL) {
		        aut* auteur_message = extraire_auteur(fichier_auteurs, message->auteur_id);
		
		        if (auteur_message != NULL && auteur_message->prfl_num_inscrit == num_inscrit) {
		            if (!found) {
		                found = true;
		            }
					i++;
		            printf("\nMessage #%u :\n", i);
		            afficher_message(message);
		        }
		
		        free(auteur_message);  // Libérer la mémoire allouée pour l'auteur
		        free(message);  // Libérer la mémoire allouée pour le message
		        message = charger_message(fichier_messages);  // Charger le prochain message
		    }
		
		    if (!found) {
		        printf("Aucun message trouvé pour le profil #%u.\n", num_inscrit);
		    }
		
		    free(profil_recherche);  // Libérer la mémoire allouée pour le profil
		}


//concernant la structure rubrique

		void ajouter_site_liste(site** debut, const char* url);
		
		rub* rubs = NULL;  // Liste chaînée de rubriques
		
		void ajouter_Id_liste(Noeud** debut,int id) {
		    Noeud* nouveau_noeud = (Noeud*)malloc(sizeof(Noeud));
		    if (nouveau_noeud == NULL) {
		        fprintf(stderr, "Allocation mémoire pour le nouveau nœud a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    nouveau_noeud->donnee = id;
		    nouveau_noeud->suivant = NULL;
		
		    if (*debut == NULL) {
		        *debut = nouveau_noeud;
		    } else {
		        Noeud* courant = *debut;
		        while (courant->suivant != NULL) {
		            courant = courant->suivant;
		        }
		        courant->suivant = nouveau_noeud;
		    }
		}
		
		// Libérer la mémoire de la liste chaînée
		void liberer_liste_messages(Noeud* debut) {
		    Noeud* courant = debut;
		    while (courant != NULL) {
		        Noeud* suivant = courant->suivant;
		        free(courant);
		        courant = suivant;
		    }
		}
		
		//fonction pour charger une rubrique a partir d un fichier
		rub* charger_rubrique(FILE* fichier) {
		    rub* nouvelle_rubrique = (rub*)malloc(sizeof(rub));
		    if (nouvelle_rubrique == NULL) {
		        fprintf(stderr, "Allocation mémoire pour la rubrique a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    if (fscanf(fichier, "%u %d/%d/%d %s %s %u",
		               &nouvelle_rubrique->id,
		               &nouvelle_rubrique->date_creation.tm_mday,
		               &nouvelle_rubrique->date_creation.tm_mon,
		               &nouvelle_rubrique->date_creation.tm_year,
		               nouvelle_rubrique->theme,
		               nouvelle_rubrique->couriel_an,
		               &nouvelle_rubrique->n_messages) != 7) {
		        free(nouvelle_rubrique);
		        return NULL;
		    }
		
		    nouvelle_rubrique->l_sites = NULL;
		    nouvelle_rubrique->l_mesg = NULL;
			
			char url[50];
		    while (fscanf(fichier, "%s", url) == 1) {
		        if (strcmp(url, "fin") == 0) {
		            break;
		        }
		        ajouter_site_liste(&nouvelle_rubrique->l_sites, url);
		    }
		
		    unsigned int i,j;
		    for (i = 0; i < nouvelle_rubrique->n_messages; i++) {
		        fscanf(fichier, "%u", &j);
		        ajouter_Id_liste(&nouvelle_rubrique->l_mesg, j);
		    }
		
		    return nouvelle_rubrique;
		}
		
		
		
		//fonction qui sauvegarde un rubriquer dans un fichier
		void sauvegarder_rubrique(FILE* fichier, rub* rubrique) {
		    fprintf(fichier, "%u %d/%d/%d %s %s %u\n",
		            rubrique->id,
		            rubrique->date_creation.tm_mday,
		            rubrique->date_creation.tm_mon,
		            rubrique->date_creation.tm_year,
		            rubrique->theme,
		            rubrique->couriel_an,
					rubrique->n_messages);
		
		    site* site_courant = rubrique->l_sites;
		    while (site_courant != NULL) {
		        fprintf(fichier, "%s\n", site_courant->url);
		        site_courant = site_courant->suivant;
		    }
		    fprintf(fichier, "fin\n");
		
		    unsigned int i;
		    Noeud* messages = rubrique->l_mesg;
		    while (messages != NULL) {
		        fprintf(fichier, "%u\n", messages->donnee);
		        messages = messages->suivant;
		    }
		}
		//fonction qui assure l ajout d un site dans une liste chainée
		void ajouter_site_liste(site** debut, const char* url) {
		    site* nouveau_site = (site*)malloc(sizeof(site));
		    if (nouveau_site == NULL) {
		        fprintf(stderr, "Allocation mémoire pour le site a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    strcpy(nouveau_site->url, url);
		    nouveau_site->suivant = *debut;
		    *debut = nouveau_site;
		}
		
		//fonction pour saisir une rubrique
		rub* saisie_rubrique(unsigned int id) {
		    unsigned int v,i;
		    bool T;
		    rub* nouvelle_rubrique = (rub*)malloc(sizeof(rub));
		    mesg* message = (mesg*)malloc(sizeof(mesg));
		    //aut* auteur1 = (aut*)malloc(sizeof(aut)) ;
			//prl* profil = (prl*)malloc(sizeof(prl));
		    if (nouvelle_rubrique == NULL) {
		        fprintf(stderr, "Allocation mémoire pour la rubrique a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
			nouvelle_rubrique->id = id;
			
		    printf("Donner la date de cr%cation de la rubrique :\n",130);
		    nouvelle_rubrique->date_creation = saisie_date();
		
		    printf("Saisir le th%cme de la rubrique : \n",138);
		    scanf("%s", nouvelle_rubrique->theme);
		
		    printf("Saisir le courriel : \n");
		    scanf("%s", nouvelle_rubrique->couriel_an);
		
		    printf("Saisir le nombre de messages pour la rubrique : \n");
		    scanf("%u", &nouvelle_rubrique->n_messages);
		
		    nouvelle_rubrique->l_sites = NULL;
		    nouvelle_rubrique->l_mesg = NULL;
		
		    printf("\nSaisir les sites pour la rubrique (saisir 'fin' pour terminer) :\n");
		    char url[50];
		    while (1) {
		        scanf("%s", url);
		        if (strcmp(url, "fin") == 0) {
		            break;
		        }
		        ajouter_site_liste(&nouvelle_rubrique->l_sites, url);
		    }
		
		    printf("\nSaisir les messages pour la rubrique :\n");
			FILE* fichier3 = fopen("Messages", "a+");
			FILE* fichier_auteurs=fopen("Auteurs","a+");
			FILE* fichier_profils=fopen("Profils","a+");
			for (i = 0; i < nouvelle_rubrique->n_messages; i++){
				printf("associer un message (deja existant) %c cette rubrique?(1 si oui 0 sinon)\n ",133);
				scanf("%d",&T);
				
				if(T==0){
			     	printf("saisie du message (non existant) num%cro %u: \n",130,i+1);
			        dernier_id_message++;
			        mesg* message = saisie_message(dernier_id_message);
			        ajouter_Id_liste(&nouvelle_rubrique->l_mesg, dernier_id_message);
			        sauvegarder_message(fichier3, message);
			    }
			    else{
			    	do{
					
				    	printf("saisie du message deja existant num%cro %u: \n\n",130,i+1);
				    	printf("donner l'id du message %c associer\n",133);
				    	scanf("%u",&v);
				    	if (v < 0 || v > dernier_id_message) {
				        	printf("id invalide !!\n"); 
				        }
						ajouter_Id_liste(&nouvelle_rubrique->l_mesg,v);	
						
				    } while (v < 0 || v > dernier_id_auteur);
				   		    	
				}
				}
			fclose(fichier3);
		    return nouvelle_rubrique;
		}
		
		
		//fonction qui affiche une rubrique donner 
		void afficher_rubrique(rub* rubrique) {
		    unsigned int i;
		    printf("Th%cme de la rubrique : %s\n",138 ,rubrique->theme);
		    printf("Date de cr%cation de la rubrique : %d/%d/%d\n",130, rubrique->date_creation.tm_mday,
		           rubrique->date_creation.tm_mon, rubrique->date_creation.tm_year);
		    printf("Courriel : %s\n", rubrique->couriel_an);
		
		    printf("\nSites dans la rubrique :\n\n");
		    site* site_courant = rubrique->l_sites;
		    while (site_courant != NULL) {
		        printf("- %s\n", site_courant->url);
		        site_courant = site_courant->suivant;
		    }
		
			printf("\nMessages dans la rubrique :\n\n");
			    FILE* fichier3 = fopen("Messages", "r");
			    Noeud* messages = rubrique->l_mesg;
			    while (messages != NULL) {
			        afficher_message(extraire_message(fichier3, messages->donnee));
			        printf("\n");
			        messages = messages->suivant;
			    }
			
			    fclose(fichier3);
			}
		//fonction qui affiche tous les rubriques
		void afficher_liste_rubriques(FILE* fichier) {
			fseek(fichier, 0, SEEK_SET);  // Move to the beginning of the file
		    rub* rubrique = charger_rubrique(fichier);
		    int j;
		    while (rubrique != NULL) {
		    	j++;
		    	printf("------------------------------------\n");
		    	printf("rubrique num%cro %d)\n\n\n\n",130,j);
		        afficher_rubrique(rubrique);
		        free(rubrique);  // Libérer la mémoire allouée pour la rubrique
		        rubrique = charger_rubrique(fichier);  // Charger une autre rubrique
		
		        // Vérifier ici si la lecture a réussi avant d'afficher la rubrique
		        if (rubrique == NULL) {
		            break;
		        }
		    }
		}
		
		
		
		rub* extraire_rubrique(FILE* fichier, unsigned int id) {
		    fseek(fichier, 0, SEEK_SET);  // Revenir au début du fichier
		
		    rub* rubrique = charger_rubrique(fichier);
		
		    while (rubrique != NULL) {
		        if (rubrique->id == id) {
		            return rubrique;  // rubrique trouvé, la renvoyer
		        }
		
		        free(rubrique);  // Libérer la mémoire allouée pour la rubrique
		        rubrique = charger_rubrique(fichier);  
		    }
		
		    return NULL;  // La rubrique n'a pas été trouvée
		}
		// Fonction pour extraire une rubrique à partir du thème
		rub* extraire_rubrique_par_theme(FILE* fichier_rubriques, const char* theme) {
		    fseek(fichier_rubriques, 0, SEEK_SET);  // Revenir au début du fichier
		
		    rub* rubrique = charger_rubrique(fichier_rubriques);
		
		    while (rubrique != NULL) {
		        if (strcmp(rubrique->theme, theme) == 0) {
		            return rubrique;  // Thème trouvé, renvoyer la rubrique
		        }
		
		        free(rubrique);  // Libérer la mémoire allouée pour la rubrique
		        rubrique = charger_rubrique(fichier_rubriques);  // Charger la prochaine rubrique
		    }
		
		    return NULL;  // La rubrique avec le thème spécifié n'a pas été trouvée
		}              
		              
		void afficher_messages_rubrique(FILE* fichier_messages, rub* rubrique) {
		    if (rubrique == NULL) {
		        fprintf(stderr, "Rubrique invalide.\n");
		        return;
		    }
		
		    printf("Messages dans la rubrique \"%s\" :\n", rubrique->theme);
		
		    Noeud* messages = rubrique->l_mesg;
		    while (messages != NULL) {
		        unsigned int id_message = messages->donnee;
		        mesg* message = extraire_message(fichier_messages, id_message);
		
		        if (message != NULL) {
		            printf("\nMessage #%u:\n", id_message);
		            afficher_message(message);
		            printf("\n");
		            free(message);  // Libérer la mémoire allouée pour le message
		        } else {
		            fprintf(stderr, "Message #%u introuvable.\n", id_message);
		        }
		
		        messages = messages->suivant;
		    }
		}   
		// Fonction pour afficher les messages dans une rubrique par ordre chronologique
		void afficher_messages_rubrique_ordre_chronologique(FILE* fichier_messages, rub* rubrique) {
		    if (rubrique == NULL) {
		        fprintf(stderr, "Rubrique invalide.\n");
		        return;
		    }
		
		    printf("Messages dans la rubrique \"%s\" par ordre chronologique :\n", rubrique->theme);
		
		    // Créer un tableau pour stocker les pointeurs vers les messages
		    mesg** tableau_messages = (mesg**)malloc(rubrique->n_messages * sizeof(mesg*));
		    if (tableau_messages == NULL) {
		        fprintf(stderr, "Allocation mémoire pour le tableau de messages a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    // Remplir le tableau avec les pointeurs vers les messages
		    Noeud* messages = rubrique->l_mesg;
		    int i = 0;
		    while (messages != NULL) {
		        tableau_messages[i] = extraire_message(fichier_messages, messages->donnee);
		        messages = messages->suivant;
		        i++;
		    }
		
		    // Trier le tableau des messages en fonction de la date de création
		    qsort(tableau_messages, rubrique->n_messages, sizeof(mesg*), comparer_dates_creation);
		
		    // Afficher les messages triés
		    for (i = 0; i < rubrique->n_messages; i++) {
		        afficher_message(tableau_messages[i]);
		        printf("\n");
		        free(tableau_messages[i]);  // Libérer la mémoire allouée pour le message
		    }
		
		    free(tableau_messages);  // Libérer la mémoire allouée pour le tableau de pointeurs
		}
		           
		// Fonction pour afficher tous les profils qui ont posté dans une rubrique donnée
		void afficher_profils_rubrique(FILE* fichier_rubriques, FILE* fichier_messages, FILE* fichier_auteurs, FILE* fichier_profils,rub* rubrique) {
		
		    printf("Profils ayant posté dans la rubrique \"%s\" :\n", rubrique->theme);
		
		    Noeud* messages = rubrique->l_mesg;
		    while (messages != NULL) {
		        unsigned int id_message = messages->donnee;
		        mesg* message = extraire_message(fichier_messages, id_message);
		
		        if (message != NULL) {
		            aut* auteur_message = extraire_auteur(fichier_auteurs, message->auteur_id);
		            if (auteur_message != NULL) {
		                prl* profil_auteur = extraire_profil(fichier_profils, auteur_message->prfl_num_inscrit);
		                if (profil_auteur != NULL) {
		                    printf("\nProfil #%u :\n", profil_auteur->num_inscrit);
		                    afficher_profil(profil_auteur);
		                    free(profil_auteur);  // Libérer la mémoire allouée pour le profil
		                }
		                free(auteur_message);  // Libérer la mémoire allouée pour l'auteur
		            }
		            free(message);  // Libérer la mémoire allouée pour le message
		        }
		
		        messages = messages->suivant;
		    }
		}              
                  
      
//concernant la structure forum          

		//fonction qui sauvegarde le forum dans un fichier
		void sauvegarder_forum(FILE* fichier, frm* forum) {
		    fprintf(fichier, "%u %s %s %u\n",
		            forum->id,
		            forum->adresse_internet,
		            forum->couriel_resp,
		            forum->nb_rubriques);
		    Noeud* rubriques = forum->rubriques;
		    while (rubriques != NULL) {
		        fprintf(fichier, "%u\n",rubriques->donnee);
		        rubriques = rubriques->suivant;
		    }
		}
		
		//fonction pour charger un forum a partir d un fichier
		frm* charger_forum(FILE* fichier) {
		    frm* forum = (frm*)malloc(sizeof(frm));
		    if (forum == NULL) {
		        fprintf(stderr, "Allocation mémoire pour le forum a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		
		    unsigned int nb_rubriques;  // Ajouter une variable temporaire
		    if (fscanf(fichier, "%u %s %s %u\n",
		            &forum->id,
		            forum->adresse_internet,
		            forum->couriel_resp,
		            &nb_rubriques) != 4) {
		        free(forum);
		        return NULL;
		    }
		
		    forum->nb_rubriques = nb_rubriques;  // Affecter la valeur à forum->nb_rubriques
		    forum->rubriques = NULL;
		    unsigned int i, j;
		    for (i = 0; i < forum->nb_rubriques; i++) {
		        fscanf(fichier, "%u", &j);
		        ajouter_Id_liste(&forum->rubriques, j);
		    }
		
		    return forum;
		}
		// Fonction pour saisir un forum
		frm* saisie_forum(unsigned int id) {
			unsigned int v,i,T;
		    frm* nouveau_forum = (frm*)malloc(sizeof(frm));
		    if (nouveau_forum == NULL) {
		        fprintf(stderr, "Allocation mémoire pour le forum a échoué.\n");
		        exit(EXIT_FAILURE);
		    }
		    nouveau_forum->id = id;
		
		    printf("Tapez le courriel du responsable : ");
		    scanf("%s", nouveau_forum->couriel_resp);
		
		    printf("Tapez l'adresse internet du forum : ");
		    scanf("%s", nouveau_forum->adresse_internet);
		
		    printf("Tapez le nombre de rubriques dans le forum : ");
		    scanf("%u", &nouveau_forum->nb_rubriques);
		
		    // Initialiser la liste chaînée de rubriques à NULL
		    nouveau_forum->rubriques = NULL;
		
		    printf("Saisie des rubriques pour le forum :\n");
		    FILE* fichier_rubriques = fopen("Rubriques", "a+");
		    for (i = 0; i < nouveau_forum->nb_rubriques; i++) {
		        printf("rubrique num%cro %u :\n",130, i + 1);
		        printf("associer un message (deja existant) %c cette rubrique?(1 si oui 0 sinon)\n ",133);
				scanf("%d",&T);
				
				if(T==1){
						do{
					    	printf("ajout d une rubrique deja existante num%cro %u: \n\n",130,i+1);
					    	printf("donner l'id de la rubrique %c associer\n",133);
					    	scanf("%u",&v);
					    	if (v < 0 || v > dernier_id_rubrique) {
					        	printf("id invalide !!\n"); 
					        }
							ajouter_Id_liste(&nouveau_forum->rubriques,v);	
						
				    	} while (v < 0 || v > dernier_id_rubrique);
			    }
			    else{
				    dernier_id_rubrique++;
				    rub* rubrique = saisie_rubrique(dernier_id_rubrique);
				    ajouter_Id_liste(&nouveau_forum->rubriques, dernier_id_rubrique);
				    sauvegarder_rubrique(fichier_rubriques, rubrique);
		    	}
				fclose(fichier_rubriques);
			}
		    return nouveau_forum;
		}
		// Fonction pour afficher un forum
		void afficher_forum(frm* forum) {
		    printf("Adresse internet du forum : %s\n", forum->adresse_internet);
		    printf("Courriel du responsable de forum : %s\n", forum->couriel_resp);
		    printf("Rubriques du forum :\n");
			printf("\nRubriques dans le forum :\n");
		    FILE* fichier_rubriques = fopen("Rubriques", "r");
		    Noeud* rubrique = forum->rubriques;
		    while (rubrique != NULL) {
		        afficher_rubrique(extraire_rubrique(fichier_rubriques, rubrique->donnee));
		        printf("\n");
		        rubrique = rubrique->suivant;
		    }
		
		    fclose(fichier_rubriques);
		}
		
		
		void afficher_liste_forums(FILE* fichier) {
			fseek(fichier, 0, SEEK_SET);  // Move to the beginning of the file
		    frm* forum; // Déplacer la déclaration à l'intérieur de la boucle
		    int i;
			while ((forum = charger_forum(fichier)) != NULL) {
			    while (forum != NULL) {
			    	i++;
			    	printf("------------------------------------\n");
		    		printf("forum num%cro %d)\n\n\n",130,i);
			        afficher_forum(forum);
			        free(forum);  // Libérer la mémoire allouée pour le forum
			        forum = charger_forum(fichier);  // Charger un autre forum
			
			        // Vérifier ici si la lecture a réussi avant d'afficher la rubrique
			        if (forum == NULL) {
			            break;
			        }
			    }
			}
		
		}
		
		frm* extraire_forum(FILE* fichier, unsigned int id) {
		    fseek(fichier, 0, SEEK_SET);  // Revenir au début du fichier
		
		    frm* forum = charger_forum(fichier);
		
		    while (forum != NULL) {
		        if (forum->id == id) {
		            return forum;  // forum trouvé, la renvoyer
		        }
		
		        free(forum);  // Libérer la mémoire allouée pour le forum
		        forum = charger_forum(fichier);  
		    }
		
		    return NULL;  // Le forum n'a pas été trouvée
		}
		// Fonction pour extraire un forum à partir du courriel du responsable
		frm* extraire_forum_par_responsable(FILE* fichier_forums, const char* courriel_resp) {
		    fseek(fichier_forums, 0, SEEK_SET);  // Revenir au début du fichier
		
		    frm* forum = charger_forum(fichier_forums);
		
		    while (forum != NULL) {
		        if (strcmp(forum->couriel_resp, courriel_resp) == 0) {
		            return forum;  // Forum trouvé, le renvoyer
		        }
		
		        free(forum);  // Libérer la mémoire allouée pour le forum
		        forum = charger_forum(fichier_forums);  // Charger le prochain forum
		    }
		
		    return NULL;  // Le forum n'a pas été trouvé
		}


//concernant la fonction stat
		// Fonction pour obtenir le nombre de messages postés par jour
		void nombre_messages_par_jour(FILE* fichier_messages) {
		    fseek(fichier_messages, 0, SEEK_SET);
		
		    int messages_par_jour[32] = {0};  // Tableau pour stocker le nombre de messages pour chaque jour
		    mesg* message = charger_message(fichier_messages);
		
		    while (message != NULL) {
		        messages_par_jour[message->date_pub.tm_mday]++;
		        free(message);
		        message = charger_message(fichier_messages);
		    }
		
		    printf("\nNombre de messages postés par jour :\n");
		    int i;
		    for (i = 1; i <= 31; i++) {
		        if (messages_par_jour[i] > 0) {
		            printf("Jour %d : %d messages\n", i, messages_par_jour[i]);
		        }
		    }
		}
		
		// Fonction pour obtenir la moyenne de messages par auteur
		void moyenne_messages_par_auteur(FILE* fichier_messages) {
		    fseek(fichier_messages, 0, SEEK_SET);
		
		    int nombre_messages_par_auteur[100] = {0};  // Tableau pour stocker le nombre de messages par auteur
		    int nombre_auteurs = 0;
		    mesg* message = charger_message(fichier_messages);
		
		    while (message != NULL) {
		        nombre_messages_par_auteur[message->auteur_id]++;
		        free(message);
		        message = charger_message(fichier_messages);
		    }
			int i;
		    for (i = 0; i < 100; i++) {
		        if (nombre_messages_par_auteur[i] > 0) {
		            nombre_auteurs++;
		        }
		    }
		
		    float moyenne = (float)nombre_auteurs > 0 ? (float)dernier_id_message / nombre_auteurs : 0;
		
		    printf("\nMoyenne de messages par auteur : %.2f messages\n", moyenne);
		}
		
		// Fonction pour obtenir le jour de la semaine avec la plus grande fréquentation
		void jour_semaine_plus_frequent(FILE* fichier_messages) {
		    fseek(fichier_messages, 0, SEEK_SET);
		
		    int messages_par_jour_semaine[7] = {0};  // Tableau pour stocker le nombre de messages pour chaque jour de la semaine
		    mesg* message = charger_message(fichier_messages);
		
		    while (message != NULL) {
		        // tm_wday représente le jour de la semaine (0 = dimanche, 1 = lundi, ..., 6 = samedi)
		        messages_par_jour_semaine[message->date_pub.tm_wday]++;
		        free(message);
		        message = charger_message(fichier_messages);
		    }
		
		    int jour_plus_frequent = 0;
		    int messages_plus_frequent = messages_par_jour_semaine[0];
			int i;
		    for (i = 1; i < 7; i++) {
		        if (messages_par_jour_semaine[i] > messages_plus_frequent) {
		            jour_plus_frequent = i;
		            messages_plus_frequent = messages_par_jour_semaine[i];
		        }
		    }
		
		    printf("\nJour de la semaine avec la plus grande fréquentation : ");
		    switch (jour_plus_frequent) {
		        case 0:
		            printf("Dimanche\n");
		            break;
		        case 1:
		            printf("Lundi\n");
		            break;
		        case 2:
		            printf("Mardi\n");
		            break;
		        case 3:
		            printf("Mercredi\n");
		            break;
		        case 4:
		            printf("Jeudi\n");
		            break;
		        case 5:
		            printf("Vendredi\n");
		            break;
		        case 6:
		            printf("Samedi\n");
		            break;
		    }
		}
		
		// Fonction pour obtenir le nombre de messages par rubrique
		void nombre_messages_par_rubrique(FILE* fichier_rubriques, FILE* fichier_messages) {
		    fseek(fichier_rubriques, 0, SEEK_SET);
		
		    rub* rubrique = charger_rubrique(fichier_rubriques);
		    while (rubrique != NULL) {
		        int nombre_messages = 0;
		        Noeud* messages = rubrique->l_mesg;
		        while (messages != NULL) {
		            unsigned int id_message = messages->donnee;
		            mesg* message = extraire_message(fichier_messages, id_message);
		            if (message != NULL) {
		                nombre_messages++;
		                free(message);
		            }
		            messages = messages->suivant;
		        }
		
		        printf("\nRubrique \"%s\" : %d messages\n", rubrique->theme, nombre_messages);
		
		        free(rubrique);
		        rubrique = charger_rubrique(fichier_rubriques);
		    }
		}
		
		// Fonction pour obtenir la taille moyenne des textes de messages par rubrique
		void taille_moyenne_textes_par_rubrique(FILE* fichier_rubriques, FILE* fichier_messages) {
		    fseek(fichier_rubriques, 0, SEEK_SET);
		
		    rub* rubrique = charger_rubrique(fichier_rubriques);
		    while (rubrique != NULL) {
		        int taille_totale = 0;
		        int nombre_messages = 0;
		        Noeud* messages = rubrique->l_mesg;
		        while (messages != NULL) {
		            unsigned int id_message = messages->donnee;
		            mesg* message = extraire_message(fichier_messages, id_message);
		            if (message != NULL) {
		                taille_totale += strlen(message->text);
		                nombre_messages++;
		                free(message);
		            }
		            messages = messages->suivant;
		        }
		
		        float taille_moyenne = (nombre_messages > 0) ? (float)taille_totale / nombre_messages : 0;
		
		        printf("\nRubrique \"%s\" : Taille moyenne des textes : %.2f caractères\n", rubrique->theme, taille_moyenne);
		
		        free(rubrique);
		        rubrique = charger_rubrique(fichier_rubriques);
		    }
		}
		
		// Fonction pour effectuer des statistiques complètes
		void stat(FILE* fichier_rubriques, FILE* fichier_messages, FILE* fichier_auteurs) {
		    printf("\n--- Statistiques Basiques ---\n");
		    nombre_messages_par_jour(fichier_messages);
		    moyenne_messages_par_auteur(fichier_messages);
		    jour_semaine_plus_frequent(fichier_messages);
		    nombre_messages_par_rubrique(fichier_rubriques, fichier_messages);
		    taille_moyenne_textes_par_rubrique(fichier_rubriques, fichier_messages);
		}


//concernat le main
		int main() {
		    unsigned int choix, choix2, id_forum, id_rubrique, id_profil, id_auteur, id_message;
		    frm forum;
		    prl profil;
		    rub rubrq;
		    aut auteur;
		    mesg message;
		
		    const char* nom_fichier_message = "Messages";
		    FILE* fichier_messages = fopen(nom_fichier_message, "a+");
		
		    // Vérification de l'ouverture du fichier de messages
		    if (fichier_messages == NULL) {
		        fprintf(stderr, "Impossible d'ouvrir le fichier de messages.\n");
		        return EXIT_FAILURE;
		    }
		
		    // Positionnement du curseur au début du fichier et comptage des messages existants
		    fseek(fichier_messages, 0, SEEK_SET);
		    while (charger_message(fichier_messages) != NULL) {
		        dernier_id_message++;
		    }
			
		    const char* nom_fichier_profil = "Profils";
		    FILE* fichier_profils = fopen(nom_fichier_profil, "a+");
			// Vérification de l'ouverture du fichier de profils
		    if (fichier_profils == NULL) {
		        fprintf(stderr, "Impossible d'ouvrir le fichier de profils.\n");
		        return EXIT_FAILURE;
		    }
			// Positionnement du curseur au début du fichier et comptage des profils existants
		    fseek(fichier_profils, 0, SEEK_SET);
		    while (charger_profil(fichier_profils) != NULL) {
		        dernier_id_profil++;
		    }
			
		    const char* nom_fichier_auteur = "Auteurs";
		    FILE* fichier_auteurs = fopen(nom_fichier_auteur, "a+");
			// Vérification de l'ouverture du fichier d auteurs
		    if (fichier_auteurs == NULL) {
		        fprintf(stderr, "Impossible d'ouvrir le fichier des profils.\n");
		        return EXIT_FAILURE;
		    }
			// Positionnement du curseur au début du fichier et comptage des auteurs existants
		    fseek(fichier_auteurs, 0, SEEK_SET);
		    while (charger_auteur(fichier_auteurs) != NULL) {
		        dernier_id_auteur++;
		    }
			
		    const char* nom_fichier_rubriques = "Rubriques";
		    FILE* fichier_rubriques = fopen(nom_fichier_rubriques, "a+");
			// Vérification de l'ouverture du fichier de rubriques
		    if (fichier_rubriques == NULL) {
		        fprintf(stderr, "Impossible d'ouvrir le fichier de rubriques.\n");
		        return EXIT_FAILURE;
		    }
			// Positionnement du curseur au début du fichier et comptage des rubriques existants
		    fseek(fichier_rubriques, 0, SEEK_SET);
		    while (charger_rubrique(fichier_rubriques) != NULL) {
		        dernier_id_rubrique++;
		    }
		   
		    const char* nom_fichier_forums = "Forums";
		    FILE* fichier_forums = fopen(nom_fichier_forums, "a+");
			// Vérification de l'ouverture du fichier de forums
		    if (fichier_forums == NULL) {
		        fprintf(stderr, "Impossible d'ouvrir le fichier des forums.\n");
		        return EXIT_FAILURE;
		    }
			// Positionnement du curseur au début du fichier et comptage des forums existants
		    fseek(fichier_forums, 0, SEEK_SET);
		    while (charger_forum(fichier_forums) != NULL) {
		        dernier_id_forum++;
		    }
		
		    printf("\t\tBienvenue dans le forum !!!\n ");
		    // Boucle principale du programme
		    do {
		        printf("\n---------\n");
		        printf("\n\tMENU\n");
		        printf("1. Forum\n");
		        printf("2. Rubrique\n");
		        printf("3. Profil\n");
		        printf("4. Auteur\n");
		        printf("5. Message\n");
		        printf("6. Stat\n");
		        printf("7. Quitter\n");
		        scanf("%u", &choix);
		
		        switch (choix) {
		            case 1:
		                printf("\nMenu Forums:\n");
		                printf("1. Ajouter un forum\n");
		                printf("2. Afficher les forums\n");
		                printf("3. Extraire un forum par id\n");
		                printf("4. Extraire un forum par courriel du responsable\n");
		                printf("5. Quitter\n");
		                printf("Choix : ");
		                scanf("%d", &choix2);
		
		                switch (choix2) {
		                    case 1:
		                    	//Ajouter un forum
		                        dernier_id_forum++;
		                        sauvegarder_forum(fichier_forums, saisie_forum(dernier_id_forum));
		                        printf("Forum ajout%c avec succ%cs!\n",130,138);
		                        break;
		
		                    case 2:
		                    	//Afficher les forums
		                        afficher_liste_forums(fichier_forums);
		                        break;
		
		                    case 3:
		                    	//Extraire un forum par id
		                        {
		                            unsigned int id;
		                            printf("Entrez l'id du forum à extraire : ");
		                            scanf("%u", &id);
		
		                            frm* extrait = extraire_forum(fichier_forums, id);
		
		                            if (extrait != NULL) {
		                                printf("Forum extrait :\n");
		                                afficher_forum(extrait);
		                                free(extrait);
		                            } else {
		                                printf("Aucun forum trouvé avec l'id %u.\n", id);
		                            }
		                        }
		                        break;
		                    case 4:
		                    	//Extraire un forum par courriel du responsable
		                        {
		                            char couriel[50];
		                            printf("Entrez le courriel du responsable du forum à extraire : ");
		                            scanf("%s", couriel);
		
		                            frm* extrait = extraire_forum_par_responsable(fichier_forums, couriel);
		
		                            if (extrait != NULL) {
		                                printf("Forum extrait :\n");
		                                afficher_forum(extrait);
		                                free(extrait);
		                            } else {
		                                printf("Aucun forum trouvé avec le couriel %s.\n", couriel);
		                            }
		                        }
		                        break;
		
		                    case 5:
		                    	//Quitter
		                        break;
		
		                    default:
		                        printf("Choix invalide. Choisissez un chiffre entre 1 et 5\n");
		                }
		                break;
		
		            case 2:
		                printf("\nMenu Rubriques:\n");
		                printf("1. Ajouter une rubrique\n");
		                printf("2. Afficher les rubriques\n");
		                printf("3. Extraire une rubrique par id\n");
		                printf("4. Afficher tous les message d une rubrique donner\n");
		                printf("5. Afficher tous les message par ordre chronologique de leur date de publication d une rubrique donner\n");
		                printf("6. Retrouver tous les profils de personnes qui postent dans une rubrique donnée\n");
		                printf("7. Quitter\n");
		                printf("Choix : ");
		                scanf("%d", &choix2);
		
		                switch (choix2) {
		                    case 1:
		                    	//Ajouter une rubrique
		                        dernier_id_rubrique++;
		                        sauvegarder_rubrique(fichier_rubriques, saisie_rubrique(dernier_id_rubrique));
		                        printf("Rubrique ajout%ce avec succ%cs!\n",130,138);
		                        break;
		
		                    case 2:
		                    	//Afficher les rubriques
		                        afficher_liste_rubriques(fichier_rubriques);
		                        break;
		
		                    case 3:
		                    	//Extraire une rubrique par id
		                        {
		                            unsigned int id;
		                            printf("Entrez l'id de la rubrique à extraire : ");
		                            scanf("%u", &id);
		
		                            rub* extrait = extraire_rubrique(fichier_rubriques, id);
		
		                            if (extrait != NULL) {
		                                printf("Rubrique extraite :\n");
		                                afficher_rubrique(extrait);
		                                free(extrait);
		                            } else {
		                                printf("Aucune rubrique trouvée avec l'id %u.\n", id);
		                            }
		                        }
		                        break;
		                    case 4:
		                    	//Afficher tous les message d une rubrique donner
		                        {
		                            unsigned int id;
		                            bool T;
		                            char theme[50];
		                            printf("Afficher tous les message de cette rubrique par son id ou par son theme?(1 id 0 theme)\n :");
		                            scanf("%u", &T);
		                            if (T){
		                            	printf("donner l id du rubrique");
		                            	scanf("%u",&id);
		                            	rub* extrait = extraire_rubrique(fichier_rubriques, id);
		
			                            if (extrait != NULL) {
			                                printf("Les messages de la Rubrique extraite :\n");
			                                afficher_messages_rubrique(fichier_messages,extrait);
			                                free(extrait);
			                            }
		                            	
									}else{
										printf("donner le theme de la rubrique");
										scanf("%s",theme);
										rub* extrait = extraire_rubrique_par_theme(fichier_rubriques, theme);
		
			                            if (extrait != NULL) {
			                                printf("Les messages de la Rubrique extraite :\n");
			                                afficher_messages_rubrique(fichier_messages,extrait);
			                                free(extrait);
			                            }
										
									}
		                        }
		                        break;
		                    case 5:
		                    	//Afficher tous les message par ordre chronologique de leur date de publication d une rubrique donner
		                        {
		                            unsigned int id;
		                            bool T;
		                            char theme[50];
		                            printf("Afficher tous les message de cette rubrique par son id ou par son theme?(1 id 0 theme)\n :");
		                            scanf("%u", &T);
		                            if (T){
		                            	printf("donner l id du rubrique");
		                            	scanf("%u",&id);
		                            	rub* extrait = extraire_rubrique(fichier_rubriques, id);
			                            if (extrait != NULL) {
			                            printf("Les messages de la Rubrique extraite :\n");
			                            afficher_messages_rubrique_ordre_chronologique(fichier_messages,extrait);
			                            free(extrait);
			                        	}
									}else{
										printf("donner le theme de la rubrique");
										scanf("%s",theme);
										rub* extrait = extraire_rubrique_par_theme(fichier_rubriques, theme);
										if (extrait != NULL) {
			                            printf("Les messages de la Rubrique extraite :\n");
			                            afficher_messages_rubrique_ordre_chronologique(fichier_messages,extrait);
			                            free(extrait);
			                        	}		
									}
		                        }
		                        break;
		                    case 6:
		                    	//Retrouver tous les profils de personnes qui postent dans une rubrique donnée
		                        {
		                            unsigned int id;
		                            bool T;
		                            char theme[50];
		                            printf("Afficher tous les message de cette rubrique par son id ou par son theme?(1 id 0 theme)\n :");
		                            scanf("%u", &T);
		                            if (T){
		                            	printf("donner l id du rubrique");
		                            	scanf("%u",&id);
		                            	rub* extrait = extraire_rubrique(fichier_rubriques, id);
			                            if (extrait != NULL) {
			                            printf("Les profils dans la Rubrique extraite :\n");
			                            afficher_profils_rubrique(fichier_rubriques,fichier_messages,fichier_auteurs,fichier_profils,extrait);
			                            free(extrait);
			                        	}
									}else{
										printf("donner le theme de la rubrique");
										scanf("%s",theme);
										rub* extrait = extraire_rubrique_par_theme(fichier_rubriques, theme);
										if (extrait != NULL) {
			                            printf("Les profils dans la Rubrique extraite :\n");
			                            afficher_profils_rubrique(fichier_rubriques,fichier_messages,fichier_auteurs,fichier_profils,extrait);
			                            free(extrait);
			                        	}		
									}
		                        }
		                        break;
		
		                    case 7:
		                    	//Quitter
		                        break;
		
		                    default:
		                        printf("Choix invalide. Choisissez un chiffre entre 1 et 7\n");
		                }
		                break;
		
		            case 3:
		                printf("\nMenu Profils:\n");
		                printf("1. Ajouter un profil\n");
		                printf("2. Afficher les profils\n");
		                printf("3. Extraire un profil par numéro d'inscription\n");
		                printf("4. Extraire tous les messages d un profil par son numéro d'inscription\n");
		                printf("5. Quitter\n");
		                printf("Choix : ");
		                scanf("%d", &choix2);
		
		                switch (choix2) {
		                    case 1:
		                    	//Ajouter un profil
		                        dernier_id_profil++;
		                        sauvegarder_profil(fichier_profils, saisie_profil(dernier_id_profil));
		                        printf("Profil ajout%c avec succ%cs!\n",130,138);
		                        break;
		
		                    case 2:
		                    	//Afficher les profils
		                        afficher_liste_profils(fichier_profils);
		                        break;
		
		                    case 3:
		                    	//Extraire un profil par numéro d'inscription
		                        {
		                            unsigned int num_inscrit;
		                            printf("Entrez le numéro d'inscription du profil à extraire : ");
		                            scanf("%u", &num_inscrit);
		
		                            prl* extrait = extraire_profil(fichier_profils, num_inscrit);
		
		                            if (extrait != NULL) {
		                                printf("Profil extrait :\n");
		                                afficher_profil(extrait);
		                                free(extrait);
		                            } else {
		                                printf("Aucun profil trouvé avec le numéro d'inscription %u.\n", num_inscrit);
		                            }
		                        }
		                        break;
		                    case 4:
		                    	//Extraire tous les messages d un profil par son numéro d'inscription
		                        {
		                            unsigned int num_inscrit;
		                            printf("Entrez le numéro d'inscription du profil à extraire : ");
		                            scanf("%u", &num_inscrit);
		
		                            prl* extrait = extraire_profil(fichier_profils, num_inscrit);
		
		                            if (extrait != NULL) {
		                                printf("Messages du profil extrait :\n");
		                                afficher_messages_par_profil(fichier_messages,fichier_auteurs,fichier_profils,num_inscrit);
		                                free(extrait);
		                            } else {
		                                printf("Aucun profil trouvé avec le numéro d'inscription %u.\n", num_inscrit);
		                            }
		                        }
		                        break;
		
		                    case 5:
		                    	//Quitter
		                        break;
		
		                    default:
		                        printf("Choix invalide. Choisissez un chiffre entre 1 et 5\n");
		                }
		                break;
		
		            case 4:
		                printf("\nMenu Auteurs:\n");
				        printf("1. Ajouter un auteur\n");
				        printf("2. Afficher les auteurs\n");
				        printf("3. Extraire un auteur par son id \n");
				        printf("4. Extraire un auteur par son pseudo \n");
				        printf("5. Extraire tous les messages d un auteur\n");
				        printf("6. Quitter\n");
				        printf("Choix : ");
				        scanf("%d", &choix);
				
				        switch (choix) {
				            case 1:
				                // Ajouter un auteur
				                dernier_id_auteur++;
								sauvegarder_auteur(fichier_auteurs, saisie_auteur(dernier_id_auteur,fichier_profils));
								printf("\nauteur ajout%c avec succ%cs!\n",130,130);
				                break;
				
				            case 2:
				                // Afficher les auteurs
				                afficher_liste_auteurs(fichier_auteurs);
				                break;
				                
				            case 3:
							    // Extraire un auteur par son id
							    {
							        unsigned int id;
							        printf("Entrez l id de l'auteur %c extraire : ",133);
							        scanf("%u", &id);
							
							        aut* extrait = extraire_auteur(fichier_auteurs, id);
							
							        if (extrait != NULL) {
							            printf("auteur extrait :\n");
							            afficher_auteur(extrait);
							            free(extrait);  // Libérer la mémoire allouée pour l auteur extrait
							        } else {
							            printf("Aucun auteur trouvé avec l id %u.\n", id);
							        }
							    }
							    break;
							case 4:
							    // Extraire un auteur par son pseudo
							    {
							        char pseudo[50];
							        printf("Entrez le pseudo de l'auteur %c extraire : ",133);
							        scanf("%s", pseudo);
							
							        aut* extrait = extraire_auteur_par_pseudo(fichier_auteurs, pseudo);
							
							        if (extrait != NULL) {
							            printf("auteur extrait :\n");
							            afficher_auteur(extrait);
							            free(extrait);  // Libérer la mémoire allouée pour le auteur extrait
							        } else {
							            printf("Aucun auteur trouvé avec le pseudo %s.\n", pseudo);
							        }
							    }
							    break;
							case 5:
								//Extraire tous les messages d un auteur
								{
								    unsigned int id;
								    bool T;
								    char pseudo[50];
								    printf("Afficher tous les messages de cet auteur par son id ou par son pseudo? (1 id 0 pseudo)\n :");
								    scanf("%u", &T);
								    
								    if (T) {
								        printf("Donner l'id de l'auteur : ");
								        scanf("%u", &id);
								        aut* extrait = extraire_auteur(fichier_auteurs, id);
								
								        if (extrait != NULL) {
								            printf("Les messages de l'auteur extrait :\n");
								            afficher_messages_par_auteur(fichier_messages, fichier_auteurs, extrait);
								            free(extrait);
								        }
								    } else {
								        printf("Donner le pseudo de cet auteur :\n");
								        scanf("%s", pseudo);
								        aut* extrait = extraire_auteur_par_pseudo(fichier_auteurs, pseudo);
								
								        if (extrait != NULL) {
								            printf("Les messages de l'auteur extrait :\n");
								            afficher_messages_par_auteur(fichier_messages, fichier_auteurs, extrait);
								            free(extrait);
								        }
								    }
								}
								break;
		
							    
							case 6:
				                // Quitter
				                break;
				
				            default:
				                printf("Choix invalide. Veuillez entrer de 1 a 6.\n");
				        }
		                break;
		
		            case 5:
		                printf("\nMenu Messages:\n");
		                printf("1. Ajouter un message\n");
				        printf("2. Afficher les messages\n");
				        printf("3. Extraire un message par id\n");
				        printf("4. Extraire un message par titre\n");
				        printf("5. Extraire les message a partir du date\n");
				        printf("6. Afficher tous les reponses a un message donner\n");
				        printf("7. Quitter\n");
				        printf("Choix : ");
				        scanf("%d", &choix);
				
				        switch (choix) {
				            case 1:
							    // Ajouter un message
							    dernier_id_message++;
							    sauvegarder_message(fichier_messages, saisie_message(dernier_id_message));
							    printf("Message ajout%c avec succ%cs!\n",130,138);
							    
							    // Fermer et réouvrir le fichier pour positionner correctement le curseur
							    fclose(fichier_messages);
							    fichier_messages = fopen(nom_fichier_message, "a+");
							    if (fichier_messages == NULL) {
							        fprintf(stderr, "Impossible de réouvrir le fichier de messages.\n");
							        return EXIT_FAILURE;
							    }
							    break;
				
				            case 2:
				                // Afficher les messages
				                afficher_liste_messages(fichier_messages);
				                break;
				
				            case 3:
				                // Extraire un message par id
				                {
				                    unsigned int id;
				                    printf("Entrez l'id du message à extraire : ");
				                    scanf("%u", &id);
				
				                    mesg* extrait = extraire_message(fichier_messages, id);
				
				                    if (extrait != NULL) {
				                        printf("Message extrait :\n");
				                        afficher_message(extrait);
				                        free(extrait);  // Libérer la mémoire allouée pour le message extrait
				                    } else {
				                        printf("Aucun message trouv%c avec l'id %u.\n",130, id);
				                    }
				                }
				                break;
				            case 4:
				                // Extraire un message par titre
				                {
				                    char titre[50];
				                    printf("Entrez le titre du message à extraire : ");
				                    scanf("%s", titre);
				
				                    mesg* extrait = extraire_message_par_titre(fichier_messages,titre);
				
				                    if (extrait != NULL) {
				                        printf("Message extrait :\n");
				                        afficher_message(extrait);
				                        free(extrait);  // Libérer la mémoire allouée pour le message extrait
				                    } else {
				                        printf("Aucun message trouv%c avec le titre %s.\n",130, titre);
				                    }
				                }
				                break;
				            case 5:
				                // Extraire les messages a partir d une date
				                {
				                    struct tm date_recherche;
								    printf("Saisir la date pour laquelle vous souhaitez afficher les messages (jj/mm/aaaa) : ");
								    scanf("%d/%d/%d", &date_recherche.tm_mday, &date_recherche.tm_mon, &date_recherche.tm_year);
								    afficher_messages_par_date(fichier_messages, date_recherche);
				                }
				                break;
				          	case 6:
				          		//Afficher tous les reponses a un message donner
							    {
		                            unsigned int id;
		                            bool T;
		                            char titre[50];
		                            printf("Afficher tous les reponses de message a partir de son id ou son titre?(1 id 0 titre)\n :");
		                            scanf("%u", &T);
		                            if (T){
		                            	printf("donner l id du message");
		                            	scanf("%u",&id);
		                                printf("Les Reponses de ce message :\n");
		                                afficher_messages_reponse(fichier_messages, id);
									}else{
										printf("donner le titre de ce message");
										scanf("%s",titre);
										mesg* extrait = extraire_message_par_titre(fichier_messages,titre);
		
			                            if (extrait != NULL) {
			                                printf("Les reponses a ce message extrait :\n");
			                                afficher_messages_reponse(fichier_messages,extrait->id);
			                                free(extrait);
			                            }
										
									}
		                        }
		                        break;
				
				            case 7:
				                // Quitter
				                break;
				
				            default:
				                printf("Choix invalide. Choisissez un chiffre entre 1 et 7\n");
				        }
		                break;
		    		case 6:
		                // Afficher les statistiques
		                stat(fichier_rubriques, fichier_messages, fichier_auteurs);
		                break;
		
		            case 7:
		                break; // Quitter
		
		            default:
		                printf("Choix invalide. Choisissez un chiffre entre 1 et 7\n");
		        }
		    } while (choix != 7);
		    
			// Fermeture des fichiers avant de quitter
		    fclose(fichier_forums);
		    fclose(fichier_rubriques);
		    fclose(fichier_messages);
		    fclose(fichier_auteurs);
		    fclose(fichier_profils);
		
		    return 0;// Fin du programme
		}

