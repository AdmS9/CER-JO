#include <stdio.h>
#include <stdlib.h> 
#include "entrainement.h"
#include <string.h>

Athlete athletes[MAX_ATHLETES];
int num_athletes = 0;

void sauvegarder_entrainements(char nom_athlete[]){
    FILE *fichier;
    char nom_fichier[MAX_LONGUEUR_NOM + 4];
    sprintf(nom_fichier, "%s.txt", nom_athlete);

    fichier=fopen(nom_fichier,"w");
    if (fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }
    int i;
    for(i=0; i < num_athletes; i++){
        if(strcmp(athletes[i].nom, nom_athlete)==0){
            int j;
            for(j=0; j < athletes[i].num_entrainements; j++){
            fprintf(fichier,"%s,%s,%.2f,%d\n",
                       athletes[i].entrainements[j].date, 
                       athletes[i].entrainements[j].type, 
                       athletes[i].entrainements[j].temps,
                       athletes[i].entrainements[j].position);
        }
            break;
    }
    }
    fclose(fichier);
}

void charger_entrainements(char nom_athlete[]) {
    FILE *fichier;
    char nom_fichier[MAX_LONGUEUR_NOM + 4];
    sprintf(nom_fichier, "%s.txt", nom_athlete);

    fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Aucun fichier trouvé pour %s\n", nom_athlete);
        return;
    }

    Athlete nouvel_athlete;
    strcpy(nouvel_athlete.nom, nom_athlete);
    nouvel_athlete.num_entrainements = 0;

    while (fscanf(fichier, "%s %s %f %d", 
                  nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].date, 
                  nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].type, 
                  &nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].temps, 
                  &nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].position) == 4) {
        nouvel_athlete.num_entrainements++;
    }

    athletes[num_athletes++] = nouvel_athlete;
    fclose(fichier);
}

void ajouter_entrainement(char nom_athlete[], char date[], char type[], float temps, int position) {
    int i;
    for (i = 0; i < num_athletes; i++) {
        if (strcmp(athletes[i].nom, nom_athlete) == 0) {
            if (strcmp(type, "relais") == 0 && athletes[i].num_entrainements > 0) {
                printf("Un seul entraînement en relais par jour est autorisé.\n");
                return;
            }
            Entrainement nouvel_entrainement;
            strcpy(nouvel_entrainement.date, date);
            strcpy(nouvel_entrainement.type, type);
            nouvel_entrainement.temps = temps;
            nouvel_entrainement.position = position;
            athletes[i].entrainements[athletes[i].num_entrainements++] = nouvel_entrainement;
            sauvegarder_entrainements(nom_athlete);
            printf("Entraînement ajouté avec succès pour %s.\n", nom_athlete);
            return;
        }
    }
    if (num_athletes >= MAX_ATHLETES) {
        printf("Limite d'athlètes atteinte.\n");
        return;
    }
    strcpy(athletes[num_athletes].nom, nom_athlete);
    Entrainement nouvel_entrainement;
    strcpy(nouvel_entrainement.date, date);
    strcpy(nouvel_entrainement.type, type);
    nouvel_entrainement.temps = temps;
    nouvel_entrainement.position = position;
    athletes[num_athletes].entrainements[athletes[num_athletes].num_entrainements++] = nouvel_entrainement;
    sauvegarder_entrainements(nom_athlete);
    num_athletes++;
    printf("Nouvel athlète ajouté : %s.\n", nom_athlete);
}

void historique_athlete(char nom_athlete[]) {
    int i;
    for (i = 0; i < num_athletes; i++) {
        if (strcmp(athletes[i].nom, nom_athlete) == 0) {
            printf("Historique des entraînements pour %s :\n", nom_athlete);
            int j;
            for (j = 0; j < athletes[i].num_entrainements; j++) {
                printf("Date: %s, Type: %s, Temps: %.2f", 
                       athletes[i].entrainements[j].date, 
                       athletes[i].entrainements[j].type, 
                       athletes[i].entrainements[j].temps);
                if (strcmp(athletes[i].entrainements[j].type, "relais") == 0) {
                    printf(", Position: %d\n", athletes[i].entrainements[j].position);
                } else {
                    printf("\n");
                }
            }
            return;
        }
    }
   printf("Athlète introuvable : %s.\n", nom_athlete);
}

