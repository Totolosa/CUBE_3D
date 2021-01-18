/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:57:10 by tdayde            #+#    #+#             */
/*   Updated: 2020/12/02 14:35:37 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char		**free_mem(char **tab, int k)
{
	while (k >= 0)
		free(tab[k--]);
	free(tab);
	return (NULL);
}

static int		nbr_of_words(char *str, char c)
{
	int i;
	int count;

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

static char		**malloc_tab(char *str, char c)
{
	int		i;
	int		j;
	int		len_word;
	char	**tab;

	i = 0;
	j = 0;
	if ((tab = malloc(sizeof(char*) * nbr_of_words(str, c) + 1)) == NULL)
		return (NULL);
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
			if ((tab[j++] = malloc(sizeof(char) * (len_word + 1))) == NULL)
				return (free_mem(tab, j - 1));
	}
	tab[j] = NULL;
	return (tab);
}

static char		**fill_tab(char **tab, char *str, char c)
{
	int	i;
	int	j;
	int k;

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

char			**ft_split(char const *s, char c)
{
	int		i;
	char	*str;
	char	**tab;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char*)s;
	if ((tab = malloc_tab(str, c)) == NULL)
		return (NULL);
	tab = fill_tab(tab, str, c);
	return (tab);
}
