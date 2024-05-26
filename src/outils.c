#include "type.h"
 
 /****************************************
 * fonction : usage
 * description : Affiche l'usage du programme pour informer l'utilisateur de la manière correcte de lancer le programme
 * entree : chaîne de caractères s (nom du programme)
 * sortie : aucune (void), affiche un message sur la sortie standard
 ****************************************/
void usage(char *s){
    printf("Usage : %s <liste_fichier.txt> <fichier_compresse.txt> \n", s);
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
