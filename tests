
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

# Compter le nombre total d'opérations
ops=$(echo "$push_swap_output" | wc -l)

# Compter le nombre d'occurrences de chaque opération
ra=$(echo "$push_swap_output" | grep -c "ra")
rb=$(echo "$push_swap_output" | grep -c "rb")
rr=$(echo "$push_swap_output" | grep -c "rr")
rra=$(echo "$push_swap_output" | grep -c "rra")
rrb=$(echo "$push_swap_output" | grep -c "rrb")
rrr=$(echo "$push_swap_output" | grep -c "rrr")
sa=$(echo "$push_swap_output" | grep -c "sa")
sb=$(echo "$push_swap_output" | grep -c "sb")
ss=$(echo "$push_swap_output" | grep -c "ss")

# Calculer les pourcentages
total_ops=$((ops == 0 ? 1 : ops))
perc_ra=$((ra * 100 / total_ops))
perc_rb=$((rb * 100 / total_ops))
perc_rr=$((rr * 100 / total_ops))
perc_rra=$((rra * 100 / total_ops))
perc_rrb=$((rrb * 100 / total_ops))
perc_rrr=$((rrr * 100 / total_ops))
perc_sa=$((sa * 100 / total_ops))
perc_sb=$((sb * 100 / total_ops))
perc_ss=$((ss * 100 / total_ops))

# Afficher les résultats
echo "Ops : $ops"
echo "ra  : $ra ($perc_ra%)"
echo "rb  : $rb ($perc_rb%)"
echo "rr  : $rr ($perc_rr%)"
echo "rra : $rra ($perc_rra%)"
echo "rrb : $rrb ($perc_rrb%)"
echo "rrr : $rrr ($perc_rrr%)"
echo "sa  : $sa ($perc_sa%)"
echo "sb  : $sb ($perc_sb%)"
echo "ss  : $ss ($perc_ss%)"

# Passer l'output de push_swap à checker_linux et afficher le résultat
output_checker=$(echo "$push_swap_output" | ./checker_linux $args)
echo "checker_linux : $output_checker"
