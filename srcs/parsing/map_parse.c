/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 14:54:27 by MP9               #+#    #+#             */
/*   Updated: 2026/06/11 15:55:43 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool is_correct(char **map)
{
	int bi;
	int si;
	int linelen;

	bi = 0;
	si = 0;
	while(map[bi])
	{
		linelen = ft_strlen(map[bi]);
		si = space_skip(map[bi]);
		if (!ft_isdigit(map[bi][si]) || !ft_isdigit(map[bi][linelen - 1]))
			return(false);
		while (map[bi][si])
		{
			if (map[bi][si] == ' ')
			{
				si = space_skip(&map[bi][si]);
				if (map[bi][si] != '1' && map[bi][si] != '\0')
					return(false);
			}
			if (!is_valid(map[bi][si]) && map[bi][si] != '\n')
				return(false);
			si++;
		}
		bi++;
	}
	return(true);
}
