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

#endif
