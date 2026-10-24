/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 17:33:11 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/24 11:51:24 by aayasrah         ###   ########.fr       */
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

#include "../includes/miniRT.h"
#include <stdio.h>
#include <stdlib.h>

static void	run_test(const char *name,
		t_vector center, t_vector axis,
		double diameter, double height,
		t_vector origin, t_vector dir, double expected)
{
	t_shape	*cyl;
	t_ray	ray;
	double	t;

	cyl = calloc(1, sizeof(t_shape));
	cyl->cylinder.center   = center;
	cyl->cylinder.axis     = axis;
	cyl->cylinder.diameter = diameter;
	cyl->cylinder.height   = height;
	ray.origin    = origin;
	ray.direction = dir;

	t = get_t_cylinder(cyl, ray);
	printf("%-35s | got = %12.6f | expected = %12.6f\n",
		name, t, expected);
	free(cyl);
}

int	main(void)
{
	/* All cylinders centered at (0,0,0) with vertical axis */
	t_vector	v = (t_vector){0, 1, 0};

	/* T1: tube hit — ray comes at the side, hits tube at x = -1 */
	run_test("T1  tube hit (side entry)",
		(t_vector){0, 0, 0}, v, 2.0, 10.0,
		(t_vector){-5, 0, 0}, (t_vector){1, 0, 0},
		4.0);

	/* T2: tube miss — ray at y = 10, above the cylinder (h/2 = 5),
	 * quadratic gives t=4/6 but height check rejects them */
	run_test("T2  tube hit rejected by height",
		(t_vector){0, 0, 0}, v, 2.0, 10.0,
		(t_vector){-5, 10, 0}, (t_vector){1, 0, 0},
		-1.0);

	/* T3: top cap hit — parallel ray, tube skipped, cap catches at t = 3 */
	run_test("T3  top cap hit",
		(t_vector){0, 0, 0}, v, 4.0, 4.0,
		(t_vector){0, 5, 0}, (t_vector){0, -1, 0},
		3.0);

	/* T4: both caps in front, nearer one wins (top at t=8, bottom at t=12) */
	run_test("T4  both caps, nearer wins",
		(t_vector){0, 0, 0}, v, 4.0, 4.0,
		(t_vector){0, 10, 0}, (t_vector){0, -1, 0},
		8.0);

	/* T5: angled tube hit — 45° into the side
	 * t1 = (14.142 - 2) / 2 = 6.071067 */
	run_test("T5  angled tube hit",
		(t_vector){0, 0, 0}, v, 2.0, 10.0,
		(t_vector){-5, 0, -5}, (t_vector){0.70710678, 0, 0.70710678},
		6.071067);

	/* T6: caps miss — ray falls straight down but 5 units off-axis, outside r=2 */
	run_test("T6  cap miss (outside radius)",
		(t_vector){0, 0, 0}, v, 4.0, 4.0,
		(t_vector){5, 5, 0}, (t_vector){0, -1, 0},
		-1.0);

	/* T7: ray behind — origin past the tube, moving away */
	run_test("T7  ray moving away",
		(t_vector){0, 0, 0}, v, 2.0, 10.0,
		(t_vector){5, 0, 0}, (t_vector){1, 0, 0},
		-1.0);

	/* T8: tube hit from inside — origin at axis, ray out sideways
	 * OC = center - origin = (0,0,0), OC_perp = (0,0,0)
	 * c = 0 - 1 = -1, b = 0, a = 1 → disc = 4, t1 = 1, t2 = -1 */
	run_test("T8  from inside, hits tube from within",
		(t_vector){0, 0, 0}, v, 2.0, 10.0,
		(t_vector){0, 0, 0}, (t_vector){1, 0, 0},
		1.0);

	return (0);
}