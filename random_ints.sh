
#!/bin/bash

# Définition des bornes pour un entier 32 bits signé
# INT_MIN=$((-2**31))  # -2147483648
# INT_MAX=$((2**31 - 1)) # 2147483647

# Générer 100 nombres aléatoires et les stocker dans un tableau
numbers=()
for ((i=0; i<$1; i++)); do
    numbers+=( $(od -An -N4 -t d4 /dev/urandom) )
done

args="${numbers[*]}"

echo "$args" > random_ints.txt

