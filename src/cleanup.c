/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 21:13:45 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 12:47:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cleanup(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->shapes_list)
		free_shapes_list(scene->shapes_list);
	if (scene->img.img)
		mlx_destroy_image(scene->mlx, scene->img.img);
	if (scene->win)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->mlx)
	{
		mlx_destroy_display(scene->mlx);
		free(scene->mlx);
	}
	free(scene);
}

void	cleanup_and_exit(t_scene *scene, int code)
{
	cleanup(scene);
	exit(code);
}
