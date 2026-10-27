/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder_utilc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 15:29:37 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/27 15:30:14 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// height = OC·A + t * (D·A)
// Valid only if |height| <= h/2 (and t > EPS) cyl, t1, OC, d
int	check_height_validity(t_shape *cyl, double t, t_vector OC, t_vector d)
{
	t_vector	a_vec;
	double		height;
	double		h;

	h = cyl->cylinder.height;
	a_vec = cyl->cylinder.axis;
	height = t * ft_dot(d, a_vec) - ft_dot(OC, a_vec);
	if (fabs(height) <= h / 2)
		return (1);
	return (0);
}

void	cooffe(double *quad_fac, t_vector oc, t_vector d, t_vector A)
{
	t_vector	oc_perp;
	t_vector	d_perp;

	oc_perp = vectors_sub(2, oc, ft_scale_vector(A, ft_dot(oc, A)));
	d_perp = vectors_sub(2, d, ft_scale_vector(A, ft_dot(d, A)));
	quad_fac[0] = ft_dot(d_perp, d_perp);
	quad_fac[1] = ft_dot(ft_scale_vector(d_perp, -2), oc_perp);
	quad_fac[2] = ft_dot(oc_perp, oc_perp);
}
