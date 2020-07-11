/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/11 18:56:40 by jabenjam         ###   ########.fr       */
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
    var->camera.map_x = 0;
    var->camera.map_y = 0;
    var->player.pos_x = 0;
    var->player.pos_y = 0;
    var->camera.dir_x = 0;
    var->camera.dir_y = 0;
    var->camera.delta_x = 0;
    var->camera.delta_y = 0;
    var->camera.plane_x = 0;
    var->camera.plane_y = 0.66;
    var->camera.cam_x = 0;
    var->camera.wall_dist = 0;
    var->camera.side_x = 0;
    var->camera.side_y = 0;
    var->camera.map_x = 0;
    var->camera.map_y = 0;
}

void    intitialize_ray(t_rayc *rayc)
{
    rayc->hit = 0;
    rayc->side = 0;
    rayc->step_x = 0;
    rayc->step_y = 0;
    rayc->line_h = 0;
    rayc->start = 0;
    rayc->end = 0;
}

void    get_window_size(t_var *var, char *line)
{
    int     x;

    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9' && *line != ' ')
        x = (x * 10) + (*(line++) - '0');
    var->length = x;
    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9')
        x = (x * 10) + (*(line++) - '0');
    var->height = x;
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

void    parse_direction(t_camera *camera, char c)
{
    if (c == 'N')
        camera->dir_y = -1;
    else if (c == 'S')
        camera->dir_y = 1;
    else if (c == 'E')
        camera->dir_x = 1;
    else
        camera->dir_x = -1;
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
                parse_direction(&var->camera, var->map[i][j]);
                var->player.pos_x = j;
                var->player.pos_y = i;
            }
            j++;
        }
        var->size_x = j;
        j = 0;
        i++;
    }
    var->size_y = i;
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

void    image_fill(t_var *var, int x, int start, int end)
{
    int i = 0;
    //printf("\nx=%d\nstart=%d\nend=%d\ni=%d\nj=%d\n", x, start, end, i, j);

    while (start <= end && end >= 0)
    {
        i = x + var->tex.sl * start;
        var->tex.dat[i++] = 127;
        var->tex.dat[i++] = 127;
        var->tex.dat[i++] = 127;
        var->tex.dat[i++] = 127;
        start++;
    }
}

