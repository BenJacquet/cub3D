/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:09:24 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/11 16:53:09 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

void		fill_space(t_var *var, int y, int x)
{
	if ((y == 0 && (x >= 0 && x <= var->size_x)) &&
			!(var->map[y][x - 1] == '0' || var->map[y][x + 1] == '0' ||
				var->map[y + 1][x] == '0'))
		var->map[y][x] = '1';
	else if ((x == 0 && (y >= 0 && y <= var->size_y)) &&
			!(var->map[y - 1][x] == '0' || var->map[y + 1][x] == '0' ||
				var->map[y][x + 1] == '0'))
		var->map[y][x] = '1';
	else if ((y == var->size_y - 1 && (x >= 0 && x <= var->size_x)) &&
			!(var->map[y][x - 1] == '0' || var->map[y][x + 1] == '0' ||
				var->map[y - 1][x] == '0'))
		var->map[y][x] = '1';
	else if ((x == var->size_x - 1 && (y >= 0 && y <= var->size_y)) &&
			!(var->map[y - 1][x] == '0' || var->map[y + 1][x] == '0' ||
				var->map[y][x - 1] == '0'))
		var->map[y][x] = '1';
	else if (!(var->map[y - 1][x] == '0' || var->map[y + 1][x] == '0' ||
				var->map[y][x - 1] == '0' || var->map[y][x + 1] == '0'))
		var->map[y][x] = '1';
}

char		*resize_line(char *line, int spaces)
{
	char	end[spaces + 1];
	int		i;
	char	*new;

	i = 0;
	while (i < spaces)
		end[i++] = ' ';
	end[i] = '\0';
	new = ft_strjoin(line, end);
	free(line);
	return (new);
}

void		make_rectangular(t_var *var)
{
	int		y;
	int		hi_len;
	int		len;

	y = -1;
	hi_len = 0;
	while (var->map[++y])
	{
		len = ft_strlen(var->map[y]);
		hi_len = (hi_len < len ? len : hi_len);
	}
	var->size_x = hi_len;
	y = -1;
	while (var->map[++y])
	{
		len = ft_strlen(var->map[y]);
		if (len < hi_len)
			var->map[y] = resize_line(var->map[y], hi_len - len);
	}
	var->size_y = y;
}

void		check_map(t_var *var)
{
	int		x;
	int		y;

	y = -1;
	while (var->map[++y])
	{
		x = -1;
		while (var->map[y][++x])
		{
			if (!ft_isinset("012NSWE ", var->map[y][x]))
				close_game(var, "Map can only contain 0 1 2 N S W E ' '.\n");
		}
	}
	if (!var->player.pos_x || !var->player.pos_y)
		close_game(var, "Player position must be specified.\n");
}
