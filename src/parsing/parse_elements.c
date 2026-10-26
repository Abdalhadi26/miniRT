/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:45:00 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 12:45:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_ambient(t_scene *scene, char **tokens, int *flags)
{
	if (*flags & FLAG_A)
		return (ft_putstr_fd("Error\nDuplicate ambient light (A)\n", 2), 0);
	if (split_len(tokens) != 3)
		return (ft_putstr_fd("Error\nInvalid format for A\n", 2), 0);
	if (!ft_atod(tokens[1], &scene->ambient_light.intensity))
		return (ft_putstr_fd("Error\nInvalid ratio for A\n", 2), 0);
	if (scene->ambient_light.intensity < 0.0
		|| scene->ambient_light.intensity > 1.0)
		return (ft_putstr_fd("Error\nRatio for A out of range [0, 1]\n", 2), 0);
	if (!parse_color(tokens[2], &scene->ambient_light.color))
		return (ft_putstr_fd("Error\nInvalid color for A\n", 2), 0);
	*flags |= FLAG_A;
	return (1);
}

int	parse_camera(t_scene *scene, char **tokens, int *flags)
{
	if (*flags & FLAG_C)
		return (ft_putstr_fd("Error\nDuplicate camera (C)\n", 2), 0);
	if (split_len(tokens) != 4)
		return (ft_putstr_fd("Error\nInvalid format for C\n", 2), 0);
	if (!parse_vector(tokens[1], &scene->camera.viewpoint))
		return (ft_putstr_fd("Error\nInvalid viewpoint for C\n", 2), 0);
	if (!parse_norm_vector(tokens[2], &scene->camera.orientation))
		return (ft_putstr_fd("Error\nInvalid orientation for C\n", 2), 0);
	if (!is_all_digits(tokens[3]))
		return (ft_putstr_fd("Error\nInvalid FOV for C\n", 2), 0);
	scene->camera.fov = ft_atoi(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		return (ft_putstr_fd("Error\nFOV out of range [0, 180]\n", 2), 0);
	*flags |= FLAG_C;
	return (1);
}

int	parse_light(t_scene *scene, char **tokens, int *flags)
{
	if (*flags & FLAG_L)
		return (ft_putstr_fd("Error\nDuplicate light (L)\n", 2), 0);
	if (split_len(tokens) != 4)
		return (ft_putstr_fd("Error\nInvalid format for L\n", 2), 0);
	if (!parse_vector(tokens[1], &scene->light.light_point))
		return (ft_putstr_fd("Error\nInvalid light point for L\n", 2), 0);
	if (!ft_atod(tokens[2], &scene->light.brightness))
		return (ft_putstr_fd("Error\nInvalid brightness for L\n", 2), 0);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		return (ft_putstr_fd("Error\nBrightness out of range [0, 1]\n", 2), 0);
	if (!parse_color(tokens[3], &scene->light.color))
		return (ft_putstr_fd("Error\nInvalid color for L\n", 2), 0);
	*flags |= FLAG_L;
	return (1);
}
