
#!/bin/bash

# Définition des bornes pour un entier 32 bits signé
INT_MIN=$((-2**31))  # -2147483648
INT_MAX=$((2**31 - 1)) # 2147483647

# Générer 100 nombres aléatoires et les stocker dans un tableau
numbers=()
for ((i=0; i<$1; i++)); do
    numbers+=( $(od -An -N4 -t d4 /dev/urandom) )
done

# Transformer le tableau en une seule ligne d'arguments
args="${numbers[*]}"

# Afficher la liste des nombres générés
echo "Liste générée :"
echo "$args"
echo

# Exécuter push_swap avec valgrind et afficher uniquement son output
echo "=== Valgrind Output ==="
valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./push_swap $args 2>&1 | tail -n 9
echo

# Exécuter push_swap normalement et stocker l'output
push_swap_output=$(./push_swap $args)

ops=$(./push_swap $args | wc -l) 

 # Afficher l'output de push_swap
echo "Ops : $ops"
echo

# Passer l'output de push_swap à checker_linux et afficher le résultat
output_checker=$(echo "$push_swap_output" | ./checker_linux $args)
echo "checker_linux : $output_checker"
