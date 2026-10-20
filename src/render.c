/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 22:14:23 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/20 17:15:46 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

static t_ray	get_camera_ray(t_scene *scene, int px, int py)
{
	t_ray	camera_ray;
	double	half_width;
	double	aspect_ratio;

	//origin
	camera_ray.origin.x = scene->camera.viewpoint.x;
	camera_ray.origin.y = scene->camera.viewpoint.y;
	camera_ray.origin.z = scene->camera.viewpoint.z;
	//u and v
	half_width = tan((scene->camera.fov * M_PI / 180) / 2);
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	double u = ((((px + 0.5) / WIDTH) * 2) - 1) * half_width;
	double v = (1 - (((py + 0.5) / HEIGHT) * 2)) * half_width / aspect_ratio;
	//the real directions, forward right and up
	t_vector sky;
	sky.x = 0;
	sky.y = 1;
	sky.z = 0;
	t_vector forward = scene->camera.orientation;
	t_vector right = normalize(ft_cross(forward, sky));
	t_vector up = normalize(ft_cross(right, forward));
	right = ft_scale_vector(right, u);
	up = ft_scale_vector(up, v);
	//final ray
	camera_ray.direction = normalize(vectors_sum(3, forward, right, up));
	return (camera_ray);
}

t_shapes_list *get_current_shaped(t_shapes_list *shapes_list,int shape_index)
{
	while (shape_index >= 0)
		shapes_list = shapes_list->next;
	return (shapes_list);
}

int get_color(t_shapes_list *current_shape, t_scene *scene, t_vector normal, t_vector thipoint)
{

}

t_vector get_hitpoint(t_ray camera_ray,double t)
{

}

void	render(t_scene *scene)
{
	int			x;
	int			y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			//ray tracing logic
			//PART 1
			//create the ray; we calculate the ray values according to the pixel and the fov
			t_ray camera_ray = get_camera_ray(scene, x, y);
			//PART 2
			//find the closest hit; loop through all the object then find the closest
			int		shape_index;
			double t = closest_hit(scene, camera_ray, &shape_index);
			//PART 3
			//if (no hit then background black) else continue
			int color;
			if (t <= EPS || t == INFINITY)
			{
				color = 0;
				ft_put_pixel(&scene->img, x++, y, color);
				continue;
			}
			t_shapes_list *current_shape;
			current_shape = get_current_shaped(scene->shapes_list, shape_index);
			t_vector hitpoint = get_hitpoint(camera_ray, t);
			//calculate the surface normal filp it if it is not facing the camera
			t_vector normal;
			normal = get_normal(current_shape, camera_ray, hitpoint);
			//calculate the color; if light calcuate with ambient and diffusion
			color = get_color(current_shape, scene, normal, hitpoint);
			//write the color to the image and move on
			ft_put_pixel(&scene->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
