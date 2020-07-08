/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/08 18:23:59 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_split.c"
#include "utils.c"
#include "keys.h"

void    initialize_structs(t_var *var)
{
    var->size_x = 0;
    var->size_y = 0;
    var->f_color = 0;
    var->c_color = 0;
    var->no_path = 0;
    var->so_path = 0;
    var->we_path = 0;
    var->ea_path = 0;
    var->s_path = 0;
    var->number = 0;
    var->map_x = 0;
    var->map_y = 0;
    var->player.pos_x = 0;
    var->player.pos_y = 0;
    var->player.d_x = 0;
    var->player.d_y = 0;
    var->player.angle = 0;
}

void    get_window_size(t_var *var, char *line)
{
    int     x;

    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9' && *line != ' ')
        x = (x * 10) + (*(line++) - '0');
    var->size_x = x;
    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9')
        x = (x * 10) + (*(line++) - '0');
    var->size_y = x;
    return;
}

char    *get_path(char *line)
{
    char    *path;

    while (line && *line == ' ')
        line++;
    path = ft_strdup(line);
    return(path);
}

int     get_rgb(char *line)
{
    int     rgb;
    int     x;
    int     colors;

    rgb = 0;
    x = 0;
    colors = 0;
    while (line && *line == ' ')
        line++;
	while (line && colors < 3)
    {
 	    while (*line >= '0' && *line <= '9')
		    x = (x * 10) + (*(line++) - '0');
        rgb = (colors == 0 ? rgb = x : (rgb << 8) + x);
        x = 0;
        colors++;
        if (*line == ',')
            line++;
        /*if (x < 0 || x > 255)
            erreur, color "out of range"*/
    }
    return (rgb);
}

void    player_parser(t_player *player, char c)
{
    if (c == 'N')
        player->angle = 3 * PI / 2;
    else if (c == 'S')
        player->angle = PI / 2;
    else if (c == 'E')
        player->angle = 2 * PI;
    else
        player->angle = PI;
    player->d_x = cos(player->angle) * 5;
    player->d_y = sin(player->angle) * 5;
}

void    map_parser(t_var *var, char **params)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    var->map = params;
    while (var->map[i] != 0)
    {
        while (var->map[i][j] != '\0')
        {
            if (var->map[i][j] == ' ')
                var->map[i][j] = '1';
            if (var->map[i][j] == 'N' || var->map[i][j] == 'S' ||
                var->map[i][j] == 'W' || var->map[i][j] == 'E')
            {
                player_parser(&var->player, var->map[i][j]);
                var->player.pos_x = j;
                var->player.pos_y = i;
            }
            j++;
        }
        var->map_x = j;
        j = 0;
        i++;
    }
    var->map_y = i;
}

void    cub_parser2(t_var *var, char *line)
{
    if (line && line[0] == 'R' && var->size_x == 0 && var->size_y == 0)
        get_window_size(var, ++line);
    else if (line && line[0] == 'F' && var->f_color == 0)
        var->f_color = get_rgb(++line);
    else if (line && line[0] == 'C' && var->c_color == 0)
        var->c_color = get_rgb(++line);
    else if (line && line[0] == 'N' && line[1] == 'O' && var->no_path == 0)
        var->no_path = get_path(2 + line);
    else if (line && line[0] == 'S' && line[1] == 'O' && var->so_path == 0)
        var->so_path = get_path(2 + line);
    else if (line && line[0] == 'W' && line[1] == 'E' && var->we_path == 0)
        var->we_path = get_path(2 + line);
    else if (line && line[0] == 'E' && line[1] == 'A' && var->ea_path == 0)
        var->ea_path = get_path(2 + line);
    else if (line && line[0] == 'S' && var->s_path == 0)
        var->s_path = get_path(++line);
}

void    cub_parser(t_var *var, char *cub)
{
    int     fd;
    int     out;
    char    **params;
    char    buffer[4096];
    char    *save;

    out = 1;
    fd = open(cub, O_RDONLY); // ajouter verification de l'extension (.cub)
    if (!(save = malloc(sizeof(char) * 4096)))
		return;
    while ((out = read(fd, buffer, 4095)) > 0)
    {
        save = ft_strjoin(save, buffer);
        save[out] = '\0';
    }
    params = ft_split(save, '\n');
    while (*params != 0 && var->number++ < 8)
    {
        cub_parser2(var, *params);
        free(*(params++));
    }
    map_parser(var, params); // recuperation de la map
    close(fd);
    return;
}

void    background_fill_test(t_var *var, char c, int r, int g, int b)
{
    void    *img_ptr;
    char    *img_dat;
    int     bpp = 32; //bits par pixel (32 = A + R + G + B)
    int     sl = var->size_x * 4; // taille de chaque ligne
    int     endian = 1;
    int     i = 0;

    img_ptr = mlx_new_image(var->mlx, var->size_x, var->size_y / 2);
    img_dat = mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
    while (i < (var->size_x * var->size_y / 2 * 4))
    {
        img_dat[i++] = (char)255;
        img_dat[i++] = (char)r;
        img_dat[i++] = (char)g;
        img_dat[i++] = (char)b;
    }
    if (c == 'C')
        mlx_put_image_to_window(var->mlx, var->win, img_ptr, 0, 0);
    if (c == 'F')
        mlx_put_image_to_window(var->mlx, var->win, img_ptr, 0, var->size_y / 2);
}

