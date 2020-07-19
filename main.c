/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/19 19:01:06 by jabenjam         ###   ########.fr       */
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

int initialize_var(t_var *var)
{
    var->size_x = 0;
    var->size_y = 0;
    var->f_color = 0;
    var->c_color = 0;
    var->tex[0].path = 0;
    var->tex[1].path = 0;
    var->tex[2].path = 0;
    var->tex[3].path = 0;
    var->s_path = 0;
    var->number = 0;
    var->player.pos_x = 0.0;
    var->player.pos_y = 0.0;
    var->camera.dir_x = 0.0;
    var->camera.dir_y = 0.0;
    var->camera.delta_x = 0.0;
    var->camera.delta_y = 0.0;
    var->camera.plane_x = 0.0;
    var->camera.plane_y = 0.0;
    var->camera.cam_x = 0.0;
    return (0);
}

int initialize_ray(t_ray *ray)
{
    ray->hit = 0;
    ray->side = 0;
    ray->step_x = 0;
    ray->step_y = 0;
    ray->line_h = 0;
    ray->start = 0;
    ray->wall_x = 0;
    ray->tex_x = 0;
    ray->tex_y = 0;
    ray->tex_pos = 0;
    ray->step_t = 0;
    ray->end = 0;
    return (0);
}

int initialize_tex(t_var *var)
{
    int i;
    int bpp;
    int endian;
    int sl;

    i = 0;
    bpp = 32;
    endian = 0;
    while (i <= 3)
    {
        sl = var->tex[i].length * 4;
        var->tex[i].length = 64;
        var->tex[i].height = 64;
        var->tex[i].ptr = mlx_xpm_file_to_image(var->mlx, var->tex[i].path, &var->tex[i].length, &var->tex[i].height);
        var->tex[i].dat = mlx_get_data_addr(var->tex[i].ptr, &bpp, &sl, &endian);
        i++;
    }
    return (0);
}

int initialize_key(t_key *key)
{
    key->forward = 0;
    key->backward = 0;
    key->left = 0;
    key->right = 0;
    key->l_strafe = 0;
    key->r_strafe = 0;
    return (0);
}

int new_image(t_img *img, void *mlx, int length, int height)
{
    img->bpp = 32;
    img->sl = length * 4;
    img->end = 0;
    img->ptr = mlx_new_image(mlx, length, height);
    img->dat = mlx_get_data_addr(img->ptr, &img->bpp, &img->sl, &img->end);
    return (0);
}

int quit_game(t_var *var)
{
    mlx_destroy_window(var->mlx, var->win);
    exit(0);
}

int forback(t_var *var, int mode)
{
    if (mode == 1)
    {
        if (var->map[(int)var->player.pos_y][(int)(var->player.pos_x + var->camera.dir_x * 0.2)] != '1')
            var->player.pos_x += (var->camera.dir_x * 0.2);
        if (var->map[(int)(var->player.pos_y + var->camera.dir_y * 0.2)][(int)var->player.pos_x] != '1')
            var->player.pos_y += (var->camera.dir_y * 0.2);
    }
    else
    {
        if (var->map[(int)var->player.pos_y][(int)(var->player.pos_x - var->camera.dir_x * 0.2)] != '1')
            var->player.pos_x -= (var->camera.dir_x * 0.2);
        if (var->map[(int)(var->player.pos_y - var->camera.dir_y * 0.2)][(int)var->player.pos_x] != '1')
            var->player.pos_y -= (var->camera.dir_y * 0.2);
    }
    return (0);
}

