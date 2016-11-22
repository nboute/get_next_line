/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:28:00 by nboute            #+#    #+#             */
/*   Updated: 2016/11/22 20:45:05 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_read(int fd)
{
	char			buff[BUFF_SIZE + 1];
	char			*str;
	int				ret;

	str = (char*)malloc(BUFF_SIZE + 1);
	ret = read(fd, buff, BUFF_SIZE);
	buff[ret] = '\0';
	if (ret <= 0)
		return (NULL);
	ft_strcpy(str, buff);
	return (str);
}

t_line				*ft_checkfd(t_line **list, int fd)
{
	t_line			*tmp;

	if (!*list)
	{
		*list = (t_line*)malloc(sizeof(t_line));
		(*list)->fd = fd;
		(*list)->next = NULL;
		(*list)->data = NULL;
	}
	tmp = *list;
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd != fd)
	{
		tmp->next = (t_line*)malloc(sizeof(t_line));
		tmp = tmp->next;
		tmp->fd = fd;
		tmp->next = NULL;
		tmp->data = NULL;
	}
	return (tmp);
}

int					ft_readmore(t_line *current, char *tmp, char **line)
{
	char			*tmp2;

	if ((tmp = ft_read(current->fd)))
	{
		while (tmp)
		{
			tmp2 = ft_strjoin(current->data, tmp);
			free(current->data);
			free(tmp);
			current->data = tmp2;
			tmp = ft_read(current->fd);
		}
		return (1);
	}
	current->data = NULL;
	*line = NULL;
	return (0);
}

int					get_next_line(const int fd, char **line)
{
	static t_line	*list = NULL;
	char			*tmp;
	t_line			*current;

	if (fd < 0 || !line)
		return (-1);
	current = ft_checkfd(&list, fd);
	tmp = NULL;
	if (!current->data || !ft_strchr(current->data, '\n'))
		if (!ft_readmore(current, tmp, line))
			return (0);
	if (*line)
		free(*line);
	*line = ft_strcdup(current->data, '\n');
	while (*current->data != '\n')
		current->data++;
	current->data += (*current->data == '\n') ? 1 : 0;
	return (1);
}
