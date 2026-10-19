/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:46:05 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/19 13:59:19 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector get_normal_sphere(t_shape shape, t_vector hit_point)
{
	
}

t_vector get_normal_cylinder(t_shape shape, t_vector hit_point)
{
	
}

t_vector get_normal_plane(t_shape shape, t_vector hit_point)
{
	
}

t_vector get_normal(t_shapes_list *current_shape, t_ray camera_ray, t_vector hitpoint)
{
	t_vector normal;

	
	if (current_shape->type == SPHERE)
		normal = get_normal_sphere(current_shape->shape, hitpoint);
	else if(current_shape->type == CYLINDER)
		normal = get_normal_cylinder(current_shape->shape, hitpoint);
	else if(current_shape->type == PLANE)
		normal = get_normal_plane(current_shape->shape, hitpoint);


	return (normal);
}
