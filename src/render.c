/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 22:14:23 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/05 12:37:03 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

static t_ray	get_camera_ray(t_scene scene, int px, int py)
{
	t_ray	camera_ray;
	double	half_width;
	double	aspect_ratio;

	//origin
	camera_ray.origin.x = scene.camera.viewpoint.x;
	camera_ray.origin.y = scene.camera.viewpoint.y;
	camera_ray.origin.z = scene.camera.viewpoint.z;
	//u and v
	half_width = tan((scene.camera.fov * M_PI / 180) / 2);
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	double u = ((((px + 0.5) / WIDTH) * 2) - 1) * half_width;
	double v = (1 - (((py + 0.5) / HEIGHT) * 2)) * half_width / aspect_ratio;
	//the real directions, forward right and up
	t_vector sky;
	sky.x = 0;
	sky.y = 1;
	sky.z = 0;
	t_vector forward = scene.camera.orientation;
	t_vector right = normalize(ft_cross(forward, sky));
	t_vector up = normalize(ft_cross(right, forward));
	right = ft_scale_vector(right, u);
	up = ft_scale_vector(up, v);
	//final ray
	camera_ray.direction = normalize(vecotrs_sum(forward, right, up));
	return (camera_ray);
}

//we want to get the lowest t AND the shape itself
double closest_hit(t_scene scene,t_ray camera_ray, int *shape_index)
{
	double t;
	double temp;
	int		i;

	t = INFINITY;
	temp = 0;
	i = 0;
	while (scene.shapes_list)
	{
		if (scene.shapes_list->type == SPHERE)
			temp = get_t_sphere(scene.shapes_list, camera_ray);
		else if(scene.shapes_list->type == CYLINDER)
			temp = get_t_cylinder(scene.shapes_list, camera_ray);
		else if(scene.shapes_list->type == PLANE)
			temp = get_t_plane(scene.shapes_list, camera_ray);
		if (temp < t)
		{
			t = temp;
			*shape_index = i;
		}
		i++;
		scene.shapes_list = scene.shapes_list->next;
	}
	return (t);
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
			t_ray camera_ray = get_camera_ray(*scene, x, y);
			//PART 2
			//find the closest hit; loop through all the object then find the closest
			int		shape_index;
			double t = closest_hit(*scene, camera_ray, &shape_index);
			//PART 3
			//if (no hit then background black) else continue
			if (t <= EPS);
				//it is blaaaAACK
			//calculate the surface normal filp it if it is not facing the camera
			
			//calculate the color; if light calcuate with ambient and diffusion
			
			//write the color to the image and move on 
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
