/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:58:57 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/17 15:33:16 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define ESC 65307

typedef enum s_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_shape_type;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}		t_color;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

typedef struct s_ambient_light
{
	float	intensity;
	t_color	color;
}			t_ambient_light;

typedef struct s_camera
{
	t_vector	viewpoint;
	t_vector	orientation;
	int			fov;
}				t_camera;

typedef struct s_light
{
	t_vector	light_point;
	float		brightness;
	t_color		color;
}				t_light;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_sphere
{
	t_vector		center;
	float			diameter;
	t_color			color;
}					t_sphere;

typedef struct s_plane
{
	t_vector		point;
	t_vector		facing_vector;
	t_color			color;
}					t_plane;

typedef struct s_cylinder
{
	t_vector		center;
	t_vector		facing_vector;
	float			diameter;
	float			height;
	t_color			color;
}					t_cylinder;

typedef union u_shape
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
}				t_shape;

typedef struct s_shapes_list
{
	t_shape_type			type;
	t_shape					shape;
	struct t_shapes_list	*next;
}					t_shapes_list;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_scene
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light			light;
	t_shapes_list	*shapes_list;
}		t_scene;

int	init_mlx(t_scene *scene);
int	init_img(t_scene *scene);

void	init_hook(t_scene *scene);

int		check_args(int ac, char *av[]);
void	cleanup(t_scene *scene);
void	cleanup_and_exit(t_scene *scene, int code);

void	ft_put_pixel(t_img *img, int x, int y, int color);
void	render(t_scene *scene);
#endif
