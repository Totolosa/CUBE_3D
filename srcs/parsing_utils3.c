/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:02:28 by tdayde            #+#    #+#             */
/*   Updated: 2021/03/18 17:48:58 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_atoi_cub(const char *str)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = 10 * result + (str[i] - '0');
		if (result > INT_MAX)
			result = INT_MAX;
		i++;
	}
	result *= sign;
	return (result);
}

int	assign_text(char **path, char *trim, char *line, t_pars *pars)
{
	*path = ft_strtrim_cub(line, trim, pars);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		pars->declaration.no++;
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		pars->declaration.so++;
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		pars->declaration.we++;
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		pars->declaration.ea++;
	else if (line[0] == 'S' && line[1] == ' ')
		pars->declaration.spr++;
	return (1);
}

int	check_declaration(t_pars *pars)
{
	if (pars->declaration.res != 1)
		quit_prog("Resolution definition issue\n", pars);
	if (pars->declaration.no != 1)
		quit_prog("North texture definition issue\n", pars);
	if (pars->declaration.so != 1)
		quit_prog("South texture definition issue\n", pars);
	if (pars->declaration.we != 1)
		quit_prog("West texture definition issue\n", pars);
	if (pars->declaration.ea != 1)
		quit_prog("East texture definition issue\n", pars);
	if (pars->declaration.spr != 1)
		quit_prog("Sprite texture definition issue\n", pars);
	if (pars->declaration.sky != 1)
		quit_prog("Sky definition issue\n", pars);
	if (pars->declaration.floor != 1)
		quit_prog("Floor definition issue\n", pars);
	return (1);
}
