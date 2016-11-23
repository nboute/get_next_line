/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:28:00 by nboute            #+#    #+#             */
/*   Updated: 2016/11/23 13:30:52 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
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

	if (fd < 0 || !line)
		return (-1);
	if (*line)
		ft_strdel(line);
	current = ft_checkfd(&list, fd);
	if (current)
	printf("%s\n", current->data);
	if (!current->data)
		if (!(current->data = ft_read(fd)))
			return (0);
	*line = ft_strcdup(current->data, '\n');
	tmp = current->data;
	size = ft_strclen(tmp, '\n');
	while (tmp[size] == '\n')
		size++;
	current->data = ft_strsub(tmp, size + 1, ft_strlen(tmp) - size);
	free(tmp);
	return (1);
}
#include <fcntl.h>

int		main(int ac, char **av)
{
	int	fd;
	char	*str;

	fd = open(av[1], O_RDONLY);
	str = NULL;
	while (getchar() != '0')
	{
		printf("ret: %i\n", get_next_line(fd, &str));
		printf("Line: %s\n", str);
	}
}
