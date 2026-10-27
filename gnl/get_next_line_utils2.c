/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 14:02:14 by aayasrah          #+#    #+#             */
/*   Updated: 2026/10/27 14:03:30 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	has_nl(char *p)
{
	int		i;

	i = 0;
	while (p[i] != '\n' && p[i])
		i++;
	if (p[i] == '\n')
		return (true);
	return (false);
}

void	new_str(char *p)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (p[i] != '\n' && p[i] != '\0')
		i++;
	if (p[i] == '\n')
		i++;
	while (p[i])
	{
		p[j] = p[i];
		i++;
		j++;
	}
	p[j] = '\0';
}

int	len_etb(char *p)
{
	int		i;

	i = 0;
	while (p[i] != '\n' && p[i] != '\0')
		i++;
	if (p[i] == '\n')
		return (i + 1);
	return (i);
}
