/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:57:22 by aayasrah          #+#    #+#             */
/*   Updated: 2026/01/24 14:22:17 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	is_valid_double(const char *str)
{
	int	i;
	int	dot_count;
	int	num_count;

	i = 0;
	dot_count = 0;
	num_count = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'))
			return (0);
		if (str[i] >= '0' && str[i] <= '9')
			num_count++;
		if (str[i] == '.')
			dot_count++;
		i++;
	}
	if (dot_count > 1 || num_count == 0)
		return (0);
	return (1);
}

static long	get_int(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] != '.' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

static double	get_decimal(const char *str)
{
	int		i;
	double	res;
	double	divisor;

	i = 0;
	res = 0;
	divisor = 1.0;
	while (str[i] != '.' && str[i])
		i++;
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		divisor *= 10;
		i++;
	}
	return (res / divisor);
}

int	ft_atod(const char *s, double *out)
{
	int		i;
	int		sign;
	double	decimal_part;
	long	integer_part;

	sign = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	if (!is_valid_double(&s[i]))
		return (0);
	integer_part = get_int(&s[i]);
	decimal_part = get_decimal(&s[i]);
	*out = (integer_part + decimal_part) * sign;
	return (1);
}
