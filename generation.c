#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generer_texte(char *nom_fichier, int nb) {
  FILE *fichier =NULL;
  int i;

  fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier1");
        return;
    }
    for (i = 0; i < nb; i++) {
        fprintf(fichier, "Il nageait, nageait, nageait toujours vers le large jusqu'à disparaître de mon champ de vision.\n");
    }
    fclose(fichier);
}


void generer_ascii(char *nom_fichier, int nb) {
  FILE *fichier =NULL;
  int i;
  char c;
  
  fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier2");
        return;
    }

 
    for ( i = 0; i < nb; i++) {
         c = 32 + (rand() % (126 - 32 + 1)); 
        fprintf(fichier, "%c", c);
    }
    fclose(fichier);
}


void generer_nums(char *nom_fichier, int nb ) {
  FILE *fichier =NULL;
  int i;

  fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier3");
        return;
    }
    for ( i = 0; i < nb; i++) {
        fprintf(fichier, "%d ", rand() % 100); 
    }
    fclose(fichier);
}

int main(){
  int i;
  char nom_fichier[100];
   srand(time(NULL));
   for(i = 1; i <= 20; i++){
     sprintf(nom_fichier, "huff_v5/%s%d.txt", "texte_repete",i);
     generer_texte(nom_fichier, 100*i);
     sprintf(nom_fichier, "huff_v5/%s%d.txt", "ascii_aleatoire",i);
     generer_ascii(nom_fichier, 1000*i);
     sprintf(nom_fichier, "huff_v5/%s%d.txt", "nombres_aleatoires",i);
     generer_nums(nom_fichier, 100*i);
   }
  exit(0);
}
