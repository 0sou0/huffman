#include "type.h"
#include "arbre.h"
#include "tableau.h"
#include "decoder.h"
#include "encoder.h"
#include "outils.h"
#define PATH_MAX 4096




/****************************************
 * fonction : main
 * description : Exécute le processus de compression de Huffman, puis décompresse pour vérification
 * entree : entiers argc (nombre d'arguments), tableau de chaînes argv (arguments)
 * sortie : (int) état de sortie du programme
 ****************************************/
int main(int argc, char *argv[]){
  struct dirent* fichierLu = NULL;
  FILE * fichier = NULL;
  FILE *fichier_compresse=NULL;
  DIR *dossier = NULL;
  noeud *arbre_huffman[N];
  noeud *alphabet[N];

  
  int i, nb_noeuds=0, nombre_feuilles=0;
  int opt, compresse = 0, decompresse = 0, optind=2;
  char *chemin_fichier_compresse = NULL;
  char *chemin_dossier = NULL;
  char nom_fichier[PATH_MAX];

  int tab_global[N];
  
  while ( (opt=getopt(argc, argv, "c:d:h")) != -1){
        switch (opt){
        case 'c':
          compresse = 1;
          chemin_dossier = argv[optind];
          break;
        case 'd':
          decompresse = 1;
          chemin_fichier_compresse = argv[optind];
          break;
      	case 'h':
          afficher_aide();
          exit(EXIT_FAILURE);
          break;
        default:
          usage(argv[0]);
          exit(EXIT_FAILURE);
        }
  }



  
    /*Initialisation de l'arbre Huffman et de l'alphabet*/
    for(i = 0; i < 256; i++){
      arbre_huffman[i] = (noeud*)malloc(sizeof(noeud));
      if(arbre_huffman[i] == NULL){
        printf("Erreur de l'allocation memoire\n");
        exit(EXIT_FAILURE);
      }
    }
        
    for(i = 0; i < 256; i++){
      alphabet[i] = NULL; 
    }



  /*Validation du nombre d'arguments*/
    if(argc < 3){
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }

if(compresse == 1){
  init_tab(tab_global);
  dossier = opendir(chemin_dossier);
  if(dossier == NULL){
    perror("Erreur ouverture dossier \n");
    exit(EXIT_FAILURE);
  }
      while((fichierLu = readdir(dossier))!= NULL){
        if(strcmp(fichierLu->d_name, ".") == 0 || strcmp(fichierLu->d_name, "..") == 0){
          continue;
        }
        sprintf(nom_fichier, "%s/%s",chemin_dossier, fichierLu->d_name);
            fichier = fopen(nom_fichier, "rb");
            if (fichier == NULL) {
                fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", fichierLu->d_name);
                continue;
            }
 
    
    occurence(fichier, tab_global);
    fclose(fichier);
  }


    arbre(arbre_huffman, tab_global);
    

  /*Création des feuilles de l'arbre Huffman*/
    for (i = 0; i < 256; i++) {
        if (tab_global[i] > 0) {
        arbre_huffman[nb_noeuds] = creer_feuille(tab_global, i);
        nb_noeuds++; 
      }
    }

    affichage_car(arbre_huffman);

  /* Construction de l'arbre de Huffman complet*/
    while (nb_noeuds > 1) {  
      creer_noeud(arbre_huffman, nb_noeuds);
      nb_noeuds--; 
    }
   

  /*création des codes de Huffman pour chaque caractère*/
    creer_code(arbre_huffman[0], 0, 0, alphabet);
    printf("-------------------------------------\n");
  	
  /*Comptage des feuilles utilisées dans l'arbre Huffman*/
    for (i = 0; i < 256; i++) {
      if (alphabet[i] != NULL) {
        nombre_feuilles++;
      }
    }

  




    fichier_compresse = fopen(argv[argc - 1], "wb");
      if (fichier_compresse == NULL) {
          perror("Erreur lors de l'ouverture du fichier compressé pour écriture");
          exit(EXIT_FAILURE);
      }

      ecrire_entete(fichier_compresse, alphabet, nombre_feuilles);
      rewinddir(dossier);
      while((fichierLu = readdir(dossier))!= NULL){
        if(strcmp(fichierLu->d_name, ".") == 0 || strcmp(fichierLu->d_name, "..") == 0){
          continue;
        }
        sprintf(nom_fichier, "%s/%s",chemin_dossier, fichierLu->d_name);
            fichier = fopen(nom_fichier, "rb");
            if (fichier == NULL) {
                fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", fichierLu->d_name);
                continue;
            }
      fichier = fopen(nom_fichier, "rb");
      fprintf(fichier_compresse, "%s ",nom_fichier );
      contenu_compresse(fichier, fichier_compresse, alphabet);
      fclose(fichier);
    }
    

    fclose(fichier_compresse);
    closedir(dossier);
  }
  
  if(decompresse == 1){ 

    fichier_compresse = fopen(chemin_fichier_compresse, "rb");
    if (fichier_compresse == NULL) {
        perror("Erreur lors de l'ouverture du fichier compressé pour lecture");
        exit(EXIT_FAILURE);
    }
  
  
  lire_entete(fichier_compresse, alphabet);
  lire_contenu(fichier_compresse, alphabet);
}

/*Libération des ressources et fermeture des fichiers*/
  liberer_inis(arbre_huffman);

  exit(EXIT_SUCCESS);


}









