/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 17:33:11 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/24 13:30:11 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// height = OC·A + t * (D·A)
// Valid only if |height| <= h/2 (and t > EPS)
int check_height_validity(double t,t_vector OC, t_vector A, t_vector d, double h)
{
	double height;

	height = t * ft_dot(d, A) - ft_dot(OC, A);
	if (fabs(height) <= h/2)
		return (1);
	return (0);
}

double get_t_disc(t_vector center, t_vector normal, double radius, t_ray camera_ray)
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

double get_t_cylinder(t_shape *cylinder, t_ray camera_ray)
{
	t_vector	OC;
	t_vector	d;
	t_vector	OC_perp;
	t_vector	d_perp;
	t_vector	A;
	t_vector	top_center;
	t_vector	bottom_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;
	double		h;
	double		radius;
	double		t_tube;
	double		t_top;
	double		t_bottom;
	double		best;

	A = cylinder->cylinder.axis;
	h = cylinder->cylinder.height;
	radius = cylinder->cylinder.diameter / 2;
	OC = vectors_sub(2, cylinder->cylinder.center, camera_ray.origin);
	d = camera_ray.direction;
	OC_perp = vectors_sub(2, OC, ft_scale_vector(A, ft_dot(OC, A)));
	d_perp = vectors_sub(2, d, ft_scale_vector(A, ft_dot(d, A)));

	//ax^2 + bx + c
	a = ft_dot(d_perp, d_perp);
	b = ft_dot(ft_scale_vector(d_perp, -2), OC_perp);
	c = ft_dot(OC_perp, OC_perp) - radius * radius;

	t_tube = -1;
	discriminant = get_discriminant(a, b, c);
	if (discriminant >= 0)
	{
		t1 = negative_quadratic_formula(a, b, discriminant);
		t2 = positive_quadratic_formula(a, b, discriminant);
		if (t1 > EPS && check_height_validity(t1, OC, A, d, h))
			t_tube = t1;
		else if (t2 > EPS && check_height_validity(t2, OC, A, d, h))
			t_tube = t2;
	}

	top_center = vectors_sub(2, cylinder->cylinder.center, ft_scale_vector(A, -h / 2));
	bottom_center = vectors_sub(2, cylinder->cylinder.center, ft_scale_vector(A, h / 2));
	t_top = get_t_disc(top_center, A, radius, camera_ray);
	t_bottom = get_t_disc(bottom_center, A, radius, camera_ray);

	best = -1;
	if (t_tube > EPS)
		best = t_tube;
	if (t_top > EPS && (best < 0 || t_top < best))
		best = t_top;
	if (t_bottom > EPS && (best < 0 || t_bottom < best))
		best = t_bottom;
	return (best);
}
