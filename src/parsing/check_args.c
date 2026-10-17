/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahhammad <ahhammad@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 15:32:12 by ahhammad          #+#    #+#             */
/*   Updated: 2026/10/15 15:32:12 by ahhammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int check_args(int ac, char *av[])
{
    if (ac != 2)
    {
        ft_putstr_fd("Usage: ./miniRT <scene.rt>\n", 1);
        return (0);
    }
    if (ft_strlen(av[1]) < 4)
    {
        ft_putstr_fd("Error: Invalid file name. Expected a file with '.rt' extension\n", 1);
        return (0);
    }
    if (!ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3))
    {
        ft_putstr_fd("Error: Invalid file extension. Expected '.rt'\n", 1);
        return (0);
    }
    return (1);
}