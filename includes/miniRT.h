/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:58:57 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/27 15:32:31 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <sys/types.h>

# define WIDTH 800
# define HEIGHT 600
# define ESC 65307
# define EPS 0.000001
# define FLAG_A 1
# define FLAG_C 2
# define FLAG_L 4
# ifndef M_PI
#  define M_PI 3.1415926535
# endif

typedef enum s_shape_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}							t_shape_type;

typedef struct s_color
{
	int						r;
	int						g;
	int						b;
}							t_color;

typedef struct s_vector
{
	double					x;
	double					y;
	double					z;
}							t_vector;

typedef struct s_ambient_light
{
	double					intensity;
	t_color					color;
}							t_ambient_light;

typedef struct s_camera
{
	t_vector				viewpoint;
	t_vector				orientation;
	int						fov;
}							t_camera;

typedef struct s_light
{
	t_vector				light_point;
	double					brightness;
	t_color					color;
}							t_light;

typedef struct s_ray
{
	t_vector				origin;
	t_vector				direction;
}							t_ray;

typedef struct s_sphere
{
	t_vector				center;
	double					diameter;
	t_color					color;
}							t_sphere;

typedef struct s_plane
{
	t_vector				point;
	t_vector				normal;
	t_color					color;
}							t_plane;

typedef struct s_cylinder
{
	t_vector				center;
	t_vector				axis;
	double					diameter;
	double					height;
	t_color					color;
}							t_cylinder;

typedef union u_shape
{
	t_sphere				sphere;
	t_plane					plane;
	t_cylinder				cylinder;
}							t_shape;

typedef struct s_shapes_list
{
	t_shape_type			type;
	t_shape					shape;
	struct s_shapes_list	*next;
}							t_shapes_list;

typedef struct s_img
{
	void					*img;
	char					*addr;
	int						bpp;
	int						line_len;
	int						endian;
}							t_img;

typedef struct s_scene
{
	void					*mlx;
	void					*win;
	t_img					img;
	t_ambient_light			ambient_light;
	t_camera				camera;
	t_light					light;
	t_shapes_list			*shapes_list;
}							t_scene;

int			init_mlx(t_scene *scene);
int			init_img(t_scene *scene);

void		init_hook(t_scene *scene);

int			check_args(int ac, char *av[]);
int			read_file(t_scene *scene, char *file_name);
int			ft_atod(const char *s, double *out);
void		free_split(char **arr);
int			split_len(char **arr);
int			count_char(const char *s, char c);
void		replace_whitespace(char *str);
void		free_shapes_list(t_shapes_list *list);
int			is_all_digits(char *str);
int			parse_color(char *str, t_color *color);
int			parse_vector(char *str, t_vector *vec);
int			parse_norm_vector(char *str, t_vector *vec);
int			parse_ambient(t_scene *scene, char **tokens,
				int *flags);
int			parse_camera(t_scene *scene, char **tokens,
				int *flags);
int			parse_light(t_scene *scene, char **tokens,
				int *flags);
int			add_shape_node(t_shapes_list **list,
				t_shape_type type, t_shape shape);
int			parse_sphere(t_scene *scene, char **tokens);
int			parse_plane(t_scene *scene, char **tokens);
int			parse_cylinder(t_scene *scene, char **tokens);
void		cleanup(t_scene *scene);
void		cleanup_and_exit(t_scene *scene, int code);

void		ft_put_pixel(t_img *img, int x, int y, int color);
void		render(t_scene *scene);

double		ft_dot(t_vector v1, t_vector v2);
t_vector	ft_cross(t_vector v1, t_vector v2);
t_vector	ft_scale_vector(t_vector v, double scale);
t_vector	vectors_sum(int n, ...);
t_vector	vectors_sub(int n, ...);
t_vector	normalize(t_vector vec);
double		vector_magnitude(t_vector vec);

t_ray		get_camera_ray(t_scene *scene, int px, int py);
double		closest_hit(t_scene *scene, t_ray camera_ray,
				int *shape_index);
t_vector	get_normal(t_shapes_list *current_shape,
				t_ray camera_ray, t_vector hitpoint);
double		get_t_sphere(t_shape *sphere, t_ray camera_ray);
double		get_t_plane(t_shape *plane, t_ray camera_ray);
double		get_t_cylinder(t_shape *cylinder, t_ray camera_ray);
int			get_color(t_shapes_list *current_shape,
				t_scene *scene, t_vector normal,
				t_vector hitpoint);
t_vector	get_hitpoint(t_ray camera_ray, double t);
double		get_discriminant(double a, double b, double c);
double		negative_quadratic_formula(double a, double b,
				double discriminant);
double		positive_quadratic_formula(double a, double b,
				double discriminant);
int			check_height_validity(t_shape *cyl, double t,
				t_vector OC, t_vector d);
void		cooffe(double *quad_fac, t_vector oc, t_vector d,
				t_vector A);
double		get_t_disc(t_vector center, t_vector normal, double radius,
				t_ray camera_ray);
#endif
