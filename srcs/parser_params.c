/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:44:24 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 23:42:19 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void		parse_resolution(t_var *var, char *line, int ac)
{
	int		x;

	x = 0;
	while (line && *line == ' ')
		line++;
	while (line && *line >= '0' && *line <= '9' && *line != ' ')
		x = (x * 10) + (*(line++) - '0');
	var->width = (x > 2560 && ac == 2 ? 2560 : x);
	x = 0;
	while (line && *line == ' ')
		line++;
	while (line && *line >= '0' && *line <= '9')
		x = (x * 10) + (*(line++) - '0');
	var->height = (x > 1440 && ac == 2 ? 1440 : x);
	check_numbers(var, line, 1);
}

char		*parse_path(char *line)
{
	char	*path;

	while (line && *line == ' ')
		line++;
	path = ft_strdup(line);
	return (path);
}

int			parse_rgb(t_var *var, char *line)
{
	int		rgb;
	int		x;

	rgb = 0;
	while (line && *line == ' ')
		line++;
	while (line && ft_isinset("0123456789", *line))
	{
		x = 0;
		while (*line >= '0' && *line <= '9')
			x = (x * 10) + (*(line++) - '0');
		if (x < 0 || x > 255)
			close_game(var, "Color must be between 0 and 255.\n");
		rgb = (var->colors++ == 0 ? x : (rgb << 8) + x);
		line += (*line == ',' && var->colors != 3 ? 1 : 0);
		while (line && *line == ' ' && var->colors != 3)
			line++;
	}
	check_numbers(var, line, 2);
	var->colors = 0;
	return (rgb);
}

int			parse_player(t_var *var, int x, int y)
{
	if (var->map[y][x] == 'N' || var->map[y][x] == 'S')
	{
		var->cam.dir_y = (var->map[y][x] == 'N' ? -1.0 : 1.0);
		var->cam.plane_x = (var->map[y][x] == 'N' ? 0.66 : -0.66);
	}
	else if (var->map[y][x] == 'E' || var->map[y][x] == 'W')
	{
		var->cam.dir_x = (var->map[y][x] == 'E' ? 1.0 : -1.0);
		var->cam.plane_y = (var->map[y][x] == 'E' ? 0.66 : -0.66);
	}
	if (var->map[y][x] == 'N' || var->map[y][x] == 'S' ||
			var->map[y][x] == 'W' || var->map[y][x] == 'E')
	{
		if (var->player.pos_x && var->player.pos_y)
			close_game(var, "Player position specified more than once.\n");
		var->player.pos_x = x + 0.5;
		var->player.pos_y = y + 0.5;
		if (!(var->player.pos_x >= 1 && var->player.pos_x <= var->size_x - 1) ||
			!(var->player.pos_y >= 1 && var->player.pos_y <= var->size_y - 1))
			close_game(var, "Incorrect player position.\n");
	}
	return (0);
}

void		parse_map(t_var *var, char **params)
{
	int		y;
	int		x;

	y = -1;
	var->map = params;
	make_rectangular(var);
	is_closed(var);
	while (var->map[++y])
	{
		x = -1;
		while (var->map[y][++x] != '\0')
		{
			if (var->map[y][x] == '2')
				var->sprites = store_sprite(var, x, y);
			parse_player(var, x, y);
		}
	}
	var->size_y = y;
	check_map(var);
}
