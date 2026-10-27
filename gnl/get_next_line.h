/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:19:11 by ahhammad          #+#    #+#             */
/*   Updated: 2026/10/27 14:04:22 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_strlen_gnl(char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	ft_strlcpy_gnl(char *dest, const char *src);
void	ft_strlcat_gnl(char *dst, char *src);
char	*get_next_line(int fd);
char	*cpye_to_nl(char *p);
bool	has_nl(char *p);
int		len_etb(char *p);
void	new_str(char *p);

#endif
