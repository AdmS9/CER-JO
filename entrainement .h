#ifndef ENTRAINEMENT_H
#define ENTRAINEMENT_H
#define MAX_ATHLETES 4
#define MAX_ENTRAINEMENT 7
#define MAX_LONGUEUR_NOM 20
#define MAX_LONGUEUR_DATE 20

typedef struct {
  char date[MAX_LONGUEUR_DATE];
  char type[MAX_LONGUEUR_NOM];
  float temps;
  int position; 
} Entrainement;

typedef struct {
  char nom[MAX_LONGUEUR_NOM];
  Entrainement entrainements[MAX_ENTRAINEMENT];
  int num_entrainements;
} Athlete;

void ajouter_entrainement(char nom_athlete[], char date[], char type[], float temps, int position);
void sauvegarder_entrainements(char nom_athlete[]);
void historique_athlete(char nom_athlete[]);
void statistiques_athlete(char nom_athlete[], char type_evenement[]);
void statisques_globales(char type_evenement[]);
void classement_athletes(char type_evenement[]);
void progression_athlete(char nom_athlete[], char type_evenement[], char date1[], char date2[]);
void charger_entrainements(char nom_athlete[]);

#endif /*ENTRAINEMENT_H*/

