/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 08:49:36 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/11 12:15:56 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *ft_alloc(unsigned long size, t_pars *pars)
{
	t_list new;
	void *alloc;

	new.content = 0;
	new.next = 0;
	alloc = malloc(size);
	if (alloc == NULL)
	{
		ft_lstclear(&pars->free, free);
		printf("Error malloc\n");
		exit (0);
	}
	else 
	{
		new.content = alloc;
		ft_lstadd_back(&pars->free, &new);
		return (alloc);
	}
}