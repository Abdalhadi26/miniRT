/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 20:23:58 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/25 20:20:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	add_shape(t_shapes_list **list, t_shape_type type, t_shape shape)
{
	t_shapes_list	*node;

	node = ft_calloc(1, sizeof(t_shapes_list));
	if (!node)
		return ;
	node->type = type;
	node->shape = shape;
	node->next = *list;
	*list = node;
}

static void	setup_static_scene(t_scene *scene)
{
	t_shape	shape;

	// Ambient Light (subtle ambient base)
	scene->ambient_light.intensity = 0.2;
	scene->ambient_light.color = (t_color){255, 255, 255};

	// Camera: pos (0, 0, 0), facing forward (0, 0, 1), FOV 70
	scene->camera.viewpoint = (t_vector){0, 0, 0};
	scene->camera.orientation = normalize((t_vector){0, 0, 1});
	scene->camera.fov = 70;

	// Light: placed to the top-left (-10, 10, 5), brightness 0.8
	scene->light.light_point = (t_vector){-10, 10, 5};
	scene->light.brightness = 0.8;
	scene->light.color = (t_color){255, 255, 255};

	// Single Red Sphere directly in front of camera
	shape.sphere.center = (t_vector){0, 0, 20};
	shape.sphere.diameter = 10;
	shape.sphere.color = (t_color){255, 40, 40};
	add_shape(&scene->shapes_list, SPHERE, shape);

	/* Optional: Uncomment to test plane or cylinder when ready
	// Floor Plane:
	shape.plane.point = (t_vector){0, -6, 0};
	shape.plane.normal = normalize((t_vector){0, 1, 0});
	shape.plane.color = (t_color){180, 180, 180};
	add_shape(&scene->shapes_list, PLANE, shape);

	// Cylinder:
	shape.cylinder.center = (t_vector){7, 0, 20};
	shape.cylinder.axis = normalize((t_vector){0, 1, 0});
	shape.cylinder.diameter = 8;
	shape.cylinder.height = 12;
	shape.cylinder.color = (t_color){50, 100, 255};
	add_shape(&scene->shapes_list, CYLINDER, shape);
	*/
}

int	main(int ac, char *av[])
{
	t_scene	*scene;

	(void)ac;
	(void)av;
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (1);
	setup_static_scene(scene);
	if (!init_mlx(scene))
		return (1);
	render(scene);
	init_hook(scene);
	mlx_loop(scene->mlx);
	return (0);
}

/*
Original main function (commented out until parser is ready):

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
*/
