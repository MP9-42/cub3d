/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:29:43 by MP9               #+#    #+#             */
/*   Updated: 2026/04/08 14:31:29 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_garbage	**get_gc_start(void)
{
	static t_garbage	*head = NULL;

	return (&head);
}

void	ft_putstr_err(char *s)
{
	if (!s)
		return ;
	while (*s)
	{
		write(STDERR_FILENO, s, 1);
		s++;
	}
}

void	__wrap_exit(int status)
{
	clear_gc();
	__real_exit(status);
}
