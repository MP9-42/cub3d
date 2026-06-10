/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:15:42 by MP9               #+#    #+#             */
/*   Updated: 2025/07/16 14:27:49 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	slen;

	slen = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * slen + 1);
	if (!s2)
		return (NULL);
	while (*s1)
	{
		*s2 = *(char *)s1;
		s1++;
		s2++;
	}
	*s2 = '\0';
	return (s2 - slen);
}

// int	main()
// {
// 	printf("%s\n", ft_strdup("lorem ipsum dolor sit amet"));
// 	printf("%s\n", strdup("lorem ipsum dolor sit amet"));
// }