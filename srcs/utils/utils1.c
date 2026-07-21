/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegeber <alegeber@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:36:52 by MP9               #+#    #+#             */
/*   Updated: 2026/07/21 17:04:42 by alegeber         ###   ########.fr       */
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
