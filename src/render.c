/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 22:14:23 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 17:21:30 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

t_shapes_list	*get_current_shaped(t_shapes_list *shapes_list, int shape_index)
{
	while (shape_index > 0)
	{
		shapes_list = shapes_list->next;
		shape_index--;
	}
	return (shapes_list);
}

int	pixel_color(t_scene *scene, t_ray camera_ray)
{
	int				shape_index;
	t_shapes_list	*current_shape;
	t_vector		hitpoint;
	t_vector		normal;
	double			t;

	t = closest_hit(scene, camera_ray, &shape_index);
	if (t <= EPS || t == INFINITY)
		return (0);
	current_shape = get_current_shaped(scene->shapes_list, shape_index);
	hitpoint = get_hitpoint(camera_ray, t);
	normal = get_normal(current_shape, camera_ray, hitpoint);
	return (get_color(current_shape, scene, normal, hitpoint));
}

void	render(t_scene *scene)
{
	int		x;
	int		y;
	int		color;
	t_ray	camera_ray;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			camera_ray = get_camera_ray(scene, x, y);
			color = pixel_color(scene, camera_ray);
			ft_put_pixel(&scene->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
