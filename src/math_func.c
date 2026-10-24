/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 12:06:20 by aayasrah            #+#    #+#             */
/*   Updated: 2026/10/11 12:06:20 by aayasrah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	ft_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector ft_cross(t_vector v1, t_vector v2)
{
	t_vector res;
	res.x = v1.y * v2.z - v2.y * v1.z;
    res.y = v2.x * v1.z - v1.x * v2.z;
    res.z = v1.x * v2.y - v2.x * v1.y;

	return (res);
}

t_vector ft_scale_vector(t_vector v, double scale)
{
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;

	return (v);
}

t_vector vectors_sum(int n, ...)
{
	va_list		vectors;
	t_vector	v;
	t_vector	res;

	res = (t_vector){0,0,0};
	va_start(vectors, n);
	while (n--)
	{
		v = va_arg(vectors, t_vector);
		res.x += v.x;
		res.y += v.y;
		res.z += v.z;
	}
	va_end(vectors);
	return (res);
}

t_vector normalize(t_vector vec)
{
	t_vector	res;
	double		magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (magnitude == 0)
	{
		res.x = 0;
		res.y = 0;
		res.z = 0;
		return (res);
	}	
	res.x = vec.x / magnitude;
	res.y = vec.y / magnitude;
	res.z = vec.z / magnitude;
	return (res);
}

t_vector vectors_sub(int n, ...)
{
	va_list		vectors;
	t_vector	v;
	t_vector	res;

	va_start(vectors, n);
	v = va_arg(vectors, t_vector);
	res = (t_vector){v.x,v.y,v.z};
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

t_vector get_hitpoint(t_ray camera_ray,double t)
{
	t_vector	res;
	t_vector	scaled_direction;

	scaled_direction = ft_scale_vector(camera_ray.direction, t);
	res = vectors_sum(2, camera_ray.origin, scaled_direction);
	return (res);
}

double vector_magnitude(t_vector vec)
{
	t_vector	res;
	double		magnitude;

	magnitude = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (magnitude);
}