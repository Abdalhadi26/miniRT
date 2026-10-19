/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:24:01 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/19 14:39:03 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double get_t_sphere(t_shapes_list *sphere, t_ray camera_ray)
{

}

double get_t_cylinder(t_shapes_list *cylinder, t_ray camera_ray)
{
	
}

double get_t_sphere(t_shapes_list *sphere, t_ray camera_ray)
{
	
}

//we want to get the lowest t AND the shape itself
double closest_hit(t_scene *scene,t_ray camera_ray, int *shape_index)
{
	double t;
	double temp;
	int		i;
	t_shapes_list *Lshapes;

	Lshapes = scene->shapes_list;
	t = INFINITY;
	temp = 0;
	i = 0;
	while (Lshapes)
	{
		if (Lshapes->type == SPHERE)
			temp = get_t_sphere(Lshapes, camera_ray);
		else if(Lshapes->type == CYLINDER)
			temp = get_t_cylinder(Lshapes, camera_ray);
		else if(Lshapes->type == PLANE)
			temp = get_t_plane(Lshapes, camera_ray);
		if (temp < t)
		{
			t = temp;
			*shape_index = i;
		}
		Lshapes = Lshapes->next;
		i++;
	}
	return (t);
}
