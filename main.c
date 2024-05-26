        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include "entrainement.h"
        #include "scanf.h"

        int main() {
            char choix;

            do {
                printf("Menu :\n");
                printf("1. Créer entraînement\n");
                printf("2. Historique\n");
                printf("3. Statistiques athlète\n");
                printf("4. Statistiques globales\n");
                printf("5. Classement\n");
                printf("6. Progression\n");
                printf("7. Quitter\n");
                printf("\nVotre choix : ");
                scanf(" %c", &choix);
                while (getchar() != '\n') {} 

                switch (choix) {
                    case '1': {
                        char nom_athlete[MAX_LONGUEUR_NOM];
                        char date[MAX_LONGUEUR_DATE];
                        char type[MAX_LONGUEUR_NOM];
                        float temps;
                        int position;
                        int entrainement_valide=0;
                        int nom_valide=0;
                        int temps_valide=0;
                        int position_valide=0;
                        while(!nom_valide){
                            better_scan("Nom : ", nom_athlete, 's');
                            if(strcmp(nom_athlete,"")!=0){
                                nom_valide=1;
                            }
                            else{
                                printf("nom invalide il ne peut pas être vide\n");
                            }
                        }
                        better_scan("Date (YYYY-MM-DD) :", date, 's');
                        while(!entrainement_valide){
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        while(!temps_valide){
                            better_scan("Temps : ", &temps, 'f');
                            if(temps>0){
                                temps_valide=1;
                            }
                            else{
                                printf("temps invalide \n");
                            }
                            
                            }
                        while(!position_valide){
                            better_scan("Position : ", &position, 'd');
                            if(position>0){
                                position_valide=1;
                            }
                            else{
                                printf("position invalide \n");
                            }

                            }
                        
                        ajouter_entrainement(nom_athlete, date, type, temps, position);
                        sauvegarder_entrainements(nom_athlete);
                        break;
                    }

                    case '2': {
                        char nom_athlete[MAX_LONGUEUR_NOM];
                        better_scan("Nom de l'athlète : ", nom_athlete, 's');
                        historique_athlete(nom_athlete);
                        break;
                    }

                    case '3': {
                        char nom_athlete[MAX_LONGUEUR_NOM];
                        char type[MAX_LONGUEUR_NOM];
                        int entrainement_valide=0;
                        better_scan("Nom de l'athlète : ", nom_athlete, 's');
                        while(!entrainement_valide){
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        statistiques_athlete(nom_athlete, type);
                        break;
                    }

                    case '4': {
                        char type[MAX_LONGUEUR_NOM];
                        int entrainement_valide=0;
                        while(!entrainement_valide){
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        statistiques_globales(type);
                        break;
                    }

                    case '5': {
                        char type[MAX_LONGUEUR_NOM];
                        int entrainement_valide=0;
                        while(!entrainement_valide){
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        classement_athletes(type);
                        break;
                    }

                    case '6': {
                        char nom_athlete[MAX_LONGUEUR_NOM];
                        char type[MAX_LONGUEUR_NOM];
                        char date1[MAX_LONGUEUR_DATE];
                        char date2[MAX_LONGUEUR_DATE];
                        int entrainement_valide=0;
                        better_scan("Nom de l'athlète : ", nom_athlete, 's');
                        while(!entrainement_valide){
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        better_scan("Date de début (YYYY-MM-DD) : ", date1, 's');
                        better_scan("Date de fin (YYYY-MM-DD) : ", date2, 's');
                        progression_athlete(nom_athlete, type, date1, date2);
                        break;
                    }

                    case '7':
                        printf("\nAu revoir !\n");
                        break;

                    default:
                        printf("Choix invalide, veuillez réessayer.\n");
                        break;
                }
            } while (choix != '7');
        
            return 0;
        }
