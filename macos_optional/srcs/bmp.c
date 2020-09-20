/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:52:02 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 22:19:15 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	fill_bmp(int fd, t_var *var)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		write(fd, "\0\0\0\0\0\0\0\0", 8);
		i++;
	}
	i = 0;
	while (var->height >= 0)
	{
		i = var->width * 4 * var->height;
		write(fd, &var->screen.dat[i], var->width * 4);
		var->height--;
	}
}

void	create_bmp(t_var *var)
{
	int	fd;
	int	size;
	int	array;
	int	header_size;
	int	color_plane;

	fd = open("Cub3D.bmp", O_RDWR | O_CREAT, 0666 | O_TRUNC);
	size = 54 + (var->width * var->height * 4);
	array = 54;
	header_size = 40;
	color_plane = 1;
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &array, 4);
	write(fd, &header_size, 4);
	write(fd, &var->width, 4);
	write(fd, &var->height, 4);
	write(fd, &color_plane, 2);
	write(fd, &var->screen.bpp, 2);
	fill_bmp(fd, var);
	close(fd);
	close_game(var, "");
}
