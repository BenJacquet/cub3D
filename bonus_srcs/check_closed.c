/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 16:15:19 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/02 18:55:13 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d.h"

void check_segment(t_var *var, char *segment)
{
    int len;

    len = ft_strlen(segment);
    if (ft_isinset("0NSWE", segment[0]) ||
        ft_isinset("0NSWE", segment[len - 1]))
    {
        if (ft_isinset("NSWE", segment[0]) ||
            ft_isinset("NSWE", segment[len - 1]))
            close_game(var, "Incorrect player position.\n");
        close_game(var, "Map is not closed or is not filled.\n");
    }
}

void check_vertically(t_var *var, int x)
{
    int y;
    int i;
    char segment[var->size_y + 1];

    y = 0;
    while (y < var->size_y)
    {
        i = 0;
        while (y < var->size_y && var->map[y][x] != ' ')
            segment[i++] = var->map[y++][x];
        segment[i] = '\0';
        check_segment(var, segment);
        y++;
    }
}

void check_horizontally(t_var *var, int y)
{
    int x;
    int i;
    char segment[var->size_x + 1];

    x = 0;
    while (x < var->size_x)
    {
        i = 0;
        check_vertically(var, x);
        while (x < var->size_x && var->map[y][x] != ' ')
            segment[i++] = var->map[y][x++];
        segment[i] = '\0';
        check_segment(var, segment);
        x++;
    }
}


void is_closed(t_var *var)
{
    int y;
    int x;

    y = -1;
    while (var->map[++y])
        check_horizontally(var, y);
    y = -1;
    while (var->map[++y])
    {
        x = -1;
        while (var->map[y][++x])
        {
            if (var->map[y][x] == ' ')
                fill_space(var, y, x);
        }
    }
}