void statistiques_athlete(char nom_athlete[], char type_evenement[]) {
              int i, count = 0;
              float temps_total = 0, meilleur_temps = 2, 
              pire_temps = -1;
              for (i = 0; i < num_athletes; i++) {
                  if (strcmp(athletes[i].nom, nom_athlete) == 0) {
                      int j;
                      for (j = 0; j < athletes[i].num_entrainements; j++) {
                          if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {
                              count++;
                              temps_total += athletes[i].entrainements[j].temps;
                              if (athletes[i].entrainements[j].temps < meilleur_temps) {
                                  meilleur_temps = athletes[i].entrainements[j].temps;
                              }
                              if (athletes[i].entrainements[j].temps > pire_temps) {
                                  pire_temps = athletes[i].entrainements[j].temps;
          }
        }
      }
    }
  }
    if (count > 0) {
      printf("Statistiques pour %s - %s:\n", nom_athlete, type_evenement);
      printf("Nombre d'entraînements: %d\n", count);
      printf("Temps moyen: %.2f\n", temps_total / count);
      printf("Meilleur temps: %.2f\n", meilleur_temps);
      printf("Pire temps: %.2f\n", pire_temps);
    } else {
      printf("Aucun entraînement trouvé pour %s - %s.\n", nom_athlete, type_evenement);
  }
}
          void statistiques_globales(char type_evenement[]) {
            int count = 0;
            float temps_total = 0, meilleur_temps = 2, pire_temps = -1;
            int i, j;
            for (i = 0; i < num_athletes; i++) {
                for (j = 0; j < athletes[i].num_entrainements; j++) {
                    if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {
                        count++;
                        temps_total += athletes[i].entrainements[j].temps;
                        if (athletes[i].entrainements[j].temps < meilleur_temps) {
                            meilleur_temps = athletes[i].entrainements[j].temps;
                        }
                        if (athletes[i].entrainements[j].temps > pire_temps) {
                            pire_temps = athletes[i].entrainements[j].temps;
        }
      }
    }
  }
    if (count > 0) {
      printf("Statistiques pour l'événement %s:\n", type_evenement);
      printf("Nombre total d'entraînements: %d\n", count);
      printf("Temps moyen: %.2f\n", temps_total / count);
      printf("Meilleur temps: %.2f\n", meilleur_temps);
      printf("Pire temps: %.2f\n", pire_temps);
    } else {
      printf("Aucun entraînement trouvé pour l'événement %s.\n", type_evenement);
  }
}

 void classement_athletes(char type_evenement[]) {
 float temps[MAX_ATHLETES];
 int i, j;
 for (i = 0; i < num_athletes; i++) {
   temps[i] = 0;
   int count = 0;
    for (j = 0; j < athletes[i].num_entrainements; j++) {
    if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {
      temps[i] += athletes[i].entrainements[j].temps;
      count++;
  }
}
    if (count > 0) {
                temps[i] /= count;
            } else {
                temps[i] = -1;
    }
    }

        for (i = 0; i < num_athletes - 1; i++) {
          for (j = 0; j < num_athletes - i - 1; j++) {
              if (temps[j] > temps[j + 1]) {
                  float temp = temps[j];
                  temps[j] = temps[j + 1];
                  temps[j + 1] = temp;
                  Athlete temp_athlete = athletes[j];
                  athletes[j] = athletes[j + 1];
                  athletes[j + 1] = temp_athlete;

      }
    }
  }
      printf("Meilleurs athlètes pour l'événement %s:\n", type_evenement);
       for (i = 0; i < num_athletes && i < 3 && temps[i] != -1; i++) {
        printf("%d. %s - Temps moyen: %.2f\n", i + 1, athletes[i].nom, temps[i]);
 }
}

       void progression_athlete(char nom_athlete[], char type_evenement[], char date1[], char date2[]) {
       float temps1 = -1, temps2 = -1;
       int i, j;
        for (i = 0; i < num_athletes; i++) {
          if (strcmp(athletes[i].nom, nom_athlete) == 0) {
           for (j = 0; j < athletes[i].num_entrainements; j++) {
            if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {
              if (strcmp(athletes[i].entrainements[j].date, date1) == 0) {
               temps1 = athletes[i].entrainements[j].temps;
              } else if (strcmp(athletes[i].entrainements[j].date, date2) == 0) {
                temps2 = athletes[i].entrainements[j].temps;
                 }
              }
            }
          }
        }
      if (temps1 != -1 && (strcmp(type_evenement, "relais") != 0 || temps2 != -1)) {
    printf("Progression de %s pour l'événement %s entre %s et %s:\n", nom_athlete, type_evenement, date1, date2);
    printf("Ancien temps: %.2f\n", temps1);
    printf("Nouveau temps: %.2f\n", temps2);
    printf("Différence de temps: %.2f\n", temps1 - temps2);
  } 
  else {
    printf("Impossible de trouver les temps pour %s pour l'événement %s entre %s et %s.\n", nom_athlete, type_evenement, date1, date2);
    }
}
