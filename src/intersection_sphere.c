/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 12:31:11 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/21 14:39:59 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/miniRT.h"

double get_discriminant(double a,double b,double c)
{
	return(pow(b, 2) - (4 * a * c));
}

double negative_quadratic_formula(double a, double b, double discriminant)
{
	return((-1 * b - sqrt(discriminant)) / (2 * a));
}
double positive_quadratic_formula(double a, double b, double discriminant)
{
	return((-1 * b + sqrt(discriminant)) / (2 * a));
}

double get_t_sphere(t_shape *sphere, t_ray camera_ray)
{
	t_vector	C;
	t_vector	Q;
	t_vector	d;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		t2;

	C = sphere->sphere.center;
	Q = camera_ray.origin;
	d = camera_ray.direction;
	//ax^2 + bx + c
	a = ft_dot(d,d);
	b = ft_dot(ft_scale_vector(d, -2), vectors_sub(2, C, Q));
	c = ft_dot(vectors_sub(2, C, Q), vectors_sub(2, C, Q)) - pow(sphere->sphere.diameter / 2, 2);
	discriminant = get_discriminant(a, b, c);
	if (discriminant < 0)
		return (-1);
	else if (discriminant == 0)
	{
		t1 = positive_quadratic_formula(a, b, discriminant);
		return (t1);
	}	
	else
	{
		t1 = negative_quadratic_formula(a, b, discriminant);
		t2 = positive_quadratic_formula(a, b, discriminant);
		if (t1 > 0 && t2 > 0)
			return (t1);
		else if (t1 < 0 && t2 > 0)
			return (t2);
		else if (t1 < 0 && t2 < 0)
			return (-1);
	}
	return (-1);
}
