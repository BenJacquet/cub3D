/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:52:52 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/13 22:30:46 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

int		check_parameters(t_var *var)
{
	if (var->number != 8 || var->width == 0 || var->height == 0 ||
			var->f_color == 0 || var->c_color == 0 || var->tex[0].path == 0 ||
			var->tex[1].path == 0 || var->tex[2].path == 0 ||
			var->tex[3].path == 0 || var->s_path == 0)
	{
		close_game(var, "Invalid map.\n");
	}
	return (0);
}

/*
**  Mode == 1 ? check la fichier;
**  Mode == 2 ? check le flag;
*/

int		check_argument(t_var *var, char *name, char *str, int mode)
{
	int	i;

	i = 0;
	while (name && name[i])
	{
		if (mode == 1)
		{
			if (name[i] == '.' && ft_strcmp(&name[i], str) == 0)
				return (0);
		}
		else if (mode == 2)
		{
			if (ft_strcmp(&name[i], str) == 0)
				return (0);
		}
		i++;
	}
	if (mode == 1)
		close_game(var, "File is invalid or line has bad format.\n");
	else if (mode == 2)
		close_game(var, "Flag must be \"--save\".\n");
	return (1);
}

void	check_tex(t_var *var)
{
	int	i;
	int	fd;

	i = -1;
	while (++i <= 3)
	{
		check_argument(var, var->tex[i].path, ".xpm", 1);
		if ((fd = open(var->tex[i].path, O_RDONLY) == -1))
		{
			close(fd);
			close_game(var, "File is invalid.\n");
		}
		close(fd);
	}
	check_argument(var, var->s_path, ".xpm", 1);
	if ((fd = open(var->s_path, O_RDONLY) == -1))
	{
		close(fd);
		close_game(var, "File is invalid.\n");
	}
	close(fd);
}

/*
**  Mode == 1 ? check la resolution;
**  Mode == 2 ? check les couleurs;
*/

void	check_numbers(t_var *var, char *line, int mode)
{
	if (*line != '\0')
		close_game(var, "Bad formatting.\n");
	if (mode == 1)
	{
		if (var->width <= 0 || var->height <= 0)
			close_game(var, "Resolution is invalid.\n");
	}
	if (mode == 2)
	{
		if (var->colors != 3)
			close_game(var, "Only 3 numbers must be specified.\n");
	}
}