int strafe(t_var *var, int mode)
{
    if (mode == 1)
    {
        if (var->map[(int)var->player.pos_y][(int)(var->player.pos_x - var->camera.plane_x * 0.2)] != '1')
            var->player.pos_x -= (var->camera.plane_x * 0.2);
        if (var->map[(int)(var->player.pos_y - var->camera.plane_y * 0.2)][(int)var->player.pos_x] != '1')
            var->player.pos_y -= (var->camera.plane_y * 0.2);
    }
    else
    {
        if (var->map[(int)var->player.pos_y][(int)(var->player.pos_x + var->camera.plane_x * 0.2)] != '1')
            var->player.pos_x += (var->camera.plane_x * 0.2);
        if (var->map[(int)(var->player.pos_y + var->camera.plane_y * 0.2)][(int)var->player.pos_x] != '1')
            var->player.pos_y += (var->camera.plane_y * 0.2);
    }
    return (0);
}

int look(t_var *var, int mode)
{
    double save_dir_x;
    double save_plane_x;

    save_dir_x = var->camera.dir_x;
    save_plane_x = var->camera.plane_x;
    if (mode == 1)
    {
        var->camera.dir_x = var->camera.dir_x * cos(0.1) - var->camera.dir_y * sin(0.1);
        var->camera.dir_y = save_dir_x * sin(0.1) + var->camera.dir_y * cos(0.1);
        var->camera.plane_x = var->camera.plane_x * cos(0.1) - var->camera.plane_y * sin(0.1);
        var->camera.plane_y = save_plane_x * sin(0.1) + var->camera.plane_y * cos(0.1);
    }
    else
    {
        var->camera.dir_x = var->camera.dir_x * cos(-0.1) - var->camera.dir_y * sin(-0.1);
        var->camera.dir_y = save_dir_x * sin(-0.1) + var->camera.dir_y * cos(-0.1);
        var->camera.plane_x = var->camera.plane_x * cos(-0.1) - var->camera.plane_y * sin(-0.1);
        var->camera.plane_y = save_plane_x * sin(-0.1) + var->camera.plane_y * cos(-0.1);
    }
    return (0);
}

void put_tiles(t_var *var, t_img *wall, t_img *pos, int size)
{
    int x;
    int y;
    int x_tile;
    int y_tile;

    x = -1;
    y = -1;
    x_tile = 0;
    y_tile = 0;
    while (var->map[++y])
    {
        while (var->map[y][++x])
        {
            if (var->map[y][x] == '1')
                mlx_put_image_to_window(var->mlx, var->win, wall->ptr,
                                        x_tile, y_tile);
            if (x == (int)var->player.pos_x && y == (int)var->player.pos_y)
                mlx_put_image_to_window(var->mlx, var->win, pos->ptr,
                                        x * (size + 1), y * (size + 1));
            x_tile += size + 1;
        }
        x = -1;
        x_tile = 0;
        y_tile += size + 1;
    }
}

/*
**  Mode == 0 ? tile mur;
**  Mode == 1 ? tile joueur;
*/
void create_tiles(t_img *tile, void *mlx, int size, int mode)
{
    int i;

    i = 0;
    new_image(tile, mlx, size, size);
    while (i < (size * size * 4))
    {
        tile->dat[i++] = (mode ? 0x64 : 0xC8); // B
        tile->dat[i++] = (mode ? 0xC8 : 0x80); // G
        tile->dat[i++] = 0x0;                  // R
        tile->dat[i++] = 0x0;                  // A
    }
}

int draw_mini_map(t_var *var, int size)
{
    t_img tile[2];
    t_img map;

    create_tiles(&tile[0], var->mlx, size, 0);
    create_tiles(&tile[1], var->mlx, size, 1);
    new_image(map, var->mlx, );// remplir une image au lieu de print tile par tile
    put_tiles(var, &tile[0], &tile[1], size);
    mlx_destroy_image(var->mlx, tile[0].ptr);
    mlx_destroy_image(var->mlx, tile[1].ptr);
    return (0);
}

int keys(t_var *var)
{
    if (var->key.forward == 1)
        forback(var, 1);
    if (var->key.backward == 1)
        forback(var, 0);
    if (var->key.l_strafe == 1)
        strafe(var, 1);
    if (var->key.r_strafe == 1)
        strafe(var, 0);
    if (var->key.left == 1)
        look(var, 1);
    if (var->key.right == 1)
        look(var, 0);
    if (var->key.map == 1)
        draw_mini_map(var, 8 + var->key.size);
    return (0);
}

