/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:20:09 by ksan              #+#    #+#             */
/*   Updated: 2025/07/16 16:50:00 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// debug function
void	print_llist(t_list *llist_a, t_list *llist_b)
{
	t_list *a;
	t_list *b;

	a = llist_a;
	b = llist_b;
	printf("A ");
	while (a)
	{
		printf("Index: %d = %d \n", a->index,*(a->num));
		a = a->next;
	}
	printf("\n");
	printf("B ");
	while (b)
	{
		printf("%d ", *(b->num));
		b = b->next;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	t_list *a;
	t_list *b;

	a = parse_input(argc, argv);
	b = NULL;
	index_nodes(a);
//	printf("Before\n");
//	print_llist(a, b);

	sort(&a, &b);

//	printf("\nAfter\n");
//	print_llist(a, b);

	free_linkedlist(a);
	//free_linkedlist(b);
}
