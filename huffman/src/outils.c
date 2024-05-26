#include "type.h"
#include "arbre.h"
#include "tableau.h"
#include "encoder.h"
#include <dirent.h>
#include <sys/stat.h>
 
 /****************************************
 * fonction : usage
 * description : Affiche l'usage du programme pour informer l'utilisateur de la manière correcte de lancer le programme
 * entree : chaîne de caractères s (nom du programme)
 * sortie : aucune (void), affiche un message sur la sortie standard
 ****************************************/
void usage(char *s){
    printf("Usage : %s <option> (-h pour plus d'informations) \n", s);
}


int taille_fichier(char *nom_fichier)
{
   FILE *fp;
   int taille;
   taille = 0;
   if ((fp = fopen(nom_fichier, "rb" )) == NULL) {
      fprintf(stderr, "ouverture impossible sorry %s.\n", nom_fichier);
      return(taille);
   }


   if (fseek(fp, (long)(0), SEEK_END) != 0) {
      fclose(fp);
      return(taille);
   }
   taille = (int) (ftell(fp));
   fclose(fp);
   return(taille);
}

/****************************************
 * fonction : compter_nombre_feuilles
 * description : Compte le nombre de noeuds feuilles (caractères uniques) dans l'arbre de Huffman,
 *               qui ont été utilisés lors de la construction de l'arbre.
 * entree : tableau de pointeurs vers noeud (alphabet)
 * sortie : entier représentant le nombre de feuilles dans l'arbre de Huffman
 ****************************************/
int compter_nombre_feuilles(noeud *alphabet[]) {
    int nombre_feuilles = 0;
    int i;

    for (i = 0; i < 256; i++) {
        if (alphabet[i] != NULL) {
            nombre_feuilles++;
        }
    }

    return nombre_feuilles;
}

/****************************************
 * fonction : initialiser_arbre_huffman
 * description : Alloue la mémoire pour chaque élément de l'arbre Huffman et initialise
 *               chaque pointeur à NULL pour éviter des pointeurs non initialisés.
 * entree : tableau de pointeurs vers noeud (arbre_huffman)
 * sortie : aucune (void), termine le programme en cas d'erreur d'allocation mémoire
 ****************************************/
void initialiser_arbre_huffman(noeud *arbre_huffman[]) {
    int i;
    for (i = 0; i < 256; i++) {
        arbre_huffman[i] = (noeud*)malloc(sizeof(noeud));
        if (arbre_huffman[i] == NULL) {
            fprintf(stderr, "Erreur de l'allocation memoire\n");
            exit(EXIT_FAILURE);
        }
    }
}

/****************************************
 * fonction : initialiser_alphabet
 * description : Initialise chaque pointeur de l'alphabet à NULL pour préparer la construction
 *               de l'arbre de Huffman.
 * entree : tableau de pointeurs vers noeud (alphabet)
 * sortie : aucune (void), initialise l'alphabet pour le codage de Huffman
 ****************************************/
void initialiser_alphabet(noeud *alphabet[]) {
    int i;
    for (i = 0; i < 256; i++) {
        alphabet[i] = NULL;
    }
}
/****************************************
 * fonction : creer_feuilles_huffman
 * description : Parcourt le tableau d'occurrences et pour chaque caractère avec une occurrence
 *               non nulle, crée un noeud feuille et l'ajoute à l'arbre Huffman.
 * entree : tableau de pointeurs vers noeud (arbre_huffman), tableau des occurrences (tab_global),
 *          pointeur vers entier (nb_noeuds) pour suivre le nombre actuel de noeuds dans l'arbre
 * sortie : aucune (void), ajoute des feuilles à l'arbre Huffman
 ****************************************/
void creer_feuilles_huffman(noeud *arbre_huffman[], int tab_global[], int *nb_noeuds) {
    int i;
    for (i = 0; i < 256; i++) {
        if (tab_global[i] > 0) {
            arbre_huffman[*nb_noeuds] = creer_feuille(tab_global, i);
            (*nb_noeuds)++;
        }
    }
}

