#include <stdlib.h>
#include "push_swap.h"
#include <stdio.h>

void print_lst(t_list *l)
{
  t_list *ptr;
  int i;

  i = 1;
  if (l == NULL)
    return ;
  ptr = l;
  printf("node #%d = %d | start = %d\n", i, ptr->n, ptr->start);
  ptr = ptr->next;
  // une fois sur le maillon inexistant : la boucle stop
  while (ptr->start == false)
  {
    i++;
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

t_list *split_int(char **av)
{
  int i;
  int j;
  int sign;
  int n;
  t_list *l;

  i = 0;
  j = 0;
  sign = 1;
  while (av[1][i])
  {
    while ((!(is_digit(av[1][i])) || av[1][i] == '-') &&) // ils mettent un + ?
      i++;
    if (av[1][i] == '-')
    {
      sign = -1;
      i++;
    }
    while (is_digit(av[1][i]))
      j++;
    //n = atoi(ft_substr(av[1], i, j)) * sign;
      /* l = lst_new() ajouter un node pour chaque int et le relier  */
    i = i + j;
  }
  return (l);
}

int init_stack(t_list **l, char **av)
{
  int i;
  int j;

  j = 0;
  i = 0;
  if (!av[1][0])
    return (-1);
  l = split_int(av); // *l ?
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
void push(t_list **la, t_list **lb) //encore des pb ici
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
