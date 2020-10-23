/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:45:36 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/20 18:07:54 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

int			cub_parser2(t_var *var, char *line, int ac)
{
	if (line && line[0] == 'R' && var->width == 0 && var->height == 0)
		parse_resolution(var, ++line, ac);
	else if (line && line[0] == 'F' && var->f_color == 0)
		var->f_color = parse_rgb(var, ++line);
	else if (line && line[0] == 'C' && var->c_color == 0)
		var->c_color = parse_rgb(var, ++line);
	else if (line && line[0] == 'N' && line[1] == 'O' && var->tex[2].path == 0)
		var->tex[2].path = parse_path(2 + line);
	else if (line && line[0] == 'S' && line[1] == 'O' && var->tex[3].path == 0)
		var->tex[3].path = parse_path(2 + line);
	else if (line && line[0] == 'W' && line[1] == 'E' && var->tex[0].path == 0)
		var->tex[0].path = parse_path(2 + line);
	else if (line && line[0] == 'E' && line[1] == 'A' && var->tex[1].path == 0)
		var->tex[1].path = parse_path(2 + line);
	else if (line && line[0] == 'S' && var->tex[4].path == 0)
		var->tex[4].path = parse_path(++line);
	return (1);
}

char		**get_param(t_var *var, char **params, int ac)
{
	while (*params != 0 && var->number < 8 && !ft_isinset("012", **params))
	{
		cub_parser2(var, *params, ac);
		free(*(params++));
		var->number++;
	}
	return (params);
}

void		cub_parser(t_var *var, int fd, int ac)
{
	int		out;
	char	**params;
	char	buffer[4096];
	char	*save;
	char	*bkp;

	out = 1;
	if (!(save = malloc(sizeof(char) * 4096)))
		close_game(var, "Could not allocate memory for read() buffer.\n");
	ft_bzero(save, 4096);
	while ((out = read(fd, buffer, 4096)) > 0)
	{
		bkp = save;
		save = ft_strjoin(save, buffer);
		save[out] = '\0';
		free(bkp);
	}
	params = ft_split(save, '\n');
	free(save);
	params = get_param(var, params, ac);
	check_parameters(var);
	parse_map(var, params);
	close(fd);
}
