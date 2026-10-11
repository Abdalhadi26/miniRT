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

#include "miniRT.h"

void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
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
			//create the ray; we calculate the ray values according to the pixel and the fov
			//find the closest hit; loop through all the object then find the closest
			//if (no hit then background black) else continue
			//if hit 
			//calculate the surface normal filp it if it is not facing the camera
			//calculate the color; if light calcuate with ambient and diffusion
			//write the color to the image and move on 
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