int     draw_mini_map(t_var *var)
{
    int     x = 0;
    int     y = 0;
    int     i = 0;
    int     bpp = 32;
    int     sl = 16 * 4;
    int     size = 16;
    int     endian = 0;
    int     x_image = 0;
    int     y_image = 0;
    void    *img_ptr;
    char    *img_dat;

    mlx_clear_window(var->mlx, var->win); // a virer une fois que tout sera render
    img_ptr = mlx_new_image(var->mlx, 16, 16);
    img_dat = mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
    while (i < (16 * 16 * 4))
    {
        img_dat[i++] = 0;
        img_dat[i++] = 0;
        img_dat[i++] = 127;
        img_dat[i++] = 0;
    }
    while (var->map[y])
    {
        while (var->map[y][x])
        {
            if (var->map[y][x] == '1')
                mlx_put_image_to_window(var->mlx, var->win, img_ptr, x_image, y_image);
            if (x == (int)var->player.pos_x  && y == (int)var->player.pos_y)
                mlx_put_image_to_window(var->mlx, var->win, mlx_xpm_file_to_image(var->mlx, "./textures/arrow.xpm", &size, &size), ((int)var->player.pos_x * 17), ((int)var->player.pos_y * 17));
            x++;
            x_image += 17;
        }
        x = 0;
        x_image = 0;
        y_image += 17;
        y++;
    }
    return (0);
}

int     draw(t_var *var)
{
    draw_mini_map(var);
    return (0);
}

int     key_press(int key, t_var *var) // TEST //
{
    printf("\nkey = %d\n", key);
    if (key == K_W)
    {
        var->player.pos_x += (var->player.d_x * 0.1);
        var->player.pos_y += (var->player.d_y * 0.1);
    }
    else if (key == K_S)
    {
        var->player.pos_x -= (var->player.d_x * 0.1);
        var->player.pos_y -= (var->player.d_y * 0.1);
    }
    else if (key == K_LEFT)
    {
        var->player.angle -= 0.1;
        var->player.d_x = cos(var->player.angle) * 5;
        var->player.d_y = sin(var->player.angle) * 5;
        if (var->player.angle < 0)
            var->player.angle += 2 * PI;
    }
    else if (key == K_RIGHT)
    {
        var->player.angle += 0.1;
        var->player.d_x = cos(var->player.angle) * 5;
        var->player.d_y = sin(var->player.angle) * 5;
        if (var->player.angle > 2 * PI)
            var->player.angle -= 2 * PI;
    }
    else if (key == K_R)
    {
        mlx_clear_window(var->mlx, var->win);
        mlx_string_put(var->mlx, var->win, 0, 10, 0255255000, "PRESS W/LEFT/S/RIGHT TO MOVE");
    }
    draw_mini_map(var);
    if (key == K_ESC) // ESC
        mlx_destroy_window(var->mlx, var->win);
    printf("PLAYER\npos_x=%f\npos_y=%f\nangle=%f\n", var->player.pos_x, var->player.pos_y, var->player.angle);
    return (0);
}

int     main(int ac, char **av)
{
        t_var       var;

    initialize_structs(&var);
    if (ac == 2 || ac == 3)
    {
        // ajouter verification d'erreurs dans les arguments [if (a || b)]
        cub_parser(&var, av[1]);
        var.mlx = mlx_init();
        var.win = mlx_new_window(var.mlx, var.size_x, var.size_y, "Cub3D");
        printf("VARS\nsize_x=%d\nsize_y=%d\nf_color=%d\nc_color=%d\nno_path=%s\nso_path=%s\nwe_path=%s\nea_path=%s\ns_path=%s\nnumber of parameters=%d\nmlx=%p\nwin=%p\nmap=\n", var.size_x, var.size_y, var.f_color, var.c_color, var.no_path, var.so_path, var.we_path, var.ea_path, var.s_path, var.number, var.mlx, var.win);
        printf("PLAYER\npos_x=%f\npos_y=%f\nangle=%f\n", var.player.pos_x, var.player.pos_y, var.player.angle);
//        while (*var.map != 0)
//            printf("%s\n", *(var.map++));
//        background_fill_test(&var, 'C', 0, 255, 255);
//        background_fill_test(&var, 'F', 120, 120, 100);
//        mlx_put_image_to_window(var.mlx, var.win, mlx_xpm_file_to_image(var.mlx, var.no_path, &x, &y), 0, 0);
//        mlx_put_image_to_window(var.mlx, var.win, mlx_xpm_file_to_image(var.mlx, var.so_path, &x, &y), 64, 0);
        draw(&var);
        mlx_hook(var.win, 2, 0, key_press, &var);
//        mlx_hook(var.win, 2, 0, key_release, &var);
        mlx_loop(var.mlx);
    }
    return(0);
}