/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:48:09 by MP9               #+#    #+#             */
/*   Updated: 2026/04/13 15:48:13 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*__wrap_malloc(size_t size)
{
	void	*ret_pointer;

	ret_pointer = __real_malloc(size);
	if (!ret_pointer)
	{
		ft_putstr_err("exit: malloc fail\n");
		__wrap_exit(EXIT_FAILURE);
	}
	add_node_gc(ret_pointer);
	return (ret_pointer);
}

void	__wrap_free(void *ptr)
{
	t_garbage	**head;
	t_garbage	*temp;

	head = get_gc_start();
	if (!ptr)
		return ;
	temp = *head;
	while (temp)
	{
		if (temp->content == ptr)
		{
			if (temp->prev)
				temp->prev->next = temp->next;
			else
				*head = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			__real_free(temp->content);
			__real_free(temp);
			return ;
		}
		temp = temp->next;
	}
	__real_free(ptr);
}

void	add_node_gc(void *ptr)
{
	t_garbage	**head;
	t_garbage	*new_node;
	t_garbage	*temp;

	new_node = __real_malloc(sizeof(t_garbage));
	if (!new_node)
	{
		ft_putstr_err("exit: malloc fail in gc\n");
		exit(EXIT_FAILURE);
	}
	head = get_gc_start();
	new_node->content = ptr;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

void	clear_gc(void)
{
	t_garbage	**head;
	t_garbage	*next;
	t_garbage	*temp;

	head = get_gc_start();
	temp = *head;
	while (temp)
	{
		next = temp->next;
		__real_free(temp->content);
		__real_free(temp);
		temp = next;
	}
	*head = NULL;
}
