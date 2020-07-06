/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/06 18:56:59 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_split.c"
#include "utils.c"

void    initialize_var(t_var *var)
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
    var->x_test = 40;
    var->y_test = 40;
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
            j++;
        }
        j = 0;
        i++;;
    }
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

void    background_test(t_var *var, char c, int r, int g, int b)
{
    void    *img_ptr;
    char    *img_dat;
    int     bpp = 32;
    int     sl = var->size_x * 4;
    int     endian = 1;
    int     i = 0;

    img_ptr = mlx_new_image(var->mlx, var->size_x, var->size_y / 2);
    img_dat = mlx_get_data_addr(img_ptr, &bpp, &sl, &endian);
    while (i < (var->size_x * var->size_y / 2 * 4))
    {
        img_dat[i++] = (char)0;
        img_dat[i++] = (char)r;
        img_dat[i++] = (char)g;
        img_dat[i++] = (char)b;
    }
    if (c == 'C')
        mlx_put_image_to_window(var->mlx, var->win, img_ptr, 0, 0);
    else if (c == 'F')
        mlx_put_image_to_window(var->mlx, var->win, img_ptr, 0, var->size_y / 2);
}

int     pixel_trail(int key, t_var *var)
{
    printf("\nkey = %d\n", key);
    if (key == 13 && var->y_test > 1) // W
        mlx_pixel_put(var->mlx, var->win, var->x_test, --var->y_test, 0255255000);
    else if (key == 0 && var->x_test > 1) // A
        mlx_pixel_put(var->mlx, var->win, --var->x_test, var->y_test, 0255255000);
    else if (key == 1 && var->y_test < 1080) // S
        mlx_pixel_put(var->mlx, var->win, var->x_test, ++var->y_test, 0255255000);
    else if (key == 2 && var->x_test < 1920) // D
        mlx_pixel_put(var->mlx, var->win, ++var->x_test, var->y_test, 0255255000);
    else if (key == 15) // R
    {
        mlx_clear_window(var->mlx, var->win);
        mlx_string_put(var->mlx, var->win, 20, 20, 0255255000, "PRESS W/A/S/D TO DRAW A TRAIL");
        var->x_test = 40;
        var->y_test = 40;
    }
/*    else if (key == 34) // I
    {
        background_test(var, 'C', 0, 150, 255);
        background_test(var, 'F', 120, 120, 100);
    }*/
    else if (key == 12) // Q
        mlx_destroy_window(var->mlx, var->win);
    return (0);
}

int     main(int ac, char **av)
{
        t_var   var;

    initialize_var(&var);
    if (ac == 2 || ac == 3)
    {
        // ajouter verification d'erreurs dans les arguments [if (a || b)]
        cub_parser(&var, av[1]);
        var.mlx = mlx_init();
        var.win = mlx_new_window(var.mlx, var.size_x, var.size_y, "Cub3D");
        printf("VARS\nsize_x=%d\nsize_y=%d\nf_color=%d\nc_color=%d\nno_path=%s\nso_path=%s\nwe_path=%s\nea_path=%s\ns_path=%s\nnumber of parameters=%d\nmlx=%p\nwin=%p\nmap=\n", var.size_x, var.size_y, var.f_color, var.c_color, var.no_path, var.so_path, var.we_path, var.ea_path, var.s_path, var.number, var.mlx, var.win);
        while (*var.map != 0)
            printf("%s\n", *(var.map++));
        background_test(&var, 'C', 0, 150, 255);
//        background_test(&var, 'F', 120, 120, 100);
        mlx_key_hook(var.win, pixel_trail, &var);
        mlx_loop(var.mlx);
    }
    return(0);
}