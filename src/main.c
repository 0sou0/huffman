#include "type.h"
#include "arbre.h"
#include "tableau.h"
#include "decoder.h"
#include "encoder.h"
#include "outils.h"




/****************************************
 * fonction : main
 * description : Exécute le processus de compression de Huffman, puis décompresse pour vérification
 * entree : entiers argc (nombre d'arguments), tableau de chaînes argv (arguments)
 * sortie : (int) état de sortie du programme
 ****************************************/
int main(int argc, char *argv[]){
  FILE *fichier_compresse=NULL; 
  noeud *arbre_huffman[N];
  noeud *alphabet[N]; 
  int  nb_noeuds=0, nombre_feuilles=0;
  int opt, compresse = 0, decompresse = 0, optind=2;
  char *chemin_fichier_compresse = NULL;
  char *chemin_dossier = NULL;
  

  int tab_global[N];


/*Validation du nombre d'arguments*/
    if(argc < 3){
      usage(argv[0]);
      exit(EXIT_FAILURE);
    }
  
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
   
if(compresse == 1){
  init_tab(tab_global);

   chemin_dossier = argv[optind];
   chemin_fichier_compresse = argv[optind + 1];
      
  
init_tab(tab_global);
compression_rec(chemin_dossier, chemin_fichier_compresse, fichier_compresse, alphabet, tab_global);
arbre(arbre_huffman, tab_global);
creer_feuilles_huffman(arbre_huffman, tab_global, &nb_noeuds);
affichage_car(arbre_huffman);
construire_arbre_huffman(arbre_huffman, &nb_noeuds);
creer_code(arbre_huffman[0], 0, 0, alphabet);
nombre_feuilles = compter_nombre_feuilles(alphabet);  

 

fichier_compresse = fopen(chemin_fichier_compresse, "wb");
        if (fichier_compresse == NULL) {
            printf("Erreur lors de l'ouverture du fichier compressé");
            exit(EXIT_FAILURE);
        }
      ecrire_entete(fichier_compresse, alphabet, nombre_feuilles);
      contenu_rec(chemin_dossier, chemin_fichier_compresse, fichier_compresse, alphabet);
    }
    
  
  
  if(decompresse == 1){ 
  if (optind < argc) {
            chemin_fichier_compresse = argv[optind++];
        } 
    fichier_compresse = fopen(chemin_fichier_compresse, "rb");
    if (fichier_compresse == NULL) {
        printf("Erreur lors de l'ouverture du fichier compressé pour lecture");
        exit(EXIT_FAILURE);
    }
  
  
  lire_entete(fichier_compresse, alphabet);
  lire_contenu(fichier_compresse, alphabet);
}
 
/*Libération des ressources et fermeture des fichiers*/
  liberer_inis(arbre_huffman);

  exit(EXIT_SUCCESS);


}









