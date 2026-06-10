/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: MP9 <mikjimen@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:23:08 by MP9               #+#    #+#             */
/*   Updated: 2025/07/20 17:19:24 by MP9              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp_list;
	t_list	*tmp_node;
	void	*new_content;

	tmp_list = NULL;
	tmp_node = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		tmp_node = ft_lstnew(new_content);
		if (!tmp_node)
		{
			del(new_content);
			ft_lstclear(&tmp_list, del);
			return (NULL);
		}
		ft_lstadd_back(&tmp_list, tmp_node);
		lst = lst->next;
	}
	return (tmp_list);
}
