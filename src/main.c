/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:23:58 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/18 14:36:37 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


int	main(int ac, char *av[])
{
	t_scene	*scene;
	int fd;
	char *data;
	int i;
	
	
	
	if (!check_args(ac, av))
		return (0);
	//------------temp code------------------------
		scene = ft_calloc(1, sizeof(t_scene));
		if (!scene)
			return (0);
	//---------------------------------------------
	//parse
	//set_scene(scene);// here i will call the function that will parse the scene file and set the scene struct
	if (!init_mlx(scene))
		return (1);
	render(scene);
	init_hook(scene);
	mlx_loop(scene->mlx);
	
	return (0);
}
