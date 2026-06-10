/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:12:28 by MP9               #+#    #+#             */
/*   Updated: 2025/07/24 15:01:35 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newlst)
{
	t_list	*tmp;

	if (!lst || !newlst)
		return ;
	if (*lst == NULL)
	{
		*lst = newlst;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = newlst;
}
