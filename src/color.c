/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 15:26:17 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 20:16:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	get_shape_color(t_shapes_list *shape)
{
	if (shape->type == SPHERE)
		return (shape->shape.sphere.color);
	else if (shape->type == CYLINDER)
		return (shape->shape.cylinder.color);
	else
		return (shape->shape.plane.color);
}

static int	pack_color(double r, double g, double b)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (((int)r << 16) | ((int)g << 8) | (int)b);
}

static void	get_ambient(t_color obj, t_ambient_light amp, double amb[3])
{
	double	ratio;

	ratio = amp.intensity / 255.0;
	amb[0] = obj.r * (amp.color.r * ratio);
	amb[1] = obj.g * (amp.color.g * ratio);
	amb[2] = obj.b * (amp.color.b * ratio);
}

static int	is_shadowed(t_scene *scene, t_vector hit, t_vector norm,
		double *cos_val)
{
	t_vector	to_light;
	t_ray		ray;
	double		light_dist;
	double		t;
	int			dummy;

	to_light = vectors_sub(2, scene->light.light_point, hit);
	light_dist = vector_magnitude(to_light);
	ray.direction = ft_scale_vector(to_light, 1.0 / light_dist);
	*cos_val = ft_dot(norm, ray.direction);
	if (*cos_val <= 0)
		return (1);
	ray.origin = vectors_sum(2, hit, ft_scale_vector(norm, EPS));
	t = closest_hit(scene, ray, &dummy);
	return (t > EPS && t < light_dist);
}

int	get_color(t_shapes_list *current_shape, t_scene *scene, t_vector normal,
		t_vector hitpoint)
{
	t_color	obj;
	double	amb[3];
	double	cos_val;
	double	factor;

	obj = get_shape_color(current_shape);
	get_ambient(obj, scene->ambient_light, amb);
	if (is_shadowed(scene, hitpoint, normal, &cos_val))
		return (pack_color(amb[0], amb[1], amb[2]));
	factor = scene->light.brightness * cos_val;
	return (pack_color(amb[0] + obj.r * factor,
			amb[1] + obj.g * factor,
			amb[2] + obj.b * factor));
}
