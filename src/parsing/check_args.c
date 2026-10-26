/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:32:12 by ahhammad          #+#    #+#             */
/*   Updated: 2026/10/26 12:44:00 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_args(int ac, char *av[])
{
	int	len;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./miniRT <scene.rt>\n", 2);
		return (0);
	}
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strncmp(av[1] + len - 3, ".rt", 3) != 0
		|| av[1][len - 4] == '/')
	{
		ft_putstr_fd("Error\nInvalid file extension, expected '.rt'\n", 2);
		return (0);
	}
	return (1);
}
