/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:23:58 by aayasrah          #+#    #+#             */
/*   Updated: 2026/06/30 20:23:58 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char *av[])
{
	t_scene	*scene;

	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene.rt>\n", 1);
		return (0);
	}
	//parse
	if (!init_mlx(scene))
		return (1);
	//render(scene);
	init_hook(scene);
	mlx_loop(scene->mlx);
	return (0);
}