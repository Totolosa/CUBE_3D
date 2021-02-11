/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:49:36 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/11 17:43:54 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_alloc(unsigned long size, t_pars *pars)
{
	t_list	*new;
	void	*alloc;

	alloc = malloc(size);
	if (alloc == NULL)
	{
		ft_lstclear(&pars->free, free);
		printf("Error malloc\n");
		exit (0);
	}
	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(alloc);
		ft_lstclear(&pars->free, free);
		printf("Error malloc\n");
		exit (0);
	}
	else
	{
		new->next = NULL;
		new->content = alloc;
		ft_lstadd_back(&pars->free, new);
		return (alloc);
	}
}
