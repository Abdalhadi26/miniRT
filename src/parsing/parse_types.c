/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:45:00 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/26 12:45:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_color(char *str, t_color *color)
{
	char	**parts;
	int		vals[3];
	int		i;

	if (count_char(str, ',') != 2)
		return (0);
	parts = ft_split(str, ',');
	if (split_len(parts) != 3)
		return (free_split(parts), 0);
	i = 0;
	while (i < 3)
	{
		if (!is_all_digits(parts[i]))
			return (free_split(parts), 0);
		vals[i] = ft_atoi(parts[i]);
		if (vals[i] < 0 || vals[i] > 255)
			return (free_split(parts), 0);
		i++;
	}
	color->r = vals[0];
	color->g = vals[1];
	color->b = vals[2];
	free_split(parts);
	return (1);
}

int	parse_vector(char *str, t_vector *vec)
{
	char	**parts;
	double	vals[3];
	int		i;

	if (count_char(str, ',') != 2)
		return (0);
	parts = ft_split(str, ',');
	if (split_len(parts) != 3)
		return (free_split(parts), 0);
	i = 0;
	while (i < 3)
	{
		if (!ft_atod(parts[i], &vals[i]))
			return (free_split(parts), 0);
		i++;
	}
	vec->x = vals[0];
	vec->y = vals[1];
	vec->z = vals[2];
	free_split(parts);
	return (1);
}

int	parse_norm_vector(char *str, t_vector *vec)
{
	if (!parse_vector(str, vec))
		return (0);
	if (vec->x < -1.0 || vec->x > 1.0
		|| vec->y < -1.0 || vec->y > 1.0
		|| vec->z < -1.0 || vec->z > 1.0)
		return (0);
	if (vector_magnitude(*vec) < EPS)
		return (0);
	*vec = normalize(*vec);
	return (1);
}