int key_press(int key, t_var *var)
{
    if (key == K_ESC)
        quit_game(var);
    else if (key == K_W)
        var->key.forward = 1;
    else if (key == K_S)
        var->key.backward = 1;
    else if (key == K_RIGHT)
        var->key.left = 1;
    else if (key == K_LEFT)
        var->key.right = 1;
    else if (key == K_A)
        var->key.l_strafe = 1;
    else if (key == K_D)
        var->key.r_strafe = 1;
    else if (key == K_M)
        var->key.map = (var->key.map ? 0 : 1);
    else if (key == K_PLUS)
        var->key.size += (var->key.size < var->length / 400);
    else if (key == K_MINUS)
        var->key.size -= (var->key.size > -4);
    return (0);
}

int key_release(int key, t_var *var)
{
    if (key == K_W)
        var->key.forward = 0;
    else if (key == K_S)
        var->key.backward = 0;
    else if (key == K_RIGHT)
        var->key.left = 0;
    else if (key == K_LEFT)
        var->key.right = 0;
    else if (key == K_A)
        var->key.l_strafe = 0;
    else if (key == K_D)
        var->key.r_strafe = 0;
    return (0);
}

void get_window_size(t_var *var, char *line)
{
    int x;

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

char *get_path(char *line)
{
    char *path;

    while (line && *line == ' ')
        line++;
    path = ft_strdup(line);
    return (path);
}

int get_rgb(char *line)
{
    int rgb;
    int x;
    int colors;

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

void parse_direction(t_camera *camera, char c)
{
    if (c == 'N')
    {
        camera->dir_y = -1.0;
        camera->plane_x = 0.66;
    }
    else if (c == 'S')
    {
        camera->dir_y = 1.0;
        camera->plane_x = -0.66;
    }
    else if (c == 'E')
    {
        camera->dir_x = 1.0;
        camera->plane_y = 0.66;
    }
    else
    {
        camera->dir_x = -1.0;
        camera->plane_y = -0.66;
    }
}

void map_parser(t_var *var, char **params)
{
    int i;
    int j;

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
                var->player.pos_x = j + 0.5;
                var->player.pos_y = i + 0.5;
            }
            j++;
        }
        var->size_x = j;
        j = 0;
        i++;
    }
    var->size_y = i;
}

void cub_parser2(t_var *var, char *line)
{
    if (line && line[0] == 'R' && var->size_x == 0 && var->size_y == 0)
        get_window_size(var, ++line);
    else if (line && line[0] == 'F' && var->f_color == 0)
        var->f_color = get_rgb(++line);
    else if (line && line[0] == 'C' && var->c_color == 0)
        var->c_color = get_rgb(++line);
    else if (line && line[0] == 'N' && line[1] == 'O' && var->tex[2].path == 0)
        var->tex[2].path = get_path(2 + line);
    else if (line && line[0] == 'S' && line[1] == 'O' && var->tex[3].path == 0)
        var->tex[3].path = get_path(2 + line);
    else if (line && line[0] == 'W' && line[1] == 'E' && var->tex[0].path == 0)
        var->tex[0].path = get_path(2 + line);
    else if (line && line[0] == 'E' && line[1] == 'A' && var->tex[1].path == 0)
        var->tex[1].path = get_path(2 + line);
    else if (line && line[0] == 'S' && var->s_path == 0)
        var->s_path = get_path(++line);
}

void cub_parser(t_var *var, char *cub)
{
    int fd;
    int out;
    char **params;
    char buffer[4096];
    char *save;

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
    free(save);
    map_parser(var, params); // recuperation de la map
    close(fd);
    return;
}

