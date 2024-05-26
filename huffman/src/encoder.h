#ifndef ENCODER_H_
#define ENCODER_H_


/****************************************
 * fonction : affichage_code
 * description : Affiche le code binaire d'un caractère 
 * entree : entier nbr_bits (nombre de bits du codage), entier codage (valeur du codage)
 * sortie : aucune (void), affiche le code 
 ****************************************/
void affichage_code(int nbr_bits, int codage);

/****************************************
 * fonction : creer_code
 * description : Crée le codage de Huffman pour un caractère et le stocke dans 'codage'
 * entree : pointeur vers noeud element, entier code (valeur du code), entier profondeur (nombre de bits),
 *          tableau de pointeurs vers noeud alphabet[]
 * sortie : aucune (void)
 ****************************************/
void creer_code(noeud *element, int code, int profondeur, noeud *alphabet[]);


 /****************************************
 * fonction : ecrire_bit
 * description : Écrit un bit dans un buffer et écrit le buffer dans un fichier si le buffer est plein
 * entree : pointeur vers fichier fichier, entier bit, pointeur vers char buffer, pointeur vers entier pos
 * sortie : aucune (void)
 ****************************************/
void ecrire_bit(FILE *fichier, int bit, char *buffer, int *pos);


 /****************************************
 * fonction : ecrire_code_huffman
 * description : Écrit le code de Huffman dans un fichier, bit par bit, en utilisant un buffer
 * entree : pointeur vers fichier fichier, entier codage, entier bits (nombre de bits du codage),
 *          pointeur vers char buffer, pointeur vers entier pos
 * sortie : aucune (void), écrit les bits dans le fichier
 ****************************************/
void ecrire_code_huffman(FILE *fichier, int codage, int bits, char *buffer, int *pos);


/****************************************
 * fonction : ecrire_entete
 * description : Écrit l'en-tête dans le fichier compressé, incluant le nombre de feuilles
 *               et pour chaque feuille, son caractère, son occurrence,
 *               la taille de son codage, et son codage binaire selon l'arbre de Huffman.
 * entree : pointeur vers FILE (fichier_compresse), tableau de pointeurs vers noeud (alphabet),
 *          entier nombre_feuilles indiquant le nombre de caractères uniques
 * sortie : aucune (void)
 ****************************************/
void ecrire_entete(FILE *fichier_compresse, noeud *alphabet[] , int nombre_feuilles);


 /****************************************
 * fonction : contenu_compresse
 * description : Parcourt le fichier à compresser, calcule la taille totale des données compressées
 *               en se basant sur le codage de Huffman et écrit les données compressées dans
 *               le fichier de sortie. Utilise la fonction ecrire_code_huffman pour chaque caractère.
 * entree : pointeur vers FILE (fichier) à compresser, pointeur vers FILE (fichier_compresse) pour
 *          écrire le contenu compressé, tableau de pointeurs vers noeud (alphabet) représentant
 *          l'arbre de Huffman
 * sortie : aucune (void)
 ****************************************/
void contenu_compresse(FILE *fichier, FILE *fichier_compresse, noeud *alphabet[]);


#endif

