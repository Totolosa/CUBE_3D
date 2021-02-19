/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 14:59:30 by tdayde            #+#    #+#             */
/*   Updated: 2021/02/18 17:01:59 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	nbr_of_words(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	**malloc_tab(char *str, char c, t_pars *pars)
{
	int		i;
	int		j;
	int		len_word;
	char	**tab;

	i = 0;
	j = 0;
	tab = ft_alloc(sizeof(char*) * (nbr_of_words(str, c) + 1), pars->free);
	while (str[i])
	{
		len_word = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			len_word++;
			i++;
		}
		if (len_word > 0)
			tab[j++] = ft_alloc(sizeof(char) * (len_word + 1), pars->free);
	}
	tab[j] = NULL;
	return (tab);
}

static char	**fill_tab(char **tab, char *str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i] && j < nbr_of_words(str, c))
	{
		k = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
			tab[j][k++] = str[i++];
		tab[j][k] = '\0';
		if (str[i] == c)
			j++;
	}
	return (tab);
}

char	**ft_split_cub(char const *s, char c, t_pars *pars)
{
	int		i;
	char	*str;
	char	**tab;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char*)s;
	tab = malloc_tab(str, c, pars);
	if (tab == NULL)
		return (NULL);
	tab = fill_tab(tab, str, c);
	return (tab);
}