int     new_image(t_var *var)
{
    var->tex.x = 0;
    var->tex.y = 0;
    var->tex.bpp = 32;
    var->tex.sl = var->length * 4;
    var->tex.end = 1;
    var->tex.ptr = mlx_new_image(var->mlx, var->length, var->height);
    var->tex.dat = mlx_get_data_addr(var->tex.ptr, &var->tex.bpp, &var->tex.sl, &var->tex.end);
    return (0);
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

int     draw_vline(t_var *var, int x, int start, int end, int color)
{
    int     i = 0;

    while (start + i < end)
    {
        mlx_pixel_put(var->mlx, var->win, x, start + i, color);
        i++;
    }
    return (0);
}

int     raycast(t_var *var, t_rayc *rayc)
{
    int     color = 45350912;
    int     x = 0;
    while (x < var->length)
    {
        var->camera.cam_x = 2 * x / (double)var->length - 1;
        var->camera.ray_dirx = var->camera.dir_x + var->camera.plane_x * var->camera.cam_x;
        var->camera.ray_diry = var->camera.dir_y + var->camera.plane_y * var->camera.cam_x;
        var->camera.map_x = (int)var->player.pos_x; // determine la case dans laquelle se trouve la camera
        var->camera.map_y = (int)var->player.pos_y;
        var->camera.delta_x = fabs(1 / var->camera.ray_dirx);
        var->camera.delta_y = fabs(1 / var->camera.ray_diry);
        if (var->camera.ray_dirx < 0)
        {
            rayc->step_x = -1;
            var->camera.side_x = (var->player.pos_x - var->camera.map_x) * var->camera.delta_x;
        }
        else
        {
            rayc->step_x = 1;
            var->camera.side_x = (var->camera.map_x + 1 - var->player.pos_x) * var->camera.delta_x;
        }
        if (var->camera.ray_diry < 0)
        {
            rayc->step_y = -1;
            var->camera.side_y = (var->player.pos_y - var->camera.map_y) * var->camera.delta_y;
        }
        else
        {
            rayc->step_y = 1;
            var->camera.side_y = (var->camera.map_y + 1 - var->player.pos_y) * var->camera.delta_y;
        }
        rayc->hit = 0;
        while (rayc->hit == 0)
        {
            if (var->camera.side_x < var->camera.side_y)
            {
                var->camera.side_x += var->camera.delta_x;
                var->camera.map_x += rayc->step_x;
                rayc->side = 0;
            }
            else
            {
                var->camera.side_y += var->camera.delta_y;
                var->camera.map_y += rayc->step_y;
                rayc->side = 1;
            }
            //printf("\nvar->camera.map_x=%d\nvar->camera.map_y=%d\n", var->camera.map_x,var->camera.map_y);
            if (var->camera.map_x < var->size_x && var->camera.map_y < var->size_y && var->map[var->camera.map_y][var->camera.map_x] > 0)
                rayc->hit = 1;
        }
        if (rayc->side == 0)
            var->camera.wall_dist = (var->camera.map_x - var->player.pos_x + (1 - rayc->step_x) / 2) / var->camera.ray_dirx;
        else
            var->camera.wall_dist = (var->camera.map_y - var->player.pos_y + (1 - rayc->step_y) / 2) / var->camera.ray_diry;
        rayc->line_h = (int)(var->height / var->camera.wall_dist);
        rayc->start = -rayc->line_h / 2 + var->height / 2;
        rayc->start = (rayc->start < 0 ? 0 : rayc->start);
        rayc->end = rayc->line_h / 2 + var->height / 2;
        rayc->end = (rayc->end >= var->height ? var->height - 1 : rayc->end);
        color = (rayc->side == 1 ? 22806528 : color); // attenuer la couleur si c'est un coté
        //printf("\nwall_dist = %f\nline_h = %d\nstart = %d\n, end = %d\n", var->camera.wall_dist, rayc->line_h, rayc->start, rayc->end);
        image_fill(var, x, rayc->start, rayc->end);
        //draw_vline(var, x, rayc->start, rayc->end, color);
        x++;
    }
    mlx_put_image_to_window(var->mlx, var->win, var->tex.ptr, 0, 0);
//    draw_mini_map(var);
    return (0);
}

int     engine(t_var *var)
{
    t_rayc  rayc;
    intitialize_ray(&rayc);
    new_image(var);
    raycast(var, &rayc);
    return (0);
}

int     draw(t_var *var)
{
    draw_mini_map(var);
    return (0);
}

int     key_press(int key, t_var *var) // TEST //
{
//   printf("\nkey = %d\n", key);
    float     save_dir_x = 0;
    float     save_plane_x = 0;

    if (key == K_W)
    {
        var->player.pos_x += (var->camera.dir_x * 0.1);
        var->player.pos_y += (var->camera.dir_y * 0.1);
    }
    else if (key == K_S)
    {
        var->player.pos_x -= (var->camera.dir_x * 0.1);
        var->player.pos_y -= (var->camera.dir_y * 0.1);
    }
    else if (key == K_RIGHT)
    {
        save_dir_x = var->camera.dir_x;
        save_plane_x = var->camera.plane_x;
        var->camera.dir_x = var->camera.dir_x * cos(0.1) - var->camera.dir_y * sin(0.1);
        var->camera.dir_y = save_dir_x * sin(0.1) + var->camera.dir_y * cos(0.1);
        var->camera.plane_x = var->camera.plane_x * cos(0.1) - var->camera.plane_y * sin(0.1);
        var->camera.plane_y = save_plane_x * sin(0.1) + var->camera.dir_y * cos(0.1);
    }
    else if (key == K_LEFT)
    {
        save_dir_x = var->camera.dir_x;
        save_plane_x = var->camera.plane_x;
        var->camera.dir_x = var->camera.dir_x * cos(-0.1) - var->camera.dir_y * sin(-0.1);
        var->camera.dir_y = save_dir_x * sin(-0.1) + var->camera.dir_y * cos(-0.1);
        var->camera.plane_x = var->camera.plane_x * cos(-0.1) - var->camera.plane_y * sin(-0.1);
        var->camera.plane_y = save_plane_x * sin(-0.1) + var->camera.dir_y * cos(-0.1);
    }
    else if (key == K_R)
    {
        mlx_clear_window(var->mlx, var->win);
        mlx_string_put(var->mlx, var->win, 0, 10, 0255255000, "PRESS W/LEFT/S/RIGHT TO MOVE");
    }
//    draw_mini_map(var);
    engine(var);
    if (key == K_ESC) // ESC
        mlx_destroy_window(var->mlx, var->win);
//    printf("PLAYER\npos_x=%f\npos_y=%f\ndir_x=%f\ndir_y=%f\n", var->player.pos_x, var->player.pos_y, var->camera.dir_x, var->camera.dir_y);
    return (0);
}

/*int     draw_pixel(t_var *var, int x, int y, int color)
{
    if (x >= 0 && x <= var->length && y >= 0 && y <= var->height)
        *(int*)(var->win + ((4 * var->length * y) + (x * 4))) = color;
    return (0);
}*/

int     main(int ac, char **av)
{
        t_var       var;

    initialize_structs(&var);
    if (ac == 2 || ac == 3)
    {
        // ajouter verification d'erreurs dans les arguments [if (a || b)]
        cub_parser(&var, av[1]);
        var.mlx = mlx_init();
        var.win = mlx_new_window(var.mlx, var.length, var.height, "Cub3D");
        printf("VARS\nlength=%d\nheight=%d\nf_color=%d\nc_color=%d\nno_path=%s\nso_path=%s\nwe_path=%s\nea_path=%s\ns_path=%s\nnumber of parameters=%d\nmlx=%p\nwin=%p\nmap=\n", var.length, var.height, var.f_color, var.c_color, var.no_path, var.so_path, var.we_path, var.ea_path, var.s_path, var.number, var.mlx, var.win);
        printf("PLAYER\npos_x=%f\npos_y=%f\ndir_x=%f\ndir_y=%f\n", var.player.pos_x, var.player.pos_y, var.camera.dir_x, var.camera.dir_y);
//        background_fill_test(&var, 'C', 0, 255, 255);
//        background_fill_test(&var, 'F', 120, 120, 100);
//        mlx_put_image_to_window(var.mlx, var.win, mlx_xpm_file_to_image(var.mlx, var.no_path, &x, &y), 0, 0);
//        mlx_put_image_to_window(var.mlx, var.win, mlx_xpm_file_to_image(var.mlx, var.so_path, &x, &y), 64, 0);
//        mlx_loop_hook(var.mlx, engine, &var);
        mlx_hook(var.win, 2, 0, key_press, &var);
//        mlx_hook(var.win, 2, 0, key_release, &var);
        mlx_loop(var.mlx);
    }
    return(0);
}