/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:16:27 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/12 12:44:41 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_on_set(char c, const char *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim_cub(char const *s1, char const *set, t_pars *pars)
{
	int		i;
	int		j;
	int		len_dest;
	char	*dest;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (is_on_set(s1[i], set))
		i++;
	if (s1[i] == '\0')
		return (ft_calloc(1, 1));
	j = ft_strlen(s1) - 1;
	while (is_on_set(s1[j], set))
		j--;
	len_dest = j - i + 2;
	dest = ft_alloc(sizeof(char) * len_dest, &pars->free);
	if (dest == NULL)
		return (NULL);
	j = -1;
	while (++j < len_dest - 1)
		dest[j] = s1[i + j];
	dest[j] = '\0';
	return (dest);
}

int	free_obj(void **obj)
{
	free(*obj);
	*obj = NULL;
	return (1);
}

int	len_save(char *argv)
{
	int	len_argv;

	len_argv = ft_strlen(argv);
	if (len_argv > 6)
		return (len_argv);
	else
		return (6);
}

int	quit_prog(char *str, t_pars *pars)
{
	destroy_mlx_all_mallocs(pars);
	ft_lstclear(&pars->free, free);
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	exit (0);
	return (1);
}
