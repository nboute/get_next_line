/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 13:46:57 by nboute            #+#    #+#             */
/*   Updated: 2016/11/26 17:09:38 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# define BUFF_SIZE 1

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct		s_line
{
	char			*data;
	int				fd;
	struct s_line	*next;
}					t_line;

int					get_next_line(const int fd, char **line);
t_line				*ft_checkfd(t_line **list, int fd);
char				*ft_read(int fd);

#endif
