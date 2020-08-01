/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:44:24 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/01 18:55:08 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d.h"

void parse_resolution(t_var *var, char *line)
{
    int x;

    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9' && *line != ' ')
        x = (x * 10) + (*(line++) - '0');
    var->width = (x > 2560 ? 2560 : x);
    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9')
        x = (x * 10) + (*(line++) - '0');
    var->height = (x > 1440 ? 1440 : x);
    check_numbers(var, line, 1);
}

char *parse_path(char *line)
{
    char *path;

    while (line && *line == ' ')
        line++;
    path = ft_strdup(line);
    return (path);
}

int parse_rgb(t_var *var, char *line)
{
    int rgb;
    int x;

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
        rgb = (var->colors++ == 0 ? rgb = x : (rgb << 8) + x);
        line += (*line == ',' && var->colors != 3 ? 1 : 0);
        while (line && *line == ' ' && var->colors != 3)
            line++;
    }
    check_numbers(var, line, 2);
    var->colors = 0;
    return (rgb);
}

int parse_player(t_var *var, int x, int y)
{
    if (var->map[y][x] == 'N' || var->map[y][x] == 'S')
    {
        var->cam.dir_y = (var->map[y][x] == 'N' ? -1.0 : 1.0);
        var->cam.plane_x = (var->map[y][x] == 'N' ? 0.66 : -0.66);
    }
    else if (var->map[y][x] == 'E' || var->map[y][x] == 'W')
    {
        var->cam.dir_x = (var->map[y][x] == 'E' ? 1.0 : -1.0);
        var->cam.plane_y = (var->map[y][x] == 'W' ? 0.66 : -0.66);
    }
    if (var->map[y][x] == 'N' || var->map[y][x] == 'S' ||
        var->map[y][x] == 'W' || var->map[y][x] == 'E')
    {
        if (var->player.pos_x && var->player.pos_y)
            close_game(var, "Player position specified more than once.\n");
        var->player.pos_x = x + 0.5;
        var->player.pos_y = y + 0.5;
        if (!(var->player.pos_x >= 1 && var->player.pos_x <= var->size_x - 1) ||
            !(var->player.pos_y >= 1 && var->player.pos_y <= var->size_x - 1))
            close_game(var, "Player cannot be placed on map edge.\n");
    }
    return (0);
}

void fill_space(t_var *var, int y, int x)
{
    //printf("\ny = %d --- x = %d\n", x, y);
    if (y == 0 && (x >= 0 && x <= var->size_x))
    {
        //        printf("\ny = %d --- x = %d\n", x, y);
        if (!(var->map[y][x - 1] == '0' || var->map[y][x + 1] == '0' ||
            var->map[y + 1][x] == '0'))
            var->map[y][x] = '1';
        else
            var->map[y][x] = '0';
    }
    else if (y == var->size_y - 1 && (x >= 0 && x <= var->size_x))
    {
        if (!(var->map[y][x - 1] == '0' || var->map[y][x + 1] == '0' ||
            var->map[y - 1][x] == '0'))
            var->map[y][x] = '1';
        else
            var->map[y][x] = '0';
    }
    else if (x == 0 && (y >= 0 && y <= var->size_y))
    {
        if (!(var->map[y - 1][x] == '0' || var->map[y + 1][x] == '0' ||
            var->map[y][x + 1] == '0'))
            var->map[y][x] = '1';
        else
            var->map[y][x] = '0';
    }
    else if (x == var->size_x - 1 && (y >= 0 && y <= var->size_y))
    {
        if (!(var->map[y - 1][x] == '0' || var->map[y + 1][x] == '0' ||
            var->map[y][x - 1] == '0'))
            var->map[y][x] = '1';
        else
            var->map[y][x] = '0';
    }
    else
    {
        if (!(var->map[y - 1][x] == '0' || var->map[y + 1][x] == '0' ||
            var->map[y][x - 1] == '0' || var->map[y][x + 1] == '0'))
            var->map[y][x] = '1';
        else
            var->map[y][x] = '0';
    }
}

void check_segment(t_var *var, char *segment, int x, int y)
{
    int len;

    len = ft_strlen(segment);
    if ((segment[0] == '0') || (segment[len - 1] == '0'))
    {
        printf("\ny = %d --- x = %d --- segment = %s\n", y, x, segment);
        for (int mapy = 0; var->map[mapy]; mapy++)
        {
            if (mapy >= 10)
                printf("(%d): %s\n", mapy, var->map[mapy]);
            else
                printf("(%d) : %s\n", mapy, var->map[mapy]);
        }
        close_game(var, "Map is not closed.\n");
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
        check_segment(var, segment, x, y);
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
        while (x < var->size_x && var->map[y][x] != ' ')
        {
            check_vertically(var, x);
            segment[i++] = var->map[y][x++];
        }
        segment[i] = '\0';
        check_segment(var, segment, x, y);
        x++;
    }
}

void is_closed(t_var *var)
{
    int y;
    int x;

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
    y = -1;
    while (var->map[++y])
        check_horizontally(var, y);
}

char *resize_line(char *line, int spaces)
{
    char end[spaces + 1];
    int i = 0;
    char *new;

    while (i < spaces)
        end[i++] = ' ';
    end[i] = '\0';
    new = ft_strjoin(line, end);
    free(line);
    return (new);
}

void make_rectangular(t_var *var)
{
    int y;
    int hi_len;
    int len;

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

void parse_map(t_var *var, char **params)
{
    int y;
    int x;

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
        /*        if (var->size_x != 0 && var->size_x != x)
            close_game(var, "Invalid map.\n");*/
    }
    var->size_y = y;
    //    check_map(var);
    for (int mapy = 0; var->map[mapy]; mapy++)
    {
        if (mapy >= 10)
            printf("(%d): %s\n", mapy, var->map[mapy]);
        else
            printf("(%d) : %s\n", mapy, var->map[mapy]);
    }
}