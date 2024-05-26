#include "type.h"
#include "arbre.h"
#include "tableau.h"
#include "decoder.h"
#include "encoder.h"
#include "outils.h"
#include <string.h>
#define PATH_MAX 4096


/****************************************
 * fonction : main
 * description : Exécute le processus de compression de Huffman, puis décompresse pour vérification
 * entree : entiers argc (nombre d'arguments), tableau de chaînes argv (arguments)
 * sortie : (int) état de sortie du programme
 ****************************************/
int main(int argc, char *argv[]){
  FILE * fichier = NULL;
  FILE *fichier_compresse=NULL;
  noeud *arbre_huffman[N];
  noeud *alphabet[N];
  int tab[N];
  int i, nb_noeuds=0, nombre_feuilles=0;
  int opt, compresse = 0, decompresse = 0, optind=2;
  char *chemin_fichier_compresse = NULL;
  char *dossier_cible = "."; 
  char chemin[PATH_MAX];

  while ( (opt=getopt(argc, argv, "c:d:h")) != -1){
        switch (opt){
        case 'c':
          compresse = 1;
          break;
        case 'd':
          decompresse = 1;
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
    if(argc < 3 && argc > 3){
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
if(compresse == 1){
  /*Ouverture du fichier à compresser*/
    fichier = fopen(argv[2], "r");
    if(fichier == NULL){
      printf("Erreur lors de l'ouverture du fichier \n");
      exit(EXIT_FAILURE);
    }
  /*Initialisation du tableau d'occurrences et construction de l'arbre*/
    init_tab(tab);
    occurence(fichier, tab);
    arbre(arbre_huffman, tab);
    

  /*Création des feuilles de l'arbre Huffman*/
    for (i = 0; i < 256; i++) {
        if (tab[i] > 0) {
        arbre_huffman[nb_noeuds] = creer_feuille(tab, i);
        nb_noeuds++; 
      }
    }

    affichage_car(arbre_huffman);

  /* Construction de l'arbre de Huffman complet*/
    while (nb_noeuds > 1) {  
      creer_noeud(arbre_huffman, nb_noeuds);
      nb_noeuds--; 
    }
    /*Affichage de l'arbre de Huffman*/
    printf("-------------------------------------\n");
    afficher_arbre(arbre_huffman[0]);
    printf("-------------------------------------\n");

  /*création des codes de Huffman pour chaque caractère*/
    creer_code(arbre_huffman[0], 0, 0, alphabet);
    printf("-------------------------------------\n");
  	
  /*Comptage des feuilles utilisées dans l'arbre Huffman*/
    for (i = 0; i < 256; i++) {
      if (alphabet[i] != NULL) {
        nombre_feuilles++;
      }
    }

  /* Écriture de l'en-tête et du contenu compressé*/
    fichier_compresse = fopen(argv[3], "wb");
    if (fichier_compresse == NULL) {
      printf("Erreur lors de l'ouverture du fichier compressé");
      exit(EXIT_FAILURE);
    }

    ecrire_entete(fichier_compresse, alphabet, nombre_feuilles);
    contenu_compresse(fichier,fichier_compresse,alphabet);
   
    fclose(fichier_compresse);
    fclose(fichier);
  }
  
  if(decompresse == 1){
    if(optind<argc){
      chemin_fichier_compresse = argv[optind];
    if (argc > optind + 1) {
            dossier_cible = argv[optind + 1];
        }
    } 
    if (strcmp(dossier_cible, ".") != 0) {
        sprintf(chemin, "%s/fichier_decompresse.txt", dossier_cible);
    } else {
       sprintf(chemin, "fich_decomp.txt");
       
    }
    /*Réouverture du fichier compressé pour vérification*/
    fichier_compresse = fopen(chemin_fichier_compresse, "rb");
    if (fichier_compresse == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier compressé '%s'.\n", chemin_fichier_compresse);
        exit(EXIT_FAILURE);
    }
    
  
  lire_entete(fichier_compresse, alphabet);
  lire_contenu(fichier_compresse, alphabet, chemin);
  fclose(fichier_compresse);

  }
  
  /*Libération des ressources*/
  liberer_inis(arbre_huffman);
	exit(EXIT_SUCCESS);


}









