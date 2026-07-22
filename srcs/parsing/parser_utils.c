/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 12:29:56 by MP9               #+#    #+#             */
/*   Updated: 2026/07/22 14:28:10 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	valid_chars(char **map)
{
	int	bi;
	int	si;

	bi = 0;
	while (map[bi])
	{
		si = 0;
		while (map[bi][si])
		{
			if (!ft_strchr("016789NSEW \t", map[bi][si]))
				return (false);
			si++;
		}
		bi++;
	}
	return (true);
}

char	*ft_linedup(const char *s1)
{
	char	*s2;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = 0;
	if (!s1)
		return (NULL);
	while (s1[i] != '\0')
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
	tab_converter(s1, s2, &i, &j);
	s2[j] = '\0';
	return (s2);
}
