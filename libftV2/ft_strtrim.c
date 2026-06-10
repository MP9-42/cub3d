/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:22:50 by MP9               #+#    #+#             */
/*   Updated: 2025/07/16 18:56:48 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, char *src, size_t n)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < (int)n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[begin]) && s1[begin])
		begin++;
	while (ft_strchr(set, s1[end - 1]) && end > begin)
		end--;
	str = (char *)malloc(sizeof(char) * ((end - begin) + 1));
	if (!str)
		return (NULL);
	ft_strncpy(str, (char *)s1 + begin, (end - begin));
	str[end - begin] = '\0';
	return (str);
}
