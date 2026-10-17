/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:23:58 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/05 15:51:20 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int ac, char *av[])
{
	t_scene	*scene;

	if (!check_args(ac, av))
		return (0);
	//parse
	//------------temp code------------------------
		scene = ft_calloc(1, sizeof(t_scene));
		if (!scene)
			return (0);
	//---------------------------------------------
	if (!init_mlx(scene))
		return (1);
	render(scene);
	init_hook(scene);
	mlx_loop(scene->mlx);
	return (0);
}
