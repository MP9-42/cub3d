/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:13:09 by MP9               #+#    #+#             */
/*   Updated: 2025/07/11 17:21:21 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*sorc;

	i = 0;
	dest = (char *)dst;
	sorc = (const char *)src;
	if (!src && !dst)
		return (NULL);
	while (i < n)
	{
		dest[i] = sorc[i];
		i++;
	}
	return (dst);
}
