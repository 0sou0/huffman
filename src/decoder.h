
#ifndef DECODER_H_
#define DECODER_H_



/****************************************
 * fonction : lire_entete
 * description : Lit l'en-tête du fichier compressé et initialise l'alphabet avec les noeuds
 *               correspondant à chaque caractère présent dans le fichier compressé.
 * entree : pointeur vers FILE (fichier), tableau de pointeurs vers noeud (alphabet)
 * sortie : aucune (void), termine le programme en cas d'erreur de lecture ou d'allocation mémoire
 ****************************************/
void lire_entete(FILE *fichier, noeud *alphabet[]);

/****************************************
 * fonction : lire_contenu
 * description : Lit le contenu compressé du fichier, décode chaque caractère selon l'alphabet
 *               et écrit le résultat dans le fichier de sortie. Les fichiers sont lus séquentiellement
 *               et décompressés un par un.
 * entree : pointeur vers FILE (fichier_compresse), tableau de pointeurs vers noeud (alphabet)
 * sortie : aucune (void), termine le programme en cas d'erreur de lecture ou d'écriture de fichier
 ****************************************/
void lire_contenu(FILE *fichier_compresse, noeud *alphabet[]);

/****************************************
 * fonction : creer_dossier
 * description : creer les differents dossiers necessaires pour la decompression
 * entree : nom du chemin du fichier
 * sortie : aucune (void), creer le dossier
 ****************************************/
void creer_dossier(char *cheminFichier);

#endif 
