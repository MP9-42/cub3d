/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:36:52 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 13:55:18 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_valid(char a)
{
	if (a == '0' || a == '1' || a == ' ')
		return (true);
	return (false);
}

int	space_skip(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	return (i);
}

void	kill_n(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

void	rf_helper(t_parsing *parsing, int *capacity, int i)
{
	char	**new_file;
	int		j;

	if (i < *capacity)
		return ;
	if (*capacity > INT_MAX / 2)
		return ;
	*capacity *= 2;
	new_file = malloc(sizeof(char *) * (*capacity + 1));
	if (!new_file)
		return ;
	j = 0;
	while (j < i)
	{
		new_file[j] = parsing->file[j];
		j++;
	}
	new_file[i] = NULL;
	free(parsing->file);
	parsing->file = new_file;
}
