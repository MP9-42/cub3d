/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:29:56 by MP9               #+#    #+#             */
/*   Updated: 2026/06/17 14:29:08 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool valid_chars(char **map)
{
	int bi;
	int si;

	bi = 0;
	while(map[bi])
	{
		si = 0;
		while(map[bi][si])
		{
			if (!ft_strchr("01NSEW \t", map[bi][si]))
				return(false);
			si++;
		}
		bi++;
	}
	return(true);
}

char **deep_copy_map(t_map *map)
{
	char **copy;
	int	bi;

	bi = 0;
	copy = ft_calloc(sizeof(char *), map->size);
	while (map->rmap[bi])
	{
		copy[bi] = ft_strdup(map->rmap[bi]);
		bi++;
	}
	return(copy);
}

void free_map(char **map, int size)
{
	while (size >= 0)
	{
		free(map[size]);
		size--;
	}
	free(map);
}

char	*ft_linedup(const char *s1)
{
	char	*s2;
	size_t	i;
	size_t j;
	size_t	len;

	i = 0;
	len = 0;
	if (!s1)
		return (NULL);
	while(s1[i] != '\0')
	{
		if (s1[i] == '\t')
			len += 4;
		else
			len++;
		i++;
	}
	s2 = (char *)malloc(sizeof(char) * len + 1);
	if (!s2)
		return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
    {
        if (s1[i] == '\t')
        {
            s2[j++] = ' ';
            s2[j++] = ' ';
            s2[j++] = ' ';
            s2[j++] = ' ';
        }
        else
            s2[j++] = s1[i];
        i++;
    }

    s2[j] = '\0';
    return (s2);
}