void image_wall(t_var *var, t_ray *ray, int x)
{
    int i;
    int j;
    int tex_length;

    tex_length = var->tex[ray->side].length;
    while (ray->start <= ray->end && ray->end >= 0) // walls;
    {
        ray->tex_y = (int)ray->tex_pos & (tex_length - 1);
        i = ray->start * var->length * 4 + x * 4;
        j = ray->tex_y * tex_length * 4 + (tex_length - 1 - ray->tex_x) * 4;
        var->screen.dat[i++] = var->tex[ray->side].dat[j++]; // B
        var->screen.dat[i++] = var->tex[ray->side].dat[j++]; // G
        var->screen.dat[i++] = var->tex[ray->side].dat[j++]; // R
        var->screen.dat[i] = var->tex[ray->side].dat[j];     // A
        ray->start++;
        ray->tex_pos += ray->step_t;
    }
}

void image_fill(t_var *var, t_ray *ray, int x)
{
    int i = 0;
    int y = 0;
    while (y < ray->start) // ceiling
    {
        i = y * var->length * 4 + x * 4;
        var->screen.dat[i++] = 0x0;  // B
        var->screen.dat[i++] = 0x64; // G
        var->screen.dat[i++] = 0xFF; // R
        var->screen.dat[i] = 0;      // A
        y++;
    }
    image_wall(var, ray, x);
    while (ray->end < var->height && ray->end >= 0) // floor
    {
        i = ray->end * var->length * 4 + x * 4;
        var->screen.dat[i++] = 0x52; // B
        var->screen.dat[i++] = 0x35; // G
        var->screen.dat[i++] = 0x2c; // R
        var->screen.dat[i] = 0;      // A
        ray->end++;
    }
}

int texture_copy(t_var *var, t_ray *ray, int x)
{
    ray->step_t = 1.0 * var->tex[ray->side].height / ray->line_h;
    if (ray->side <= 1)
        ray->wall_x = var->player.pos_y + (ray->wall_dist * ray->dir_y);
    else
        ray->wall_x = var->player.pos_x + (ray->wall_dist * ray->dir_x);
    //printf("\nray->wall_x=%f\nvar->player.pos_y=%f\nvar->player.pos_x=%f\nray->wall_dist=%f\nray->dir_y=%f\nray->dir_x=%f\n",ray->wall_x,var->player.pos_y,var->player.pos_x,ray->wall_dist,ray->dir_y,ray->dir_x);
    ray->wall_x -= floor(ray->wall_x);
    //printf("\nray->wall_x=%f\n", ray->wall_x);
    ray->tex_x = (int)(ray->wall_x * (double)var->tex[ray->side].length);
    if ((ray->side <= 1 && ray->dir_x > 0) ||
        (ray->side >= 2 && ray->dir_y < 0))
        ray->tex_x = var->tex[ray->side].length - ray->tex_x - 1;
    ray->tex_pos = (ray->start - var->height / 2 + ray->line_h / 2) * ray->step_t;
    image_fill(var, ray, x);
    return (0);
}

