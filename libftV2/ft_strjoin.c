/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:55:28 by MP9               #+#    #+#             */
/*   Updated: 2025/07/17 19:04:59 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstr;
	size_t	len;
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	joinstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!joinstr)
		return (NULL);
	while (s1[i] != '\0')
	{
		joinstr[i] = s1[i];
		i++;
	}
	while (s2[i2] != '\0')
	{
		joinstr[i] = s2[i2];
		i++;
		i2++;
	}
	joinstr[i] = '\0';
	return (joinstr);
}
