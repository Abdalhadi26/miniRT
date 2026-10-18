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

t_vector vecotrs_sum(t_vector forward, t_vector right, t_vector up)
{
	t_vector	res;

	res.x = forward.x + right.x + up.x;
	res.y = forward.y + right.y + up.y;
	res.z = forward.z + right.z + up.z;
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
