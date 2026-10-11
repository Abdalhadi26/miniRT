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

float	ft_dot(t_vector v1, t_vector v2)
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
