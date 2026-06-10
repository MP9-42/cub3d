/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:04:16 by MP9               #+#    #+#             */
/*   Updated: 2025/07/13 14:20:37 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	i2;
	size_t	i3;

	i = 0;
	i2 = ft_strlen(dst);
	i3 = ft_strlen(src);
	if (i2 >= dstsize)
		return (i3 + dstsize);
	while (src[i] != '\0' && i2 + i < dstsize - 1)
	{
		dst[i2 + i] = src[i];
		i++;
	}
	if (i2 + i < dstsize)
		dst[i2 + i] = '\0';
	return (i2 + i3);
}

// int main()
// {
// 	char *dest;

// 	dest[11] = 'a';
// 	ft_strlcat(dest, "lorem", 15);
// 	printf("%s\n", dest);
// 	strlcat(dest, "lorem", 15);
// 	printf("%s\n", dest);
// 	return(0);
// }