/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:45:36 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/29 14:28:35 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int cub_parser2(t_var *var, char *line)
{
    if (line && line[0] == 'R' && var->width == 0 && var->height == 0)
        parse_resolution(var, ++line);
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
    else if (line && line[0] == 'S' && var->s_path == 0)
        var->s_path = parse_path(++line);
    return (1);
}

void cub_parser(t_var *var, int fd)
{
    int out;
    char **params;
    char buffer[4096];
    char *save;

    out = 1;
    if (!(save = malloc(sizeof(char) * 4096)))
        close_game(var, "Could not allocate memory for read() buffer.");
    ft_bzero(save, 4096);
    while ((out = read(fd, buffer, 4096)) > 0)
    {
        save = ft_strjoin(save, buffer);
        save[out] = '\0';
    }
    params = ft_split(save, '\n');
    free(save);
    while (*params != 0 && var->number < 8 && !ft_isinset("012", **params))
    {
        cub_parser2(var, *params);
        free(*(params++));
        var->number++;
    }
    check_parameters(var);
    parse_map(var, params);
    close(fd);
}