#ifndef _OUTILS_H_
#define _OUTILS_H_


/****************************************
 * fonction : usage
 * description : Affiche l'usage du programme pour informer l'utilisateur de la manière correcte de lancer le programme
 * entree : chaîne de caractères s (nom du programme)
 * sortie : aucune (void), affiche un message sur la sortie standard
 ****************************************/

void usage(char *s);



/****************************************
 * fonction : liberer_arbre
 * description : Libère récursivement toute la mémoire allouée pour un arbre Huffman
 * entree : pointeur vers le noeud racine de l'arbre
 * sortie : aucune (void), libère la mémoire de tous les noeuds de l'arbre
 ****************************************/
void liberer_arbre(noeud *racine);


/****************************************
 * fonction : liberer_inis
 * description : Libère tous les arbres stockés dans un tableau d'arbres
 * entree : tableau de pointeurs vers noeud a[]
 * sortie : aucune (void), libère la mémoire de tous les noeuds dans le tableau
 ****************************************/
void liberer_inis(noeud *a[]);


/****************************************
 * fonction : afficher_aide
 * description : Affiche des informations sur les différentes options de ligne de commande disponibles 
 *               pour la compression et la décompression.
 * entree : aucune
 * sortie : aucune (void), affiche l'aide sur la sortie standard
 ****************************************/
void afficher_aide();


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
void compression_rec( char *chemin_dossier,char *chemin_fichier_compresse, FILE *fichier_compresse, noeud *alphabet[], int tab_global[]);


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
void contenu_rec(char *chemin_dossier, char* chemin_fichier_compresse, FILE *fichier_compresse, noeud *alphabet[]);

/****************************************
 * fonction : compter_nombre_feuilles
 * description : Compte le nombre de noeuds feuilles (caractères uniques) dans l'arbre de Huffman,
 *               qui ont été utilisés lors de la construction de l'arbre.
 * entree : tableau de pointeurs vers noeud (alphabet)
 * sortie : entier représentant le nombre de feuilles dans l'arbre de Huffman
 ****************************************/
int compter_nombre_feuilles(noeud *alphabet[]);
   
/****************************************
 * fonction : initialiser_arbre_huffman
 * description : Alloue la mémoire pour chaque élément de l'arbre Huffman et initialise
 *               chaque pointeur à NULL pour éviter des pointeurs non initialisés.
 * entree : tableau de pointeurs vers noeud (arbre_huffman)
 * sortie : aucune (void), termine le programme en cas d'erreur d'allocation mémoire
 ****************************************/
void initialiser_arbre_huffman(noeud *arbre_huffman[]);
    

/****************************************
 * fonction : initialiser_alphabet
 * description : Initialise chaque pointeur de l'alphabet à NULL pour préparer la construction
 *               de l'arbre de Huffman.
 * entree : tableau de pointeurs vers noeud (alphabet)
 * sortie : aucune (void), initialise l'alphabet pour le codage de Huffman
 ****************************************/
void initialiser_alphabet(noeud *alphabet[]);

/****************************************
 * fonction : creer_feuilles_huffman
 * description : Parcourt le tableau d'occurrences et pour chaque caractère avec une occurrence
 *               non nulle, crée un noeud feuille et l'ajoute à l'arbre Huffman.
 * entree : tableau de pointeurs vers noeud (arbre_huffman), tableau des occurrences (tab_global),
 *          pointeur vers entier (nb_noeuds) pour suivre le nombre actuel de noeuds dans l'arbre
 * sortie : aucune (void), ajoute des feuilles à l'arbre Huffman
 ****************************************/
void creer_feuilles_huffman(noeud *arbre_huffman[], int tab_global[], int *nb_noeuds);

/****************************************
 * fonction : construire_arbre_huffman
 * description : Répète le processus de création de noeuds jusqu'à ce que l'arbre de Huffman soit
 *               entièrement construit, c'est-à-dire qu'il ne reste plus qu'un seul noeud
 *               représentant la racine de l'arbre.
 * entree : tableau de pointeurs vers noeud (arbre_huffman), pointeur vers entier (nb_noeuds)
 * sortie : aucune (void), construit l'arbre de Huffman en combinant les noeuds
 ****************************************/
void construire_arbre_huffman(noeud *arbre_huffman[], int *nb_noeuds);


int taille_fichier(char *nom_fichier);

#endif
