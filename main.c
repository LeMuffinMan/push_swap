/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 22:49:41 by oelleaum          #+#    #+#             */
/*   Updated: 2025/01/29 01:21:30 by oelleaum         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


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

typedef struct s_list
{
  struct s_list *prev;
  bool          start;
  int           n;
  struct s_list *next;
} t_list;


//je cherche a la print, pas la modifier : donc un simple pointeur * 
void print_lst(t_list *l)
{
  t_list *ptr;
  int i;

  i = 0;
  if (l == NULL)
    return ;
  ptr = l;
  printf("node #%d = %d | start = %d\n", i, ptr->n, ptr->start);
  ptr = ptr->next;
  // une fois sur le maillon inexistant : la boucle stop
  while (ptr->start == false)
  {
     printf("node #%d = %d\n", i, ptr->n);
    //comme pour le swap ! c'est deux pointeurs 
    ptr = ptr->next;
  }
}

t_list *lst_last(t_list *lst)
{
  t_list *ptr;

  ptr = lst;
  if (ptr == NULL)
    return (NULL);
  ptr = ptr->next;
  //le pb etait que ptr->start me permet pas de checker l'element suivant : 
  //on s'arrete quand "le prochain est le premier"
  while (ptr->next->start != true)
    ptr = ptr->next;
  return (ptr);
}

//pour init : il manque le "circulaire"
void add_back(t_list **lst, int n)
{
  t_list *ptr;
  t_list *new;

  new = malloc(sizeof(t_list) * 1);
  /* if (new == NULL) */
  /*   lst_clear(*lst); */
  //si ma liste est vide 
  if (*lst == NULL)
  {
    /* printf("la\n"); */
    new->prev = new;
    new->next = new;
    new->n = n;
    new->start = true;
    *lst = new;
  }
  // liste pas vide : on veut set : 
  //  - prev du premier 
  //  - prev & next du dernier (new) 
  else 
  { 
    ptr = *lst;
    ptr->prev = lst_last(*lst);
    ptr = ptr->prev;
    /* printf("ptr->n = %d\n", ptr->n); */
    new->prev = ptr;
    ptr->next = new;
    new->next = *lst;
    new->n = n;
    new->start = false;
  }
}

int	ft_atoi(const char *nptr)
{
	char			sign;
	long long int	n;

	n = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		sign = *nptr;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n += *nptr - '0';
		nptr++;
		if (*nptr >= '0' && *nptr <= '9')
			n *= 10;
	}
	if (sign == '-')
		n *= -1;
	return (n);
}

 //INIT !
  //on doit creer la liste en respectant l'ordre dans lequel on recoit les int 
  //donc on add back pour que le premier arg soit le premier de la pile 
  /* add_back(&l, atoi(av[i]) */

  // creer une liste de 5 elements
  // chaque element a 
  //  - un next vers le suivant
  //  - un prev vers le precedent
  //Le next du dernier element pointe vers le premier
  //le prev du premier elment pointe vers le dernier
  //
void init_stack(t_list **l, char **av)
{
  int i;

  i = 0;
  while (av[++i])
    add_back(l, atoi(av[i]));
  //Dabuche parsing warning ./a.out " 4 5 6"
}

/* ra (rotate a): Shift up all elements of stack a by 1. */
/* The first element becomes the last one. */
/* rb (rotate b): Shift up all elements of stack b by 1. */
/* The first element becomes the last one. */
void rotate(t_list **l)
{
  (*l)->start = false;
  (*l)->next->start = true;
  *l = (*l)->next;
}

/* rr : ra and rb at the same time. */
void rotate_both(t_list **la, t_list **lb)
{
  rotate(la);
  rotate(lb);
}

/* rra (reverse rotate a): Shift down all elements of stack a by 1. */
/* The last element becomes the first one. */
/* rrb (reverse rotate b): Shift down all elements of stack b by 1. */
/* The last element becomes the first one. */
void reverse_rotate(t_list **l)
{
  (*l)->prev->start = true;
  (*l)->start = false;
  *l = (*l)->prev;
}

/* rrr : rra and rrb at the same time. */
void reverse_rotate_both(t_list **la, t_list **lb)
{
  reverse_rotate(la);
  reverse_rotate(lb);
}

