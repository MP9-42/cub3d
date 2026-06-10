/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:47:14 by MP9               #+#    #+#             */
/*   Updated: 2025/08/08 15:28:15 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstr;
	size_t	i;
	size_t	i2;

	i = 0;
	i2 = 0;
	if (!s1 || !s2)
		return (NULL);
	joinstr = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joinstr)
		return (NULL);
	while (s1[i] != '\0')
	{
		joinstr[i] = s1[i];
		i++;
	}
	while (s2[i2] != '\0')
	{
		joinstr[i + i2] = s2[i2];
		i2++;
	}
	joinstr[i + i2] = '\0';
	return (joinstr);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;
	size_t	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * len + 1);
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		i;
	size_t		i3;

	if (!s)
		return (NULL);
	i = 0;
	i3 = 0;
	if (ft_strlen(s) > start)
	{
		while (s[start + i] != '\0' && i < len)
			i++;
	}
	str = (char *)malloc(sizeof(char) * i + 1);
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
