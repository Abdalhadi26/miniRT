/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:53:42 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/05 12:39:30 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		return (0);
	scene->win = mlx_new_window(scene->mlx, WIDTH, HEIGHT,
			"miniRT");
	if (!scene->win)
	{
		cleanup(scene);
		return (0);
	}
	if (!init_img(scene))
		return (0);
	return (1);
}

int	init_img(t_scene *scene)
{
	scene->img.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->img.img)
	{
		cleanup(scene);
		return (0);
	}
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bpp,
			&scene->img.line_len, &scene->img.endian);
	if (!scene->img.addr)
	{
		cleanup(scene);
		return (0);
	}
	return (1);
}