/****************************************
 * fonction : construire_arbre_huffman
 * description : Répète le processus de création de noeuds jusqu'à ce que l'arbre de Huffman soit
 *               entièrement construit, c'est-à-dire qu'il ne reste plus qu'un seul noeud
 *               représentant la racine de l'arbre.
 * entree : tableau de pointeurs vers noeud (arbre_huffman), pointeur vers entier (nb_noeuds)
 * sortie : aucune (void), construit l'arbre de Huffman en combinant les noeuds
 ****************************************/
void construire_arbre_huffman(noeud *arbre_huffman[], int *nb_noeuds) {
    while (*nb_noeuds > 1) {
        creer_noeud(arbre_huffman, *nb_noeuds);
        (*nb_noeuds)--;
    }
}


/****************************************
 * fonction : liberer_arbre
 * description : Libère récursivement toute la mémoire allouée pour un arbre Huffman
 * entree : pointeur vers le noeud racine de l'arbre
 * sortie : aucune (void), libère la mémoire de tous les noeuds de l'arbre
 ****************************************/
void liberer_arbre(noeud *racine) {
    if (racine != NULL) {
        liberer_arbre(racine->gauche);
        liberer_arbre(racine->droit);
        free(racine);
    }
}

/****************************************
 * fonction : liberer_inis
 * description : Libère tous les arbres stockés dans un tableau d'arbres
 * entree : tableau de pointeurs vers noeud a[]
 * sortie : aucune (void), libère la mémoire de tous les noeuds dans le tableau
 ****************************************/
void liberer_inis(noeud *a[]){
    int i;
    for (i = 0; i < 256; i++) {
        if (a[i] != NULL) {
            liberer_arbre(a[i]);
            a[i] = NULL;
        }
    }
}

/****************************************
 * fonction : afficher_aide
 * description : Affiche des informations sur les différentes options de ligne de commande disponibles 
 *               pour la compression et la décompression.
 * entree : aucune
 * sortie : aucune (void), affiche l'aide sur la sortie standard
 ****************************************/
void afficher_aide() {
  printf("les différentes options sont : \n-c : compression <fichier_a_compresse> <fichier_compresse>\n-d : décompression (si un chemin dossier_cible est spécifié alors la décompression doit se faire dans dossier_cible, sinon elle doit s’effectuer dans le dossier courant)\n-h : doit afficher une page d’aide à l’utilisation de votre programme (comme une page du man)\n");
}



/****************************************
 * fonction : compression_rec
 * description : Parcourt récursivement les dossiers et fichiers à partir du chemin donné et 
 *               effectue des opérations de compression sur chacun d'eux. Si un fichier est trouvé, 
 *               il est traité et son occurrence est comptabilisée. Si un dossier est trouvé, 
 *               la fonction s'appelle récursivement pour ce dossier.
 * entree : pointeur vers une chaîne de caractères (chemin_dossier), 
 *          pointeur vers une chaîne de caractères (chemin_fichier_compresse), 
 *          pointeur vers FILE (fichier_compresse), 
 *          tableau de pointeurs vers noeud (alphabet), 
 *          tableau d'entiers (tab_global) pour les occurrences de caractères
 * sortie : aucune (void), peut terminer l'exécution en cas d'erreur de lecture ou d'accès fichier/dossier
 ****************************************/
