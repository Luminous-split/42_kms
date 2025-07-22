/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksan <ksan@student.42.sg>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:38:56 by ksan              #+#    #+#             */
/*   Updated: 2025/07/16 16:55:20 by ksan             ###   ########.sg       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_gracefully(t_list *llist);

static int	is_valid_num(char *str);

static int	parse_string(char **array, t_list **llist);

static int	dup_check(t_list *llist);

t_list	*parse_input(int argc, char **argv);

void	exit_gracefully(t_list *llist)
{
	ft_putstr_fd("Error\n", 2);
	free_linkedlist(llist);
	exit(EXIT_FAILURE);
}

static int	is_valid_num(char *str)
{
	int	i;

	if (*str == '\0')
		return (0);
	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
	{
		if (!(ft_isdigit(str[i])))
			return (0);
	}
	return (1);
}

static int	parse_string(char **array, t_list **llist)
{
	int	*num;
	int	failed;
	char	*temp_arr_index;
	char	**temp_array;

	failed = 0;
	temp_array = array;
	while (*temp_array)
	{
		temp_arr_index = *temp_array;
		if (is_valid_num(*temp_array) && !failed)
		{
			num = malloc(sizeof(int));
			*num = ft_atoi(*temp_array);
			add_back(llist, lst_new(num));
		}
		else
			failed = 1;
		free(temp_arr_index);
		temp_array++;
	}
	free(array);
	return (failed);
}

static int	dup_check(t_list *llist)
{
	t_list	*temp;
	t_list	*temp1;

	temp = llist;
	while (temp)
	{
		temp1 = temp->next;
		while (temp1)
		{
			if (*(temp->num) == *(temp1->num))
				return (1);
			temp1 = temp1->next;
		}
		temp = temp->next;
	}
	return (0);
}


t_list	*parse_input(int argc, char **argv)
{
	t_list	*stack_a;
	int	*num;
	int 	i;
	int	failed;

	i = 0;
	failed = 0;
	stack_a = NULL;
	while (++i < argc && !failed)
	{
		if (ft_strchr(argv[i], ' '))
			failed = parse_string(ft_split(argv[i], ' '), &stack_a);
		else if (is_valid_num(argv[i]))
		{
			num = malloc(sizeof(int));
			*num = ft_atoi(argv[i]);
			add_back(&stack_a, lst_new(num));
		}
		else
			failed = 1;
	}
	if (failed || dup_check(stack_a))
		exit_gracefully(stack_a);
	return (stack_a);
}
