/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:01:30 by MP9               #+#    #+#             */
/*   Updated: 2025/07/17 22:27:44 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	i2;
	size_t	i3;

	if (!s)
		return (NULL);
	i = 0;
	i2 = ft_strlen(s);
	i3 = 0;
	if (i2 > start)
	{
		while (s[start + i] != '\0' && i < len)
			i++;
	}
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	while (i3 < i && i != 0)
	{
		str[i3] = s[start + i3];
		i3++;
	}
	str[i3] = '\0';
	return (str);
}
