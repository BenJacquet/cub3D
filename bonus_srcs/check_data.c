/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:52:52 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/29 18:47:25 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d.h"

int check_parameters(t_var *var)
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
int check_argument(t_var *var, char *name, char *str, int mode)
{
    int i;

    i = 0;
    while (name && name[i])
    {
        if (mode == 1)
        {
            if (name[i] == '.' && ft_strcmp(&name[i], str) == 1)
                return (0);
        }
        else if (mode == 2)
        {
            if (ft_strcmp(&name[i], str) == 1)
                return (0);
        }
        i++;
    }
    if (mode == 1)
        close_game(var, "File is invalid\n");
    else if (mode == 2)
        close_game(var, "Flag must be \"--save\".\n");
    return (1);
}

void check_tex(t_var *var)
{
    int i;
    int fd;

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

void check_map(t_var *var)
{
    int x;
    int y;

    x = -1;
    y = -1;
    while (var->map[++y])
    {
        while (var->map[y][++x])
        {
            if (!ft_isinset("012NSWE", var->map[y][x]))
                close_game(var, "Map can only contain 0 1 2 N S W E.\n");
            else if ((x == 0 && var->map[y][x] == '0') ||
                     (x == var->size_x - 1 && var->map[y][x] == '0') ||
                     (y == 0 && var->map[y][x] == '0') ||
                     (y == var->size_y - 1 && var->map[y][x] == '0'))
                close_game(var, "Map is not closed, check the edges.\n");
        }
        x = -1;
    }
    if (!var->player.pos_x && !var->player.pos_y)
        close_game(var, "Player position must be specified.\n");
    if (!(var->player.pos_x >= 1 && var->player.pos_x <= var->size_x - 1) ||
        !(var->player.pos_y >= 1 && var->player.pos_y <= var->size_x - 1))
        close_game(var, "Player cannot be placed on map edge.\n");
}