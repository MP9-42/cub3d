/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:32:42 by MP9               #+#    #+#             */
/*   Updated: 2025/07/15 19:56:42 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	zahl;
	int	vorzeichen;

	zahl = 0;
	vorzeichen = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			vorzeichen = vorzeichen * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		zahl = zahl * 10 + (*str - '0');
		str++;
	}
	return (vorzeichen * zahl);
}
