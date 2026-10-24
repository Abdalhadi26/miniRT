/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:46:05 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/24 14:04:18 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector get_normal_sphere(t_shape sphere, t_vector hit_point)
{
	t_vector	n;
	t_vector	C;
	double		r;

	C = sphere.sphere.center;
	r = sphere.sphere.diameter / 2;

	n = ft_scale_vector(vectors_sub(2, hit_point, C), (1 / r));

	return (n);
}

t_vector get_normal_cylinder(t_shape cylinder, t_vector hit_point)
{
	t_vector	n;
	t_vector	V;
	t_vector	V_perp;
	t_vector	A;
	double		r;
	double		h;

	A = cylinder.cylinder.axis;
	r = cylinder.cylinder.diameter / 2;
	V = vectors_sub(2, hit_point, cylinder.cylinder.center);
	h = ft_dot(V, A);
	if (fabs(h) < (cylinder.cylinder.height / 2 - EPS))
	{
		V_perp = vectors_sub(2, V, ft_scale_vector(A, h));
		n = ft_scale_vector(V_perp, (1 / r));
		return (n);
	}
	else if (h > 0)
		return (A);
	else
		return(ft_scale_vector(A, -1));
}

t_vector get_normal(t_shapes_list *current_shape, t_ray camera_ray, t_vector hitpoint)
{
	t_vector	normal;
	t_vector	d;
	
	d = camera_ray.direction;
	if (current_shape->type == SPHERE)
		normal = get_normal_sphere(current_shape->shape, hitpoint);
	else if(current_shape->type == CYLINDER)
		normal = get_normal_cylinder(current_shape->shape, hitpoint);
	else if(current_shape->type == PLANE)
		normal = current_shape->shape.plane.normal;
	if (ft_dot(normal, d) > 0)
		normal = ft_scale_vector(normal, -1);

	return (normal);
}
