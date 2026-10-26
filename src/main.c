/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:23:58 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 12:48:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char *av[])
{
	t_scene	*scene;

	if (!check_args(ac, av))
		return (1);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (1);
	if (!read_file(scene, av[1]))
	{
		free(scene);
		return (1);
	}
	if (!init_mlx(scene))
	{
		cleanup(scene);
		return (1);
	}
	render(scene);
	init_hook(scene);
	mlx_loop(scene->mlx);
	return (0);
}
