
#!/bin/bash

# Set default size to 100 if no argument
size=${1:-100}

declare -A nums

# od (octal dump) : Commande utilisée pour afficher le contenu d'un fichier sous différents formats (hexadécimal, décimal, octal, etc.).
# -An : Supprime l'affichage des adresses de sortie (pas d'offset au début de la ligne).
# -N4 : Lit exactement 4 octets du fichier /dev/urandom (4 octets = 32 bits, ce qui permet de représenter un entier de 32 bits).
# -t d4 : Affiche ces 4 octets sous la forme d’un entier signé en base 10.

while (( ${#nums[@]} < size )); do
    num=$(od -An -N4 -t d4 /dev/urandom | tr -d ' ')
    nums["$num"]=1
done

echo "${!nums[@]}" > random_ints.txt

