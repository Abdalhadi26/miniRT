/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 15:26:17 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/25 17:47:18 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_color get_shape_color(t_shapes_list *shape)
{
	if (shape->type == SPHERE)
		return (shape->shape.sphere.color);
	else if(shape->type == CYLINDER)
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

int	get_color(t_shapes_list *current_shape, t_scene *scene, t_vector normal, t_vector hitpoint)
{
	t_color			obj;
	t_ambient_light	amp;
	double			ambient_r;
	double			ambient_g;
	double			ambient_b;
	t_vector		hitpoint_to_light;
	t_vector		L;
	double			light_len;
	double			cos;
	t_ray			light_ray;
	double			t;
	int				useless;

	obj = get_shape_color(current_shape);
	amp = scene->ambient_light;

	ambient_r = obj.r * amp.intensity * (amp.color.r / 255.0);
	ambient_g = obj.g * amp.intensity * (amp.color.g / 255.0);
	ambient_b = obj.b * amp.intensity * (amp.color.b / 255.0);

	hitpoint_to_light = vectors_sub(2, scene->light.light_point, hitpoint);
	light_len = vector_magnitude(hitpoint_to_light);
	L = ft_scale_vector(hitpoint_to_light, 1.0 / light_len);

	cos = ft_dot(normal, L);
	if (cos <= 0)
		return (pack_color(ambient_r, ambient_g, ambient_b));

	light_ray.origin = vectors_sum(2, hitpoint, ft_scale_vector(normal, EPS));
	light_ray.direction = L;

	t = closest_hit(scene, light_ray, &useless);
	if (t < light_len)
		return (pack_color(ambient_r, ambient_g, ambient_b));

	return (pack_color(
			ambient_r + obj.r * scene->light.brightness * cos,
			ambient_g + obj.g * scene->light.brightness * cos,
			ambient_b + obj.b * scene->light.brightness * cos));
}
