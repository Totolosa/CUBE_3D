/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 13:56:59 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/15 14:04:05 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_alloc(unsigned long size, t_list *lst)
{
	t_list	*new;
	void	*alloc;

	alloc = malloc(size);
	if (alloc == NULL)
	{
		ft_lstclear(&lst, free);
		write(1, "Error malloc\n", 13);
		exit (0);
	}
	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(alloc);
		ft_lstclear(&lst, free);
		write(1, "Error malloc\n", 13);
		exit (0);
	}
	else
	{
		new->next = NULL;
		new->content = alloc;
		ft_lstadd_back(&lst, new);
		return (alloc);
	}
}
