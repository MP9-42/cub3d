/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:46:59 by MP9               #+#    #+#             */
/*   Updated: 2025/07/15 19:31:20 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelen;

	if (len == 0 && !haystack)
		return (NULL);
	if (*needle == 0)
		return ((char *)haystack);
	needlelen = ft_strlen(needle);
	while (--len != (size_t) - 1 && *haystack && needlelen <= len + 1)
	{
		if (ft_strncmp(haystack, needle, needlelen) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

// int main()
// {
// 	const char str[] = "abcdefgh";
// 	const char str2[] = "abc";
// 	printf("%s\n", ft_strnstr(str,str2, 3));
// 	printf("%s\n", strnstr(str, str2, 3));
// }