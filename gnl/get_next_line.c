/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:08:24 by ahhammad          #+#    #+#             */
/*   Updated: 2026/10/27 14:03:21 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*cpye_to_nl(char *p)
{
	char	*line;
	int		len;
	int		i;

	i = 0;
	len = len_etb(p);
	if (!p[0])
		return (NULL);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = p[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	fill_buf(int fd, char *p, char **line)
{
	int		read_f;

	if (p[0])
		return (1);
	read_f = read(fd, p, BUFFER_SIZE);
	if (read_f < 0)
	{
		p[0] = '\0';
		free(*line);
		*line = NULL;
		return (0);
	}
	p[read_f] = '\0';
	return (read_f > 0);
}

static char	*add_line(char *line, char *p)
{
	if (!line)
		return (cpye_to_nl(p));
	return (ft_strjoin_gnl(line, p));
}

char	*get_next_line(int fd)
{
	static char	p[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (fill_buf(fd, p, &line))
	{
		line = add_line(line, p);
		if (!line)
			return (NULL);
		if (has_nl(p))
		{
			new_str(p);
			break ;
		}
		p[0] = '\0';
	}
	return (line);
}
