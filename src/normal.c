/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:46:05 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 16:49:42 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	get_normal_sphere(t_shape sphere, t_vector hit_point)
{
	t_vector	n;
	t_vector	center;
	double		r;

	center = sphere.sphere.center;
	r = sphere.sphere.diameter / 2;
	n = ft_scale_vector(vectors_sub(2, hit_point, center), (1 / r));
	return (n);
}

t_vector	get_normal_cylinder(t_shape cylinder, t_vector hit_point)
{
	t_vector	n;
	t_vector	v;
	t_vector	v_perp;
	double		r;
	double		h;

	r = cylinder.cylinder.diameter / 2;
	v = vectors_sub(2, hit_point, cylinder.cylinder.center);
	h = ft_dot(v, cylinder.cylinder.axis);
	if (fabs(h) < (cylinder.cylinder.height / 2 - EPS))
	{
		v_perp = vectors_sub(2, v, ft_scale_vector(cylinder.cylinder.axis, h));
		n = ft_scale_vector(v_perp, (1 / r));
		return (n);
	}
	else if (h > 0)
		return (cylinder.cylinder.axis);
	else
		return (ft_scale_vector(cylinder.cylinder.axis, -1));
}

t_vector	get_normal(t_shapes_list *current_shape, t_ray camera_ray,
		t_vector hitpoint)
{
	t_vector	normal;
	t_vector	d;

	d = camera_ray.direction;
	if (current_shape->type == SPHERE)
		normal = get_normal_sphere(current_shape->shape, hitpoint);
	else if (current_shape->type == CYLINDER)
		normal = get_normal_cylinder(current_shape->shape, hitpoint);
	else
		normal = current_shape->shape.plane.normal;
	if (ft_dot(normal, d) > 0)
		normal = ft_scale_vector(normal, -1);
	return (normal);
}
