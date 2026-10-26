/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 14:45:34 by ahhammad          #+#    #+#             */
/*   Updated: 2026/10/26 12:47:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_line(t_scene *scene, char *line, int *flags)
{
	char	**tokens;
	int		res;

	replace_whitespace(line);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	if (!tokens[0])
		return (free_split(tokens), 1);
	res = 0;
	if (!ft_strncmp(tokens[0], "A", 2))
		res = parse_ambient(scene, tokens, flags);
	else if (!ft_strncmp(tokens[0], "C", 2))
		res = parse_camera(scene, tokens, flags);
	else if (!ft_strncmp(tokens[0], "L", 2))
		res = parse_light(scene, tokens, flags);
	else if (!ft_strncmp(tokens[0], "sp", 3))
		res = parse_sphere(scene, tokens);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		res = parse_plane(scene, tokens);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		res = parse_cylinder(scene, tokens);
	else
		ft_putstr_fd("Error\nUnknown identifier in scene file\n", 2);
	free_split(tokens);
	return (res);
}

static void	drain_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	read_file(t_scene *scene, char *file_name)
{
	int		fd;
	int		flags;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error\nCannot open scene file\n", 2), 0);
	flags = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(scene, line, &flags))
		{
			free(line);
			drain_gnl(fd);
			close(fd);
			return (free_shapes_list(scene->shapes_list), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (flags != (FLAG_A | FLAG_C | FLAG_L))
		return (ft_putstr_fd("Error\nMissing required element\n", 2),
			free_shapes_list(scene->shapes_list), 0);
	return (1);
}
