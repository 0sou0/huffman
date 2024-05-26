#include "type.h"
#include "arbre.h"
#include "tableau.h"
#include "decoder.h"
#include "encoder.h"
#include "outils.h"
#include <sys/stat.h>




/****************************************
 * fonction : main
 * description : Point d'entrée principal du programme. Gère les arguments de la ligne de commande
 *               pour effectuer la compression ou la décompression selon l'option choisie.
 *               Initialise les structures de données nécessaires, appelle les fonctions de 
 *               compression ou de décompression, et gère les ressources et la fermeture des fichiers.
 * entree : entiers argc (nombre d'arguments), tableau de chaînes argv (arguments)
 * sortie : (int) état de sortie du programme
 ****************************************/
int main(int argc, char *argv[]){
  FILE *fichier_compresse=NULL;
  noeud *arbre_huffman[N];
  noeud *alphabet[N];
  char *chemin_fichier_compresse = NULL;
  int i, nb_noeuds=0, nombre_feuilles=0;
  int compresse = 0, decompresse = 0;
  int opt, optind=2;
  int tab_global[N];
  struct stat info;
  
 
  
/*Validation du nombre d'arguments*/
  if(argc < 2){
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
/*Traitement des arguments de la ligne de commande*/
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
initialiser_arbre_huffman(arbre_huffman);
initialiser_alphabet(alphabet);

/*Processus de compression*/
if(compresse == 1){
  init_tab(tab_global);

  if (optind < argc) {
    chemin_fichier_compresse = argv[argc - 1];
  }
 
  for (i = optind; i < argc - 1; i++) {
        compression_rec(argv[i],chemin_fichier_compresse, fichier_compresse, alphabet, tab_global);
    }
 
arbre(arbre_huffman, tab_global);
creer_feuilles_huffman(arbre_huffman, tab_global, &nb_noeuds);
/*affichage_car(arbre_huffman);*/
construire_arbre_huffman(arbre_huffman, &nb_noeuds);
creer_code(arbre_huffman[0], 0, 0, alphabet);
nombre_feuilles = compter_nombre_feuilles(alphabet);


fichier_compresse = fopen(chemin_fichier_compresse, "wb");
  if (fichier_compresse == NULL) {
      printf("Erreur lors de l'ouverture du fichier compressé");
        exit(EXIT_FAILURE);
  }

  ecrire_entete(fichier_compresse, alphabet, nombre_feuilles);
  for ( i = optind; i < argc - 1; i++) {
    contenu_rec(argv[i],chemin_fichier_compresse, fichier_compresse, alphabet);
    if (stat(argv[i], &info) != 0) {
        perror("Erreur on arrive pas à savoir si le chemin amene vers un fichier ou un dossier");
        exit(EXIT_FAILURE);
    }
    if(!S_ISDIR(info.st_mode)){
      printf("fichier : %s \n", argv[i]);
      printf("taille fichier : %d\n",taille_fichier((argv[i])));
    }
    }
    fclose(fichier_compresse);
 }


/*Processus de décompression*/ 
if(decompresse == 1){ 
  if (optind < argc) {
    chemin_fichier_compresse = argv[argc - 1];
  } 
  fichier_compresse = fopen(chemin_fichier_compresse, "rb");
    if (fichier_compresse == NULL) {
      printf("Erreur ouverture du fichier compressé");
      exit(EXIT_FAILURE);
    }
  
  
  lire_entete(fichier_compresse, alphabet);
  lire_contenu(fichier_compresse, alphabet);
}
  
/*Libération des ressources et fermeture des fichiers*/
  liberer_inis(arbre_huffman);
  exit(EXIT_SUCCESS);
}