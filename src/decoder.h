
#ifndef DECODER_H_
#define DECODER_H_



/****************************************
 * fonction : lire_entete
 * description : Lit l'en-tête du fichier compressé pour extraire l'alphabet utilisé, 
 *               avec les occurrences, les bits utilisés pour chaque caractère, et leur codage
 * entree : pointeur vers fichier FILE *fichier, tableau de pointeurs vers noeud alphabet[]
 * sortie : aucune (void), termine le programme en cas d'erreur de lecture
 ****************************************/
void lire_entete(FILE *fichier, noeud *alphabet[]);

/****************************************
 * fonction : lire_contenu
 * description : Lit le contenu compressé, décode les caractères selon l'alphabet et les écrit dans un fichier de sortie
 * entree : pointeur vers fichier FILE *fichier_compresse, tableau de pointeurs vers noeud alphabet[]
 * sortie : aucune (void), crée un fichier "decompresse.txt" contenant le texte décompressé
 ****************************************/
void lire_contenu(FILE *fichier_compresse, noeud *alphabet[]);

#endif 
