/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:24:01 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 17:54:08 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	shapes_dispatcher(t_shapes_list	*lshapes, t_ray camera_ray)
{
	double	t;

	if (lshapes->type == SPHERE)
		t = get_t_sphere(&lshapes->shape, camera_ray);
	else if (lshapes->type == CYLINDER)
		t = get_t_cylinder(&lshapes->shape, camera_ray);
	else
		t = get_t_plane(&lshapes->shape, camera_ray);
	return (t);
}

// we want to get the lowest t AND the shape itself
double	closest_hit(t_scene *scene, t_ray camera_ray, int *shape_index)
{
	double			t;
	double			temp;
	int				i;
	t_shapes_list	*lshapes;

	lshapes = scene->shapes_list;
	t = INFINITY;
	temp = 0;
	i = 0;
	while (lshapes)
	{
		temp = shapes_dispatcher(lshapes, camera_ray);
		if (temp > EPS && temp < t)
		{
			t = temp;
			*shape_index = i;
		}
		lshapes = lshapes->next;
		i++;
	}
	return (t);
}