void compression_rec( char *chemin_dossier,char *chemin_fichier_compresse, FILE *fichier_compresse, noeud *alphabet[], int tab_global[]) {
    struct dirent *fichierLu=NULL;
    DIR *dossier=NULL;
    FILE *fichier=NULL;
    char nom_fichier[PATH_MAX];
    struct stat info;

    if (stat(chemin_dossier, &info) != 0) {
        printf("Erreur on arrive pas à savoir si le chemin amene vers un fichier ou un dossier");
        exit(EXIT_FAILURE);
    }
    if (S_ISREG(info.st_mode)) {
       fichier = fopen(chemin_dossier, "rb");
        if (fichier == NULL) {
        printf( "Erreur lors de l'ouverture du fichier\n");
            return;
        }
        occurence(fichier, tab_global);
        fclose(fichier);
        return;

    }
    dossier = opendir(chemin_dossier);
    if (dossier == NULL) {
        printf("Erreur lors de l'ouverture du dossier\n");
        exit(EXIT_FAILURE);
    }
    
    while ((fichierLu = readdir(dossier)) != NULL) {
        if (strcmp(fichierLu->d_name, ".") == 0 || strcmp(fichierLu->d_name, "..") == 0) {
            continue; 
        }

        sprintf(nom_fichier, "%s/%s", chemin_dossier, fichierLu->d_name);

       if (strcmp(nom_fichier, chemin_fichier_compresse) == 0) {
            continue;
        }
       if (S_ISDIR(info.st_mode)) {
           compression_rec(nom_fichier,chemin_fichier_compresse, fichier_compresse, alphabet, tab_global);
        } else {
            fichier = fopen(nom_fichier, "rb");
            if (fichier == NULL) {
                fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
                return ;
            }
            occurence(fichier, tab_global);
            fclose(fichier);
        }
    }
    closedir(dossier);
}


/****************************************
 * fonction : contenu_rec
 * description : Parcourt récursivement les dossiers et fichiers à partir du chemin donné et 
 *               écrit le chemin et le contenu compressé dans le fichier de sortie. Si un fichier 
 *               est trouvé, son chemin et son contenu compressé sont écrits dans le fichier 
 *               compressé. Si un dossier est trouvé, la fonction s'appelle récursivement pour ce dossier.
 * entree : pointeur vers une chaîne de caractères (chemin_dossier), 
 *          pointeur vers une chaîne de caractères (chemin_fichier_compresse), 
 *          pointeur vers FILE (fichier_compresse), 
 *          tableau de pointeurs vers noeud (alphabet)
 * sortie : aucune (void), peut terminer l'exécution en cas d'erreur d'ouverture de fichier ou de dossier
 ****************************************/
void contenu_rec(char *chemin_dossier, char* chemin_fichier_compresse, FILE *fichier_compresse, noeud *alphabet[]){
    struct dirent *fichierLu=NULL;
    DIR *dossier=NULL;
    FILE *fichier=NULL;
    char nom_fichier[PATH_MAX];
    struct stat info;

    if (stat(chemin_dossier, &info) != 0) {
        perror("Erreur on arrive pas à savoir si le chemin amene vers un fichier ou un dossier");
        exit(EXIT_FAILURE);
    }
    if (S_ISREG(info.st_mode)) {
       fichier = fopen(chemin_dossier, "rb");
        if (fichier == NULL) {
        printf( "Erreur lors de l'ouverture du fichier\n");
            return;
        }
        fprintf(fichier_compresse, "%s ",chemin_dossier );
            contenu_compresse(fichier, fichier_compresse, alphabet);
        fclose(fichier);
        return;

    }

    dossier = opendir(chemin_dossier);
       if (dossier == NULL) {
            perror("Erreur lors de la réouverture du dossier\n");
            exit(EXIT_FAILURE);
        }
        
      while((fichierLu = readdir(dossier))!= NULL){
        if(strcmp(fichierLu->d_name, ".") == 0 || strcmp(fichierLu->d_name, "..") == 0){
          continue;
        }
        sprintf(nom_fichier, "%s/%s",chemin_dossier, fichierLu->d_name);
         if (strcmp(nom_fichier, chemin_fichier_compresse) == 0) {
            continue;
         }
	 if (!S_ISDIR(info.st_mode)) {
            fichier = fopen(nom_fichier, "rb");
            if (fichier == NULL) {
                fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", fichierLu->d_name);
                return;
            }
            printf("fichier : %s \n", nom_fichier);
            printf("taille fichier : %d\n",taille_fichier(nom_fichier));
            fprintf(fichier_compresse, "%s ",nom_fichier );
            contenu_compresse(fichier, fichier_compresse, alphabet);
            fclose(fichier);
        }
        else{
            contenu_rec(nom_fichier, chemin_fichier_compresse, fichier_compresse, alphabet);
        }
      }
      closedir(dossier); 
}

