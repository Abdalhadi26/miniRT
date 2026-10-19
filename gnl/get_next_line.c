/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:08:24 by ahhammad          #+#    #+#             */
/*   Updated: 2025/10/22 17:08:24 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	has_nl(char *p)
{
	int		i;

	i = 0;
	while (p[i] != '\n' && p[i])
		i++;
	if (p[i] == '\n')
		return (true);
	return (false);
}

void	new_str(char *p)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (p[i] != '\n' && p[i] != '\0')
		i++;
	i++;
	while (p[i])
	{
		p[j] = p[i];
		i++;
		j++;
	}
	p[j] = '\0';
}

int	len_etb(char *p)
{
	int		i;

	i = 0;
	while (p[i] != '\n' && p[i] != '\0')
		i++;
	if (p[i] == '\n')
		return (i + 1);
	return (i);
}

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
	if (p[i] == '\n' && p[i] != '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}


int get_next_line(int fd, char *line)
{
	static char		p[BUFFER_SIZE + 1];
	static int		read_f;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!p[0])
		read_f = read(fd, p, BUFFER_SIZE);
	if (read_f <= 0)
		return (read_f);
	p[read_f] = '\0';
	line = cpye_to_nl(p);
	while (line != NULL)
	{
		if (has_nl(p))
			break ;
		read_f = read(fd, p, BUFFER_SIZE);
		if (read_f <= 0)
			break ;
		p[read_f] = '\0';
		line = ft_strjoin_gnl(line, p);
	}
	if(line != NULL && read_f > 0)
		new_str(p);
	return (read_f);
}
