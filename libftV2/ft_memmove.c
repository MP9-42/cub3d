/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:36:05 by MP9               #+#    #+#             */
/*   Updated: 2025/07/11 17:21:57 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*sorc;
	char		*dest;

	i = 0;
	sorc = (const char *)src;
	dest = (char *)dst;
	if (dst > src)
	{
		while (len != 0)
		{
			dest[len - 1] = sorc[len - 1];
			len--;
		}
	}
	if (dst < src)
	{
		while (i != len)
		{
			dest[i] = sorc[i];
			i++;
		}
	}
	return (dst);
}
