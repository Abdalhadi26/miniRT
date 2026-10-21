/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:31:39 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/21 17:31:06 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double get_t_plane(t_shape *plane, t_ray camera_ray)
{
	t_vector	plane_point;
	t_vector	plane_normal;
	double	t;
	double	numerator;
	double	denumerator;

	plane_point = plane->plane.point;
	plane_normal = plane->plane.normal;
	numerator = ft_dot(vectors_sub(2, plane_point, camera_ray.origin), plane_normal);
	denumerator = ft_dot(camera_ray.direction, plane_normal);
	if (denumerator == 0)
		return (-1);
	t = numerator / denumerator;
	if (t <= EPS)
		return (-1);
	return (t);
}
