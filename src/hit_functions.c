/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 16:24:01 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/20 17:19:04 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double get_t_sphere(t_shape *sphere, t_ray camera_ray)
{
	t_vector	C;
	t_vector	Q;
	t_vector	d;
	double		a;
	double		b;
	double		c;

	C = sphere->sphere.center;
	Q = camera_ray.origin;
	d = camera_ray.direction;
	//ax^2 + bx + c
	a = ft_dot(d,d);
	b = ft_dot(ft_scale_vector(d, -2), vectors_sub(2, C, Q));
	c = ft_dot(vectors_sub(2, C, Q), vectors_sub(2, C, Q)) - pow(sphere->sphere.diameter, 2);
	
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
			temp = get_t_sphere(&Lshapes->shape, camera_ray);
		else if(Lshapes->type == CYLINDER)
			temp = get_t_cylinder(&Lshapes->shape, camera_ray);
		else if(Lshapes->type == PLANE)
			temp = get_t_plane(&Lshapes->shape, camera_ray);
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
