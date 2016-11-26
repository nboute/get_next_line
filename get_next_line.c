/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:28:00 by nboute            #+#    #+#             */
/*   Updated: 2016/11/26 17:50:26 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_read(int fd)
{
	char			buff[BUFF_SIZE + 1];
	char			*tmp;
	char			*str;
	int				ret;
	int				size;

	str = NULL;
	size = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		tmp = ft_strjoin(str, buff);
		if (str)
			free(str);
		str = tmp;
	}
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

int					get_next_line(const int fd, char **line)
{
	static t_line	*list = NULL;
	t_line			*current;
	char			*tmp;
	size_t			size;

	if (fd < 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	ft_strdel(line);
	current = ft_checkfd(&list, fd);
	if (!current->data)
		if (!(current->data = ft_read(fd)))
			return (0);
	if (!*(current->data))
		return (0);
	*line = ft_strcdup(current->data, '\n');
	tmp = current->data;
	size = ft_strclen(tmp, '\n');
	if (tmp[size] == '\n')
		size++;
	current->data = ft_strsub(tmp, size, ft_strlen(tmp) - size);
	if (tmp)
		free(tmp);
	return (1);
}
