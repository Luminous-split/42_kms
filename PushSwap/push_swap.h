#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"

#define CHUNK_SIZE 15

typedef struct	s_list
{
	int		*num;
	int		index;
	struct	s_list	*next;
}	t_list;

//linked lists >>delete comments
t_list	*lst_new(void *content);
int	ft_lstsize(t_list *llist);
void	add_front(t_list **llist, t_list *new);
void	add_back(t_list **llist, t_list *new);
void	free_linkedlist(t_list *llist);

t_list	*parse_input(int argc, char **argv);
void	index_nodes(t_list *llist);

void	ft_sa(t_list **llist_a, int in_ss);
void	ft_ra(t_list **llist_a, int in_rr);
void	ft_rra(t_list **llist_a, int in_rrr);

void	ft_pa(t_list **llist_a, t_list **llist_b);

void	ft_sb(t_list **llist_b, int in_ss);
void	ft_rb(t_list **llist_b, int in_rr);
void	ft_rrb(t_list **llist_b, int in_rrr);

void	ft_pb(t_list **llist_a, t_list **llist_b);

void	ft_ss(t_list **llist_a, t_list **llist_b);
void	ft_rr(t_list **llist_a, t_list **llist_b);
void	ft_rrr(t_list **llist_a, t_list **llist_b);


void	sort(t_list **llist_a, t_list **llist_b);

