/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 21:23:41 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/30 21:23:41 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	handle_key(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == ESC)
		cleanup_and_exit(scene, 0);
	return (0);
}

int	handle_close(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	cleanup_and_exit(scene, 0);
	return (0);
}

void	init_hook(t_scene *scene)
{
	mlx_key_hook(scene->win, handle_key, scene);
	mlx_hook(scene->win, 17, 0, handle_close, scene);
}
