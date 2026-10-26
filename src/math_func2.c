/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 14:36:34 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 14:38:08 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	vectors_sub(int n, ...)
{
	va_list		vectors;
	t_vector	v;
	t_vector	res;

	va_start(vectors, n);
	v = va_arg(vectors, t_vector);
	res = (t_vector){v.x, v.y, v.z};
	n--;
	while (n--)
	{
		v = va_arg(vectors, t_vector);
		res.x -= v.x;
		res.y -= v.y;
		res.z -= v.z;
	}
	va_end(vectors);
	return (res);
}

t_vector	get_hitpoint(t_ray camera_ray, double t)
{
	t_vector	res;
	t_vector	scaled_direction;

	scaled_direction = ft_scale_vector(camera_ray.direction, t);
	res = vectors_sum(2, camera_ray.origin, scaled_direction);
	return (res);
}

double	vector_magnitude(t_vector vec)
{
	double	magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (magnitude);
}
