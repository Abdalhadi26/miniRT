/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 17:08:12 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 17:27:03 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	get_u_v(t_scene *scene, double *u, double *v, int px, int py)
{
	double	half_width;
	double	aspect_ratio;

	half_width = tan((scene->camera.fov * M_PI / 180) / 2);
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	*u = ((((px + 0.5) / WIDTH) * 2) - 1) * half_width;
	*v = (1 - (((py + 0.5) / HEIGHT) * 2)) * half_width / aspect_ratio;
}

static t_vector	get_direction(t_scene *scene, double u, double v)
{
	t_vector	sky;
	t_vector	forward;
	t_vector	right_raw;
	t_vector	right;
	t_vector	up;

	sky.x = 0;
	sky.y = 1;
	sky.z = 0;
	forward = scene->camera.orientation;
	right_raw = ft_cross(forward, sky);
	if (vector_magnitude(right_raw) < EPS)
	{
		sky.x = 0;
		sky.y = 0;
		sky.z = 1;
		right_raw = ft_cross(forward, sky);
	}
	right = normalize(right_raw);
	up = normalize(ft_cross(right, forward));
	right = ft_scale_vector(right, u);
	up = ft_scale_vector(up, v);
	return (normalize(vectors_sum(3, forward, right, up)));
}

t_ray	get_camera_ray(t_scene *scene, int px, int py)
{
	t_ray	camera_ray;
	double	u;
	double	v;

	u = 0;
	v = 0;
	camera_ray.origin.x = scene->camera.viewpoint.x;
	camera_ray.origin.y = scene->camera.viewpoint.y;
	camera_ray.origin.z = scene->camera.viewpoint.z;
	get_u_v(scene, &u, &v, px, py);
	camera_ray.direction = get_direction(scene, u, v);
	return (camera_ray);
}
