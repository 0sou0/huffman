#!/usr/bin/env bash

count=20
a="$1"
a2="nombres_aleatoires"
a3="texte_repete"
b=".txt"
c="res"

for i in $(seq $count)
do
    ./huffman5 -c "${a}$i${b}" "${c}$i${b}"
done



# Récupère la liste des tailles de fichiers
tailles=($(ls -l ${a}*.txt | awk '{print $5}'))

# Trie les tailles
IFS=$'\n' tailles_triees=($(sort -n <<<"${tailles[*]}"))
unset IFS

# Supprime le fichier le plus lourd et le plus léger
tailles_sans_extremes=("${tailles_triees[@]:1:${#tailles_triees[@]}-2}")

# Calcule la somme des tailles restantes
somme=0
for taille in "${tailles_sans_extremes[@]}"; do
  let somme+=taille
done

# Calcule la moyenne
moyenne1=0
if [ ${#tailles_sans_extremes[@]} -gt 0 ]; then
  moyenne1=$(($somme / ${#tailles_sans_extremes[@]}))
fi

# Affiche la moyenne
echo "La moyenne des tailles des fichiers textes est : $moyenne1 octets"

# Calculer les différences au carré
somme_carre=0
for taille in "${tailles_sans_extremes[@]}"; do
  diff=$((taille - moyenne1))
  carre=$((diff * diff))
  let somme_carre+=carre
done

# Calculer la moyenne des différences au carré
moyenne_carre=$(awk -v somme="$somme_carre" -v n="${#tailles_sans_extremes[@]}" 'BEGIN {print somme / n}')

# Calculer l'ecart type
ecart_type=$(awk -v moy="$moyenne_carre" 'BEGIN {print sqrt(moy)}')

echo "L'écart type des tailles fichiers textes est : $ecart_type octets"



# Récupère la liste des tailles de fichiers
tailles=($(ls -l res*.txt | awk '{print $5}'))

# Trie les tailles
IFS=$'\n' tailles_triees=($(sort -n <<<"${tailles[*]}"))
unset IFS

# Supprime le fichier le plus lourd et le plus léger
tailles_sans_extremes=("${tailles_triees[@]:1:${#tailles_triees[@]}-2}")

# Calcule la somme des tailles restantes
somme=0
for taille in "${tailles_sans_extremes[@]}"; do
  let somme+=taille
done

# Calcule la moyenne
moyenne2=0
if [ ${#tailles_sans_extremes[@]} -gt 0 ]; then
  moyenne2=$(($somme / ${#tailles_sans_extremes[@]}))
fi

# Affiche la moyenne
echo "La moyenne des tailles fichiers compressés est : $moyenne2 octets"

pourcentage_compression=$(awk -v init="$moyenne1" -v fin="$moyenne2" 'BEGIN {printf "%.2f", (init - fin) / init * 100}')
echo "Le pourcentage de compression est : $pourcentage_compression%"

# Calculer les différences au carré
somme_carre=0
for taille in "${tailles_sans_extremes[@]}"; do
  diff=$((taille - moyenne2))
  carre=$((diff * diff))
  let somme_carre+=carre
done

# Calculer la moyenne des différences au carré
moyenne_carre=$(awk -v somme="$somme_carre" -v n="${#tailles_sans_extremes[@]}" 'BEGIN {print somme / n}')

# Calculer l'ecart type
ecart_type=$(awk -v moy="$moyenne_carre" 'BEGIN {print sqrt(moy)}')

echo "L'écart type des tailles fichiers compressés est : $ecart_type octets"


