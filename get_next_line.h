/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:10:19 by jabenjam          #+#    #+#             */
/*   Updated: 2020/03/09 14:16:08 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);
int					ft_findn(char *s);
int					get_next_line(int fd, char **line);
char				*get_line(char *rem);
char				*get_remain(char *rem);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif
