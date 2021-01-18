/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdayde <tdayde@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:58:12 by tdayde            #+#    #+#             */
/*   Updated: 2020/12/07 18:40:29 by tdayde           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <assert.h>

static int	contains_linebreak(char *buff)
{
	int i;

	i = -1;
	while (buff[++i])
	{
		if (buff[i] == '\n')
			return (1);
	}
	return (0);
}

static int	end_gnl(int ret, char **save, char **line)
{
	if (ret == -1)
	{
		free(*save);
		*save = NULL;
		return (-1);
	}
	if (ret == 0)
	{
		if ((*line = gnl_strdup(*save)) == NULL)
			return (-1);
		free(*save);
		*save = NULL;
		return (0);
	}
	if ((*line = content_before_linebreak(*save, '\n')) == NULL)
		return (-1);
	if ((*save = content_after_linebreak(*save, '\n')) == NULL)
		return (-1);
	return (1);
}

static int	update_save(char **save, char **line)
{
	char *tmp;

	if ((*line = content_before_linebreak(*save, '\n')) == NULL)
		return (-1);
	if ((tmp = content_after_linebreak(*save, '\n')) == NULL)
		return (-1);
	*save = gnl_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*save[4100];
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (BUFFER_SIZE < 1 || fd < 0 || line == NULL)
		return (-1);
	if (save[fd] == NULL)
		if ((save[fd] = gnl_strdup("")) == NULL)
			return (-1);
	ret = 1;
	buff[0] = '\0';
	if (contains_linebreak(save[fd]))
		return (update_save(&(save[fd]), line));
	while (!contains_linebreak(buff) && ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret > 0)
		{
			buff[ret] = '\0';
			if ((save[fd] = gnl_strjoin(save[fd], buff)) == NULL)
				return (-1);
		}
	}
	return (end_gnl(ret, &(save[fd]), line));
}
