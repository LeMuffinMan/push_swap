#include <stdbool.h>

typedef struct s_list
{
  struct s_list *prev;
  bool          start;
  int           n;
  struct s_list *next;
} t_list;


void print_lst(t_list *l);
t_list *lst_last(t_list *lst);
void add_back(t_list **lst, int n);
int	ft_atoi(const char *nptr);
int init_stack(t_list **l, char **av);
void rotate(t_list **l);
void rotate_both(t_list **la, t_list **lb);
void reverse_rotate(t_list **l);
void reverse_rotate_both(t_list **la, t_list **lb);
void swap(t_list **l);
void swap_both(t_list **la, t_list **lb);
void push(t_list **la, t_list **lb);
void free_list(t_list *l);
void init_stackb(t_list **l);
