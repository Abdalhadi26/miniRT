/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:31:11 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 17:40:06 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

double	get_discriminant(double a, double b, double c)
{
	return (pow(b, 2) - (4 * a * c));
}

double	negative_quadratic_formula(double a, double b, double discriminant)
{
	return ((-1 * b - sqrt(discriminant)) / (2 * a));
}

double	positive_quadratic_formula(double a, double b, double discriminant)
{
	return ((-1 * b + sqrt(discriminant)) / (2 * a));
}

double	get_t(double discriminant, double a, double b)
{
	double	t1;
	double	t2;

	if (discriminant == 0)
	{
		t1 = positive_quadratic_formula(a, b, discriminant);
		return (t1);
	}
	else
	{
		t1 = negative_quadratic_formula(a, b, discriminant);
		t2 = positive_quadratic_formula(a, b, discriminant);
		if (t1 > EPS && t2 > EPS)
			return (t1);
		else if (t1 < EPS && t2 > EPS)
			return (t2);
		else if (t1 < EPS && t2 < EPS)
			return (-1);
	}
	return (-1);
}

double	get_t_sphere(t_shape *sphere, t_ray camera_ray)
{
	t_vector	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vectors_sub(2, sphere->sphere.center, camera_ray.origin);
	a = ft_dot(camera_ray.direction, camera_ray.direction);
	b = ft_dot(ft_scale_vector(camera_ray.direction, -2), oc);
	c = ft_dot(oc, oc) - pow(sphere->sphere.diameter / 2, 2);
	discriminant = get_discriminant(a, b, c);
	if (discriminant < 0)
		return (-1);
	return (get_t(discriminant, a, b));
}
