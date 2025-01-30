/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:49:41 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/30 18:14:32 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdlib.h>
#include <stdio.h>

//PAS d'OPERATION SI LA PILE EST DEJA TRIEE 
////tester les ints min et les ints max 


/* pa (push a): Take the first element at the top of b and put it at the top of a. */
/* Do nothing if b is empty. */

//addfront 
//rm  vieux node 
//rebrancher 

/* void pa(t_list **la, t_list **lb) */
/* { */
/**/
  /* if (*lb == NULL) */
  /*   return ; */
  /* (*lb)->next->prev = NULL; */
  /* if (*lb->next != NULL) */
  /*   (*lb)->next = *la; */
  /* else  */
  /*   return ; */
  /* (*la)->prev = *lb; */
/* } */

/* pb (push b): Take the first element at the top of a and put it at the top of b. */
/* Do nothing if a is empty. */




//je cherche a la print, pas la modifier : donc un simple pointeur *l 

// /!\ un seul arg part en vrille : un cas d'erreur 
// cas sur peu d'arguments : mois de 3 ca bug 

int main (int ac, char **av)
{
  //l'idee est de garder ce pointeur vers le 1er element de ma liste 
  t_list *la = NULL;
  t_list *lb = NULL;
  
  if (ac <=1) // ARG "1 5 -65" comme seul input ? 
  {
    printf("ERROR : not enough arguments\n");
    return (1);
  }
  init_stack(&la, av);
  printf("---------------------------\ninit la:\n");
  print_lst(la);
  /* init_stackb(&lb); */
  /* printf("---------------------------\ninit lb:\n"); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\nswap la :\n"); */
  /* swap(&la); */
  /* print_lst(la); */
  /**/
  /* printf("---------------------------\nswap lb :\n"); */
  /* swap(&lb); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\nss :\n"); */
  /* swap_both(&la, &lb); */
  /* printf("la : \n"); */
  /* print_lst(la); */
  /* printf("lb : \n"); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\npush a :\n"); */
  /* push(&la, &lb); */
  /* printf("la : \n"); */
  /* print_lst(la); */
  /* printf("lb : \n"); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\npush b :\n"); */
  /* push(&lb, &la); */
  /* printf("la : \n"); */
  /* print_lst(la); */
  /* printf("lb : \n"); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\nrotate la :\n"); */
  /* rotate(&la); */
  /* print_lst(la); */
  /**/
  /* printf("---------------------------\nrotate lb :\n"); */
  /* rotate(&lb); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\nrotate both :\n"); */
  /* rotate_both(&la, &lb); */
  /**/
  /* printf("\nla :\n"); */
  /* print_lst(la); */
  /**/
  /* printf("\nlb :\n"); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\nreverse rotate la :\n"); */
  /* reverse_rotate(&la); */
  /* print_lst(la); */
  /**/
  /* printf("---------------------------\nreverse rotate lb :\n"); */
  /* reverse_rotate(&lb); */
  /* print_lst(lb); */
  /**/
  /* printf("---------------------------\nreverse rotate both :\n"); */
  /* reverse_rotate_both(&la, &lb); */
  /* printf("\nla :\n"); */
  /* print_lst(la); */
  /* printf("\nlb :\n"); */
  /* print_lst(lb); */

  free_list(&la);
  /* free_list(&lb); */
  return (0);
}
  //dans fractol je declare une struct : ici je declare un pointeur sur la struct :
  //C'EST POUR CA QUE envoyer &l ici peut etre recupere en **lst
  /* t_list *a = NULL; */
  /* t_list *b = NULL; */
  /* t_list *ptr = NULL; */
  /**/
  /* (void)ptr; */
  /* add_front(&a, 5); */
  /* add_front(&a, 1); */
  /*  printf("\n"); */ 
  /* add_front(&b, 2); */
  /* add_front(&b, 8); */
  /*  add_back(&a, 1);  */
  /* print_lst(a); */
  /* printf("\n"); */
  /* print_lst(b); */
  /* ptr = lst_last(a); */
  /* printf("\nlast = %d\n\n", ptr->n); */
  /* print_rev_lst(a); */
  /* printf("\n"); */
  /* print_rev_lst(b); */
/**/
/* (*lst) */
/* *lst->next */
/**/
/* (**lst) */
/* (*lst)->next */
