#include "calendar.h"

creneau initCours(){
    creneau c;
    c.nom_matiere = NULL;
    c.type_cours = NULL;
    c.jour_semaine = NULL;
    c.heure_debut = NULL;
    c.heure_fin = NULL;
    c.frequence = 1;
    c.mode_cours = NULL;
    c.salles = NULL;
    return c;
}

int menu(char* titre_menu, char** tableau_proposition){
    if(tableau_proposition[0] != NULL){
        int i;
        char buffer[100];
        int reponse = -1;
        do{
            i=0;
            printf("\n%s\n", titre_menu);
            while(tableau_proposition[i] != NULL){
                printf("\n%d : %s", i,  tableau_proposition[i]);
                i++;
            }
            printf("\n\n Votre reponse :\t");
            scanf("%s", buffer);
        } while((sscanf(buffer,"%d",&reponse)==EOF)||(reponse > i-1)||(reponse <0));
        return reponse;
    }
    return -1;
}

char* afficher_repertoire(char* repertoire){
    int index_fichier = -1;
    struct dirent *dir;
    int iteration = 0;
    char** tableau_fichiers = NULL;
    char* buffer_fichier;
    // opendir() renvoie un pointeur de type DIR. 
    DIR *d = opendir(repertoire);
    perror("Erreur");
    if (d != NULL){
        while ((dir = readdir(d)) != NULL){
            buffer_fichier =(char*) malloc(sizeof(char)*strlen(dir->d_name));
            buffer_fichier = strcpy(buffer_fichier, dir->d_name);
            if(tableau_fichiers == NULL){
                tableau_fichiers = (char**) malloc(sizeof(char*));
            } else{
                tableau_fichiers = realloc(tableau_fichiers, sizeof(char*)*(iteration+1));
            }
            tableau_fichiers[iteration] = (char*) malloc(sizeof(char)*strlen(buffer_fichier));
            tableau_fichiers[iteration] = strcpy(tableau_fichiers[iteration],buffer_fichier);
            iteration++;
            free(buffer_fichier);
        }
        closedir(d);

        index_fichier = menu("Quel fichier voulez-vous choisir ?", tableau_fichiers);
        return tableau_fichiers[index_fichier];    
    }
    perror("Erreur");
    return NULL;
}

time_t getTime(){
    time_t t;
    return time(&t);
}