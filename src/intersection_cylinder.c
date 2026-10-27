/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 17:33:11 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/27 15:34:13 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	get_t_disc(t_vector center, t_vector normal, double radius,
		t_ray camera_ray)
{
	t_vector	hit_point;
	t_vector	to_center;
	double		t;
	double		numerator;
	double		denumerator;

	numerator = ft_dot(vectors_sub(2, center, camera_ray.origin), normal);
	denumerator = ft_dot(camera_ray.direction, normal);
	if (denumerator == 0)
		return (-1);
	t = numerator / denumerator;
	if (t <= EPS)
		return (-1);
	hit_point = get_hitpoint(camera_ray, t);
	to_center = vectors_sub(2, hit_point, center);
	if (ft_dot(to_center, to_center) > radius * radius)
		return (-1);
	return (t);
}

double	get_t_tube(t_shape *cyl, t_ray camera_ray, t_vector A, double radius)
{
	t_vector	oc;
	t_vector	d;
	double		quad_fac[3];
	double		t[2];
	double		disc;

	oc = vectors_sub(2, cyl->cylinder.center, camera_ray.origin);
	d = camera_ray.direction;
	cooffe(quad_fac, oc, d, A);
	quad_fac[2] -= radius * radius;
	disc = get_discriminant(quad_fac[0], quad_fac[1], quad_fac[2]);
	if (disc >= 0)
	{
		t[1] = positive_quadratic_formula(quad_fac[0], quad_fac[1], disc);
		t[0] = negative_quadratic_formula(quad_fac[0], quad_fac[1], disc);
		if (t[0] > EPS && check_height_validity(cyl, t[0], oc, d))
			return (t[0]);
		else if (t[1] > EPS && check_height_validity(cyl, t[1], oc, d))
			return (t[1]);
	}
	return (-1);
}

double	chose_best_t(double t_tube, double t_top, double t_bottom)
{
	double	best;

	best = -1;
	if (t_tube > EPS)
		best = t_tube;
	if (t_top > EPS && (best < 0 || t_top < best))
		best = t_top;
	if (t_bottom > EPS && (best < 0 || t_bottom < best))
		best = t_bottom;
	return (best);
}

double	get_t_cylinder(t_shape *cyl, t_ray camera_ray)
{
	t_vector	a_vec;
	t_vector	top_center;
	t_vector	bottom_center;
	double		radius;
	double		t_val[3];

	a_vec = cyl->cylinder.axis;
	radius = cyl->cylinder.diameter / 2;
	t_val[0] = get_t_tube(cyl, camera_ray, a_vec, radius);
	top_center = vectors_sub(2, cyl->cylinder.center, ft_scale_vector(a_vec,
				-cyl->cylinder.height / 2));
	bottom_center = vectors_sub(2, cyl->cylinder.center, ft_scale_vector(a_vec,
				cyl->cylinder.height / 2));
	t_val[1] = get_t_disc(top_center, a_vec, radius, camera_ray);
	t_val[2] = get_t_disc(bottom_center, a_vec, radius, camera_ray);
	return (chose_best_t(t_val[0], t_val[1], t_val[2]));
}
