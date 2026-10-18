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
     #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int	main(int ac, char *av[])
{
	t_scene	*scene;
	int fd;
	char *data;
	int i;
	
	fd = open(".rt", O_RDONLY);
	data = malloc(10);
	i = read(fd,data, 10); //There are two choices: I can use read() to read the entire file and then split it, or I can use GNL and store the return values in a double pointer.
	if (i < 1) // exit
		printf("hello\n");
	data[i]= '\0';
	printf("hi i%c %d\n", data[i - 1], i);
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