void raycast_scale(t_var *var, t_ray *ray)
{
    if (ray->side <= 1)
        ray->wall_dist = (ray->map_x - var->player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->wall_dist = (ray->map_y - var->player.pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
    ray->line_h = (int)(var->height / ray->wall_dist);
    ray->start = -ray->line_h / 2 + var->height / 2;
    ray->start = (ray->start < 0 ? 0 : ray->start);
    ray->end = ray->line_h / 2 + var->height / 2;
    ray->end = (ray->end >= var->height ? var->height - 1 : ray->end);
}

void raycast_cast(t_var *var, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_x < ray->side_y)
        {
            ray->side_x += var->camera.delta_x;
            ray->map_x += ray->step_x;
            ray->side = (ray->step_x == -1 ? 0 : 1);
        }
        else
        {
            ray->side_y += var->camera.delta_y;
            ray->map_y += ray->step_y;
            ray->side = (ray->step_y == -1 ? 2 : 3);
        }
        //printf("\nray->map_x=%d\nray->map_y=%d\n", ray->map_x,ray->map_y);
        if (ray->map_x < var->size_x && ray->map_y < var->size_y && var->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void raycast_step(t_var *var, t_ray *ray)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_x = (var->player.pos_x - ray->map_x) * var->camera.delta_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_x = (ray->map_x + 1.0 - var->player.pos_x) * var->camera.delta_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_y = (var->player.pos_y - ray->map_y) * var->camera.delta_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_y = (ray->map_y + 1 - var->player.pos_y) * var->camera.delta_y;
    }
}

void raycast_setup(t_var *var, t_ray *ray, int x)
{
    var->camera.cam_x = (2 * x) / (double)var->length - 1;
    ray->dir_x = var->camera.dir_x + var->camera.plane_x * var->camera.cam_x;
    ray->dir_y = var->camera.dir_y + var->camera.plane_y * var->camera.cam_x;
    ray->map_x = (int)var->player.pos_x; // determine la case dans laquelle se trouve la camera
    ray->map_y = (int)var->player.pos_y;
    var->camera.delta_x = fabs(1 / ray->dir_x);
    var->camera.delta_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
}

int raycast(t_var *var, t_ray *ray)
{
    int x;
    double zbuffer[var->length];

    x = 0;
    while (x < var->length)
    {
        raycast_setup(var, ray, x);
        raycast_step(var, ray);
        raycast_cast(var, ray);
        raycast_scale(var, ray);
        //printf("\n\nvar->camera.cam_x=%f\nray->dir_x=%f\nray->dir_y=%f\nray->map_x=%d\nray->map_y=%d\nvar->camera.delta_x=%f\nvar->camera.delta_y=%f\n",var->camera.cam_x,ray->dir_x,ray->dir_y,ray->map_x,ray->map_y,var->camera.delta_x,var->camera.delta_y);
        //printf("ray->side_x=%f\nray->side_y=%f\n", ray->side_x,ray->side_y);
        zbuffer[x] = ray->wall_dist;
        texture_copy(var, ray, x++);
    }
    //printf("\nwall_dist = %f\nline_h = %d\nstart = %d\nend = %d\n", ray->wall_dist, ray->line_h, ray->start, ray->end);
    return (0);
}

int game(t_var *var)
{
    t_ray ray;
    initialize_ray(&ray);
    initialize_tex(var);
    new_image(&var->screen, var->mlx, var->length, var->height);
    raycast(var, &ray);
    mlx_put_image_to_window(var->mlx, var->win, var->screen.ptr, 0, 0);
    mlx_destroy_image(var->mlx, var->screen.ptr);
    //draw_mini_map(var, 8 + var->key.size);
    keys(var);
    return (0);
}

int main(int ac, char **av)
{
    t_var var;

    initialize_var(&var);
    if (ac == 2 || ac == 3)
    {
        // ajouter verification d'erreurs dans les arguments [if (a || b)]
        cub_parser(&var, av[1]);
        var.mlx = mlx_init();
        var.win = mlx_new_window(var.mlx, var.length, var.height, "Cub3D");
        //        printf("VARS\nlength=%d\nheight=%d\nf_color=%d\nc_color=%d\nno_path=%s\nso_path=%s\nwe_path=%s\nea_path=%s\ns_path=%s\nnumber of parameters=%d\nmlx=%p\nwin=%p\nmap=\n", var.length, var.height, var.f_color, var.c_color, var.tex[0].path, var.tex[1].path, var.tex[2].path, var.tex[3].path, var.s_path, var.number, var.mlx, var.win);
        //        printf("PLAYER\npos_x=%f\npos_y=%f\ndir_x=%f\ndir_y=%f\n", var.player.pos_x, var.player.pos_y, var.camera.dir_x, var.camera.dir_y);
        mlx_hook(var.win, 2, 0, key_press, &var);
        mlx_hook(var.win, 3, 0, key_release, &var);
        mlx_loop_hook(var.mlx, game, &var);
        mlx_loop(var.mlx);
    }
    return (0);
}