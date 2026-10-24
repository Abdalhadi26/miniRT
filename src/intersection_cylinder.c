/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 17:33:11 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/24 08:59:55 by aayasrah         ###   ########.fr       */
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


double get_t_cylinder(t_shape *cylinder, t_ray camera_ray)
{
	t_vector	OC;
	t_vector	d;
	t_vector	OC_perp;
	t_vector	d_perp;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;

	OC = vectors_sub(2, cylinder->cylinder.center, camera_ray.origin);
	d = camera_ray.direction;
	OC_perp = vectors_sub(2, OC, ft_scale_vector(cylinder->cylinder.axis, ft_dot(OC, cylinder->cylinder.axis)));
	d_perp = vectors_sub(2, d, ft_scale_vector(cylinder->cylinder.axis, ft_dot(d, cylinder->cylinder.axis)));
	//ax^2 + bx + c
	a = ft_dot(d_perp, d_perp);
	b = ft_dot(ft_scale_vector(d_perp, -2), OC_perp);
	c = ft_dot(OC_perp, OC_perp) - pow(cylinder->cylinder.diameter / 2, 2);
	discriminant = get_discriminant(a, b, c);
	if (discriminant < 0)
		return (-1);
	else if (discriminant == 0)
	{
		t1 = positive_quadratic_formula(a, b, discriminant);
		if (check_height_validity(t1, OC, cylinder->cylinder.axis, d, cylinder->cylinder.height) == 1)
			return (t1);
		return (-1);
	}	
	else
	{
		t1 = negative_quadratic_formula(a, b, discriminant);
		t2 = positive_quadratic_formula(a, b, discriminant);
		if (t1 > EPS && t2 > EPS)
		{
			if (check_height_validity(t1, OC, cylinder->cylinder.axis, d, cylinder->cylinder.height) == 1)
				return (t1);
			else if (check_height_validity(t2, OC, cylinder->cylinder.axis, d, cylinder->cylinder.height) == 1)
				return (t2);
			return (-1);
		}
		else if (t1 < EPS && t2 > EPS)
		{
			if (check_height_validity(t2, OC, cylinder->cylinder.axis, d, cylinder->cylinder.height) == 1)
				return (t2);
			return (-1);
		}
		else if (t1 < EPS && t2 < EPS)
			return (-1);
	}
	return (-1);
}
