/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:43:33 by MP9               #+#    #+#             */
/*   Updated: 2025/07/15 15:27:09 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (--n != (size_t)-1)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s = (char *)s + 1;
	}
	return (NULL);
}
