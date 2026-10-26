/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:45:00 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 12:45:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	add_shape_node(t_shapes_list **list, t_shape_type type, t_shape shape)
{
	t_shapes_list	*node;
	t_shapes_list	*curr;

	node = ft_calloc(1, sizeof(t_shapes_list));
	if (!node)
		return (0);
	node->type = type;
	node->shape = shape;
	if (!*list)
		*list = node;
	else
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
	return (1);
}

int	parse_sphere(t_scene *scene, char **tokens)
{
	t_shape	shape;

	if (split_len(tokens) != 4)
		return (ft_putstr_fd("Error\nInvalid format for sp\n", 2), 0);
	if (!parse_vector(tokens[1], &shape.sphere.center))
		return (ft_putstr_fd("Error\nInvalid center for sp\n", 2), 0);
	if (!ft_atod(tokens[2], &shape.sphere.diameter)
		|| shape.sphere.diameter <= 0.0)
		return (ft_putstr_fd("Error\nInvalid diameter for sp\n", 2), 0);
	if (!parse_color(tokens[3], &shape.sphere.color))
		return (ft_putstr_fd("Error\nInvalid color for sp\n", 2), 0);
	if (!add_shape_node(&scene->shapes_list, SPHERE, shape))
		return (ft_putstr_fd("Error\nMalloc failed for sp\n", 2), 0);
	return (1);
}

int	parse_plane(t_scene *scene, char **tokens)
{
	t_shape	shape;

	if (split_len(tokens) != 4)
		return (ft_putstr_fd("Error\nInvalid format for pl\n", 2), 0);
	if (!parse_vector(tokens[1], &shape.plane.point))
		return (ft_putstr_fd("Error\nInvalid point for pl\n", 2), 0);
	if (!parse_norm_vector(tokens[2], &shape.plane.normal))
		return (ft_putstr_fd("Error\nInvalid normal for pl\n", 2), 0);
	if (!parse_color(tokens[3], &shape.plane.color))
		return (ft_putstr_fd("Error\nInvalid color for pl\n", 2), 0);
	if (!add_shape_node(&scene->shapes_list, PLANE, shape))
		return (ft_putstr_fd("Error\nMalloc failed for pl\n", 2), 0);
	return (1);
}

int	parse_cylinder(t_scene *scene, char **tokens)
{
	t_shape	shape;

	if (split_len(tokens) != 6)
		return (ft_putstr_fd("Error\nInvalid format for cy\n", 2), 0);
	if (!parse_vector(tokens[1], &shape.cylinder.center))
		return (ft_putstr_fd("Error\nInvalid center for cy\n", 2), 0);
	if (!parse_norm_vector(tokens[2], &shape.cylinder.axis))
		return (ft_putstr_fd("Error\nInvalid axis for cy\n", 2), 0);
	if (!ft_atod(tokens[3], &shape.cylinder.diameter)
		|| shape.cylinder.diameter <= 0.0)
		return (ft_putstr_fd("Error\nInvalid diameter for cy\n", 2), 0);
	if (!ft_atod(tokens[4], &shape.cylinder.height)
		|| shape.cylinder.height <= 0.0)
		return (ft_putstr_fd("Error\nInvalid height for cy\n", 2), 0);
	if (!parse_color(tokens[5], &shape.cylinder.color))
		return (ft_putstr_fd("Error\nInvalid color for cy\n", 2), 0);
	if (!add_shape_node(&scene->shapes_list, CYLINDER, shape))
		return (ft_putstr_fd("Error\nMalloc failed for cy\n", 2), 0);
	return (1);
}