/* sa (swap a): Swap the first 2 elements at the top of stack a. */
/* Do nothing if there is only one or no elements. */
/* sb (swap b): Swap the first 2 elements at the top of stack b. */
/* Do nothing if there is only one or no elements. */
void swap(t_list **l)
{
  int tmp;

  tmp = (*l)->n;
  (*l)->n = (*l)->next->n;
  (*l)->next->n = tmp;
}

/* ss : sa and sb at the same time. */
void swap_both(t_list **la, t_list **lb)
{
  swap(la);  
  swap(lb);  
}

/* pa (push a): Take the first element at the top of b and put it at the top of a. */
/* Do nothing if b is empty. */
/* pb (push b): Take the first element at the top of a and put it at the top of b. */
/* Do nothing if a is empty */
void push(t_list **la, t_list **lb)
{
  //on met le 1er node en haut de lb, on le met en haut de la
  (void)la;
  t_list *last;
  t_list *tmp;

  tmp = *lb;
  (*lb)->start = false;
  last = (*lb)->prev;
  *lb = (*lb)->next;
  (*lb)->start = true;
  (*lb)->prev = last;
  last->next = *lb;  //lb a toujours son premier element
  //la, lb a perdu un element (pas free !)
  //il faut qu'on le branche sur la 
  tmp->next = *la;
  tmp->prev = (*la)->prev;
  (*la)->prev = tmp;
  tmp->prev->next = tmp;
  (*la)->start = false;
  tmp->start = true;
  *la = tmp;

  /* la->next.n = la.n; */
  // addfront sur lb, avec le premier node de la
  // la->next.n = la.n
  //
  /* t_list *tmp; */
  /**/
  /* tmp = la->next; */
  //
  // on vire le premier node de la :
  //  - tmp.start = true
  //  - tmp->prev = lst_last(tmp) // peut etre qu'il faut un iter ?
  //  - la = tmp 
  //  
  //
}

void free_list(t_list *l)
{
    t_list *tmp = l;
    t_list *next_node;
    
    if (!l)
        return;
    l->prev->next = NULL;
    while (tmp)
    {
        next_node = tmp->next;
        free(tmp);
        tmp = next_node;
    }
}


void init_stackb(t_list **l)
{
  int i;

  i = -6;
  while (++i < 0)
    add_back(l, i);
  //Dabuche parsing warning ./a.out " 4 5 6"
}

int main (int ac, char **av)
{
  //l'idee est de garder ce pointeur vers le 1er element de ma liste 
  t_list *la = NULL;
  t_list *lb = NULL;
  
  if (ac <= 1)
  {
    printf("ERROR : not enough arguments\n");
    return (1);
  }
  init_stack(&la, av);
  printf("init la:\n");
  print_lst(la);
  init_stackb(&lb);
  printf("\ninit lb:\n");
  print_lst(lb);

  printf("\nswap la :\n");
  swap(&la);
  print_lst(la);
  
  printf("\nswap lb :\n");
  swap(&lb);
  print_lst(lb);
  
  printf("\nss :\n");
  swap_both(&la, &lb);
  printf("la : \n");
  print_lst(la);
  printf("lb : \n");
  print_lst(lb);
  
  printf("\npush a :\n");
  push(&la, &lb);
  printf("la : \n");
  print_lst(la);
  printf("lb : \n");
  print_lst(lb);
  
  printf("\npush b :\n");
  push(&lb, &la);
  printf("la : \n");
  print_lst(la);
  printf("lb : \n");
  print_lst(lb);
  
  printf("\nrotate la :\n");
  rotate(&la);
  print_lst(la);
  
  printf("\nrotate lb :\n");
  rotate(&lb);
  print_lst(lb);
  
  printf("\nrotate both :\n");
  rotate_both(&la, &lb);
  
  printf("\nla :\n");
  print_lst(la);
  
  printf("\nlb :\n");
  print_lst(lb);
  
  printf("\nreverse rotate la :\n");
  reverse_rotate(&la);
  print_lst(la);
  
  printf("\nreverse rotate lb :\n");
  reverse_rotate(&lb);
  print_lst(lb);

  printf("\nreverse rotate both :\n");
  reverse_rotate_both(&la, &lb);
  print_lst(la);
  print_lst(lb);

  free_list(la);
  free_list(lb);
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
