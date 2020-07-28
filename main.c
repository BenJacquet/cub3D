/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/28 14:56:33 by jabenjam         ###   ########.fr       */
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

void close_game(t_var *var, char *error)
{
    void *current;

    while (var->sprites)
    {
        current = var->sprites;
        var->sprites = var->sprites->next;
        free(current);
    }
    if (*error != '\0')
    {
        ft_putstr_fd("Error : ", 2);
        ft_putstr_fd(error, 2);
    }
    while (var->map && *var->map)
        free(*var->map++);
    if (var->mlx)
        mlx_destroy_window(var->mlx, var->win);
    exit(0);
}

int check_parameters(t_var *var)
{
    if (var->number != 8 || var->width == 0 || var->height == 0 ||
        var->f_color == 0 || var->c_color == 0 || var->tex[0].path == 0 ||
        var->tex[1].path == 0 || var->tex[2].path == 0 ||
        var->tex[3].path == 0 || var->s_path == 0)
    {
        close_game(var, "Invalid map.");
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
        close_game(var, "File is invalid");
    else if (mode == 2)
        close_game(var, "Flag must be \"--save\".");
    return (1);
}

void initialize_var(t_var *var)
{
    var->width = 0;
    var->height = 0;
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
    var->save = 0;
    var->n_sprites = 0;
    var->player.pos_x = 0.0;
    var->player.pos_y = 0.0;
    var->cam.dir_x = 0.0;
    var->cam.dir_y = 0.0;
    var->cam.delta_x = 0.0;
    var->cam.delta_y = 0.0;
    var->cam.plane_x = 0.0;
    var->cam.plane_y = 0.0;
    var->cam.cam_x = 0.0;
}

void initialize_ray(t_ray *ray)
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
}

void initialize_tex(t_var *var)
{
    int i;
    int bpp;
    int endian;
    int sl;
    int fd;

    i = 0;
    bpp = 32;
    endian = 0;
    while (i <= 3)
    {
        check_argument(var, var->tex[i].path, ".xpm", 1);
        if ((fd = open(var->tex[i].path, O_RDONLY) == -1))
        {
            close(fd);
            close_game(var, "File is invalid");
        }
        close(fd);
        sl = var->tex[i].width * 4;
        var->tex[i].width = 64;
        var->tex[i].height = 64;
        var->tex[i].ptr = mlx_xpm_file_to_image(var->mlx, var->tex[i].path, &var->tex[i].width, &var->tex[i].height);
        var->tex[i].dat = mlx_get_data_addr(var->tex[i].ptr, &bpp, &sl, &endian);
        i++;
    }
}

void initialize_sprite(t_var *var, t_sprite *sprite)
{
    int bpp;
    int endian;
    int fd;

    sprite->width = 64;
    sprite->height = 64;
    sprite->sl = sprite->width * 4;
    bpp = 32;
    endian = 0;
    check_argument(var, var->s_path, ".xpm", 1);
    if ((fd = open(var->s_path, O_RDONLY) == -1))
    {
        close(fd);
        close_game(var, "File is invalid");
    }
    close(fd);
    sprite->ptr = mlx_xpm_file_to_image(var->mlx, var->s_path, &sprite->width, &sprite->height);
    sprite->dat = mlx_get_data_addr(sprite->ptr, &bpp, &sprite->sl, &endian);
}

void initialize_key(t_key *key)
{
    key->forward = 0;
    key->backward = 0;
    key->left = 0;
    key->right = 0;
    key->l_strafe = 0;
    key->r_strafe = 0;
}

void create_image(t_img *img, void *mlx, int width, int height)
{
    img->bpp = 32;
    img->sl = width * 4;
    img->end = 0;
    img->ptr = mlx_new_image(mlx, width, height);
    img->dat = mlx_get_data_addr(img->ptr, &img->bpp, &img->sl, &img->end);
}

void fill_bmp(int fd, t_var *var)
{
    int i;
    i = 0;
    // MISE A ZERO DES DONNEES INUTILES ICI
    while (i < 3)
    {
        write(fd, "\0\0\0\0\0\0\0\0", 8);
        i++;
    }
    // REMPLISSAGE DU TABLEAU DE PIXELS
    i = 0;
    while (var->height >= 0)
    {
        i = var->width * 4 * var->height;
        write(fd, &var->screen.dat[i], var->width * 4); // Copie de l'image ligne par ligne
        var->height--;
    }
}

void create_bmp(t_var *var)
{
    int fd;
    int size;
    int array;
    int header_size;
    int color_plane;

    fd = open("Cub3D.bmp", O_CREAT | O_RDWR);
    size = 54 + (var->width * var->height * 4);
    array = 54;
    header_size = 40;
    color_plane = 1;
    //BMP HEADER
    write(fd, "BM", 2);       // Identificateur
    write(fd, &size, 4);      // Taille du fichier
    write(fd, "\0\0\0\0", 4); // Reserve a l'application qui genere le fichier
    write(fd, &array, 4);     // Debut du tableau de pixels
    // DIB HEADER
    write(fd, &header_size, 4);     // Taille du header DIB
    write(fd, &var->width, 4);      // Largeur de l'image
    write(fd, &var->height, 4);     // Hauteur de l'image
    write(fd, &color_plane, 2);     // Nombre de plans de couleurs
    write(fd, &var->screen.bpp, 2); // Bits par pixel
    fill_bmp(fd, var);
    close(fd);
    close_game(var, "");
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
    create_image(tile, mlx, size, size);
    while (i < (size * size * 4))
    {
        tile->dat[i++] = (mode ? 0x64 : 0xFF); // B
        tile->dat[i++] = (mode ? 0x64 : 0xFF); // G
        tile->dat[i++] = (mode ? 0x0 : 0xFF);  // R
        tile->dat[i++] = 0x0;                  // A
    }
}

int draw_mini_map(t_var *var, int size)
{
    t_img tile[2];

    create_tiles(&tile[0], var->mlx, size, 0);
    create_tiles(&tile[1], var->mlx, size, 1);
    put_tiles(var, &tile[0], &tile[1], size);
    mlx_destroy_image(var->mlx, tile[0].ptr);
    mlx_destroy_image(var->mlx, tile[1].ptr);
    return (0);
}

int check_oob(t_var *var)
{
    if (var->player.pos_x + var->cam.dir_x * 0.1 <= 1 ||
        var->player.pos_y + var->cam.dir_y * 0.1 <= 1)
        return (1);
    if (var->player.pos_x + var->cam.dir_x * 0.1 >= var->size_x - 1 ||
        var->player.pos_y + var->cam.dir_y * 0.1 >= var->size_y - 1)
        return (1);
    if (var->player.pos_x - var->cam.dir_x * 0.1 <= 1 ||
        var->player.pos_y - var->cam.dir_y * 0.1 <= 1)
        return (1);
    if (var->player.pos_x - var->cam.dir_x * 0.1 >= var->size_x - 1 ||
        var->player.pos_y - var->cam.dir_y * 0.1 >= var->size_y - 1)
        return (1);
    if (var->player.pos_x + var->cam.plane_x * 0.1 <= 1 ||
        var->player.pos_y + var->cam.plane_y * 0.1 <= 1)
        return (1);
    if (var->player.pos_x + var->cam.plane_x * 0.1 >= var->size_x - 1 ||
        var->player.pos_y + var->cam.plane_y * 0.1 >= var->size_y - 1)
        return (1);
    if (var->player.pos_x - var->cam.plane_x * 0.1 <= 1 ||
        var->player.pos_y - var->cam.plane_y * 0.1 <= 1)
        return (1);
    if (var->player.pos_x - var->cam.plane_x * 0.1 >= var->size_x - 1 ||
        var->player.pos_y - var->cam.plane_y * 0.1 >= var->size_y - 1)
        return (1);
    return (0);
}

int forback(t_var *var, int mode)
{
    /*    if (check_oob(var))
        close_game(var, "Out of map limits");*/
    if (mode == 1)
    {
        if (var->map[(int)var->player.pos_y]
                    [(int)(var->player.pos_x + var->cam.dir_x * 0.1)] != '1')
            var->player.pos_x += (var->cam.dir_x * 0.1);
        if (var->map[(int)(var->player.pos_y + var->cam.dir_y * 0.1)]
                    [(int)var->player.pos_x] != '1')
            var->player.pos_y += (var->cam.dir_y * 0.1);
    }
    else
    {
        if (var->map[(int)var->player.pos_y]
                    [(int)(var->player.pos_x - var->cam.dir_x * 0.1)] != '1')
            var->player.pos_x -= (var->cam.dir_x * 0.1);
        if (var->map[(int)(var->player.pos_y - var->cam.dir_y * 0.1)]
                    [(int)var->player.pos_x] != '1')
            var->player.pos_y -= (var->cam.dir_y * 0.1);
    }
    return (0);
}

int strafe(t_var *var, int mode)
{
    /*    if (check_oob(var))
        close_game(var, "Out of map limits");*/
    if (mode == 3)
    {
        if (var->map[(int)var->player.pos_y]
                    [(int)(var->player.pos_x - var->cam.plane_x * 0.1)] != '1')
            var->player.pos_x -= (var->cam.plane_x * 0.1);
        if (var->map[(int)(var->player.pos_y - var->cam.plane_y * 0.1)]
                    [(int)var->player.pos_x] != '1')
            var->player.pos_y -= (var->cam.plane_y * 0.1);
    }
    else
    {
        if (var->map[(int)var->player.pos_y]
                    [(int)(var->player.pos_x + var->cam.plane_x * 0.1)] != '1')
            var->player.pos_x += (var->cam.plane_x * 0.1);
        if (var->map[(int)(var->player.pos_y + var->cam.plane_y * 0.1)]
                    [(int)var->player.pos_x] != '1')
            var->player.pos_y += (var->cam.plane_y * 0.1);
    }
    return (0);
}

int look(t_cam *cam, int mode)
{
    double save_dir_x;
    double save_plane_x;

    save_dir_x = cam->dir_x;
    save_plane_x = cam->plane_x;
    if (mode == 1)
    {
        cam->dir_x = cam->dir_x * cos(0.1) - cam->dir_y * sin(0.1);
        cam->dir_y = save_dir_x * sin(0.1) + cam->dir_y * cos(0.1);
        cam->plane_x = cam->plane_x * cos(0.1) - cam->plane_y * sin(0.1);
        cam->plane_y = save_plane_x * sin(0.1) + cam->plane_y * cos(0.1);
    }
    else
    {
        cam->dir_x = cam->dir_x * cos(-0.1) - cam->dir_y * sin(-0.1);
        cam->dir_y = save_dir_x * sin(-0.1) + cam->dir_y * cos(-0.1);
        cam->plane_x = cam->plane_x * cos(-0.1) - cam->plane_y * sin(-0.1);
        cam->plane_y = save_plane_x * sin(-0.1) + cam->plane_y * cos(-0.1);
    }
    return (0);
}


int keys(t_var *var)
{
    if (var->key.forward == 1)
        forback(var, 1);
    if (var->key.backward == 1)
        forback(var, 0);
    if (var->key.l_strafe == 1)
        strafe(var, 3);
    if (var->key.r_strafe == 1)
        strafe(var, 2);
    if (var->key.left == 1)
        look(&var->cam, 1);
    if (var->key.right == 1)
        look(&var->cam, 0);
    if (var->key.map == 1)
        draw_mini_map(var, 8 + var->key.size);
    return (0);
}

int key_press(int key, t_var *var)
{
    if (key == K_ESC)
        close_game(var, "");
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
        var->key.size += (var->key.size < var->width / 400);
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

int close_window(t_var *var)
{
    close_game(var, "");
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
    var->width = (x > 2560 ? 2560 : x);
    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9')
        x = (x * 10) + (*(line++) - '0');
    var->height = (x > 1440 ? 1440 : x);
    if (var->height <= 0 || var->width <= 0)
        close_game(var, "Resolution must be higher than 0.");
}

char *get_path(char *line)
{
    char *path;

    while (line && *line == ' ')
        line++;
    path = ft_strdup(line);
    return (path);
}

int get_rgb(t_var *var, char *line)
{
    int rgb;
    int x;
    int colors;

    rgb = 0;
    x = 0;
    colors = 0;
    while (line && *line == ' ')
        line++;
    while (line)
    {
        if (*line == '-')
            x = -1;
        while (*line >= '0' && *line <= '9')
            x = (x * 10) + (*(line++) - '0');
        if (x < 0 || x > 255)
            close_game(var, "Color must be between 0 and 255.");
        rgb = (colors++ == 0 ? rgb = x : (rgb << 8) + x);
        if (*(line++) != ',')
            break;
        x = 0;
    }
    if (colors != 3)
        close_game(var, "Color must contain 3 numbers separated by comas.");
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
            close_game(var, "Player position specified more than once");
        var->player.pos_x = x + 0.5;
        var->player.pos_y = y + 0.5;
    }
    return (0);
}

t_sprite *store_sprite(t_var *var, int x, int y)
{
    t_sprite *new;

    if (!(new = malloc(sizeof(t_sprite))))
        return (NULL);
    new->x = x;
    new->y = y;
    new->dist = 0.0;
    new->next = (var->sprites ? var->sprites : NULL);
    if (var->sprites)
        new->next = var->sprites;
    var->n_sprites++;
    return (new);
}

void get_distance(t_sprite *sprites, t_player *player)
{
    t_sprite *head;

    head = sprites;
    while (sprites)
    {
        sprites->dist =
            ((player->pos_x - sprites->x) * (player->pos_x - sprites->x) +
             (player->pos_y - sprites->y) * (player->pos_y - sprites->y));
        sprites = sprites->next;
    }
    sprites = head;
}

void swap_content(t_sprite *current, t_sprite *next)
{
    float temp;

    temp = 0;
    if (current && next)
    {
        temp = current->x;
        current->x = next->x;
        next->x = temp;
        temp = current->y;
        current->y = next->y;
        next->y = temp;
        temp = current->dist;
        current->dist = next->dist;
        next->dist = temp;
    }
}

t_sprite *sort_sprites(t_sprite *sprites)
{
    t_sprite *head;
    t_sprite *next;

    head = sprites;
    while (sprites && sprites->next)
    {
        next = sprites->next;
        if (sprites->dist < next->dist)
            swap_content(sprites, next);
        sprites = sprites->next;
    }
    return (head);
}

int raycast_sprites(t_var *var, double *zbuffer)
{
    double x;
    double y;
    t_sprite *head;
    t_ray_s ray_s;

    head = var->sprites;
    initialize_sprite(var, head);
    while (var->sprites)
    {
        x = var->sprites->x - (var->player.pos_x - 0.5);
        y = var->sprites->y - (var->player.pos_y - 0.5);
        ray_s.inv = 1.0 / (var->cam.plane_x * var->cam.dir_y -
                           var->cam.dir_x * var->cam.plane_y);
        ray_s.x = ray_s.inv * (var->cam.dir_y * x - var->cam.dir_x * y);
        ray_s.y = ray_s.inv * (-var->cam.plane_y * x + var->cam.plane_x * y);
        ray_s.x_screen = (int)((var->width / 2) * (1 + ray_s.x / ray_s.y));
        ray_s.height = abs((int)(var->height / ray_s.y));
        /*calcul de la longueur du sprite a afficher*/
        ray_s.start_y = -ray_s.height / 2 + var->height / 2;
        ray_s.start_y = (ray_s.start_y < 0 ? 0 : ray_s.start_y);
        ray_s.end_y = ray_s.height / 2 + var->height / 2;
        ray_s.end_y = (ray_s.end_y >= var->height ? var->height - 1 : ray_s.end_y);
        /*calcul de la largeur du sprite a afficher*/
        ray_s.width = abs((int)(var->height / ray_s.y));
        ray_s.start_x = -ray_s.width / 2 + ray_s.x_screen;
        ray_s.start_x = (ray_s.start_x < 0 ? 0 : ray_s.start_x);
        ray_s.end_x = ray_s.width / 2 + ray_s.x_screen;
        ray_s.end_x = (ray_s.end_x >= var->width ? var->width - 1 : ray_s.end_x);
        int stripe = ray_s.start_x;
        while (stripe < ray_s.end_x)
        {
            ray_s.tex_x = (int)((head->width * 4) * (stripe - (-ray_s.width / 2 + ray_s.x_screen)) *
                                head->width / ray_s.width) /
                          (head->width * 4);
            if (ray_s.y > 0 && stripe > 0 &&
                stripe < var->width && ray_s.y < zbuffer[stripe])
            {
                int start = ray_s.start_y;
                while (start < ray_s.end_y)
                {
                    ray_s.d = start * (head->width * 4) - var->height * (head->width * 4 / 2) +
                              ray_s.height * (head->width * 4) / 2;
                    ray_s.tex_y = ((ray_s.d * head->height) / ray_s.height / (head->width * 4));
                    int i = start * (var->width * 4) + (stripe * 4);
                    int j = ray_s.tex_y * (head->width * 4) + (ray_s.tex_x * 4);
                    if (head->dat[j] + head->dat[j + 1] + head->dat[j + 2] + head->dat[j + 3] != 0x0)
                    {
                        var->screen.dat[i++] = head->dat[j++]; // B
                        var->screen.dat[i++] = head->dat[j++]; // G
                        var->screen.dat[i++] = head->dat[j++]; // R
                        var->screen.dat[i] = head->dat[j];     // A
                    }
                    start++;
                }
            }
            stripe++;
        }
        var->sprites = var->sprites->next;
    }
    var->sprites = head;
    return (0);
}

int sprites_manager(t_var *var, double *zbuffer)
{
    get_distance(var->sprites, &var->player);
    var->sprites = sort_sprites(var->sprites);
    raycast_sprites(var, zbuffer);
    return (0);
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
                close_game(var, "Map can only contain 0 1 2 N S W E.");
            else if ((x == 0 && var->map[y][x] == '0') ||
                     (x == var->size_x - 1 && var->map[y][x] == '0') ||
                     (y == 0 && var->map[y][x] == '0') ||
                     (y == var->size_y - 1 && var->map[y][x] == '0'))
                close_game(var, "Map is not closed, check the edges.");
        }
        x = -1;
    }
    if (!var->player.pos_x && !var->player.pos_y)
        close_game(var, "Player position must be specified.");
    if (!(var->player.pos_x >= 1 && var->player.pos_x <= var->size_x - 1) ||
        !(var->player.pos_y >= 1 && var->player.pos_y <= var->size_x - 1))
        close_game(var, "Player cannot be placed on map edge.");
}

void map_parser(t_var *var, char **params)
{
    int y;
    int x;

    y = -1;
    x = -1;
    var->map = params;
    while (var->map[++y] != 0)
    {
        while (var->map[y][++x] != '\0')
        {
            if (var->map[y][x] == ' ')
                var->map[y][x] = '1';
            if (var->map[y][x] == '2')
                var->sprites = store_sprite(var, x, y);
            parse_player(var, x, y);
        }
        if (var->size_x != 0 && var->size_x != x)
            close_game(var, "Invalid map.");
        var->size_x = x;
        x = -1;
    }
    var->size_y = y;
    check_map(var);
}

int cub_parser2(t_var *var, char *line)
{
    if (line && line[0] == 'R' && var->width == 0 && var->height == 0)
        get_window_size(var, ++line);
    else if (line && line[0] == 'F' && var->f_color == 0)
        var->f_color = get_rgb(var, ++line);
    else if (line && line[0] == 'C' && var->c_color == 0)
        var->c_color = get_rgb(var, ++line);
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
    map_parser(var, params); // recuperation de la map
    close(fd);
}

void image_wall(t_var *var, t_ray *ray, int x)
{
    int i;
    int j;
    int tex_width;

    tex_width = var->tex[ray->side].width;
    while (ray->start <= ray->end && ray->end >= 0) // walls;
    {
        ray->tex_y = (int)ray->tex_pos & (tex_width - 1);
        i = ray->start * var->width * 4 + x * 4;
        j = ray->tex_y * tex_width * 4 + (tex_width - 1 - ray->tex_x) * 4;
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
        i = y * var->width * 4 + x * 4;
        var->screen.dat[i++] = var->c_color & 0x0000FF;       // B
        var->screen.dat[i++] = var->c_color >> 8 & 0x0000FF;  // G
        var->screen.dat[i++] = var->c_color >> 16 & 0x0000FF; // R
        var->screen.dat[i] = 0;                               // A
        y++;
    }
    image_wall(var, ray, x);
    while (ray->end < var->height && ray->end >= 0) // floor
    {
        i = ray->end * var->width * 4 + x * 4;
        var->screen.dat[i++] = var->f_color & 0x0000FF;       // B
        var->screen.dat[i++] = var->f_color >> 8 & 0x0000FF;  // G
        var->screen.dat[i++] = var->f_color >> 16 & 0x0000FF; // R
        var->screen.dat[i] = 0;                               // A
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
    ray->wall_x -= floor(ray->wall_x);
    ray->tex_x = (int)(ray->wall_x * (double)var->tex[ray->side].width);
    if ((ray->side <= 1 && ray->dir_x > 0) ||
        (ray->side >= 2 && ray->dir_y < 0))
        ray->tex_x = var->tex[ray->side].width - ray->tex_x - 1;
    ray->tex_pos = (ray->start - var->height / 2 + ray->line_h / 2) * ray->step_t;
    image_fill(var, ray, x);
    return (0);
}

void raycast_scale(t_var *var, t_ray *ray)
{
    if (ray->side <= 1)
        ray->wall_dist = (ray->map_x - var->player.pos_x +
                          (1 - ray->step_x) / 2) /
                         ray->dir_x;
    else
        ray->wall_dist = (ray->map_y - var->player.pos_y +
                          (1 - ray->step_y) / 2) /
                         ray->dir_y;
    ray->line_h = (int)(var->height / ray->wall_dist);
    ray->start = -ray->line_h / 2 + var->height / 2;
    ray->start = (ray->start < 0 ? 0 : ray->start);
    ray->end = ray->line_h / 2 + var->height / 2;
    ray->end = (ray->end >= var->height ? var->height - 1 : ray->end);
}

void raycast_walls(t_var *var, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_x < ray->side_y)
        {
            ray->side_x += var->cam.delta_x;
            ray->map_x += ray->step_x;
            ray->side = (ray->step_x == -1 ? 0 : 1);
        }
        else
        {
            ray->side_y += var->cam.delta_y;
            ray->map_y += ray->step_y;
            ray->side = (ray->step_y == -1 ? 2 : 3);
        }
        if (ray->map_x < var->size_x && ray->map_y < var->size_y &&
            (var->map[ray->map_y][ray->map_x] == '1'))
            ray->hit = 1;
    }
}

void raycast_step(t_var *var, t_ray *ray)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_x = (var->player.pos_x - ray->map_x) * var->cam.delta_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_x = (ray->map_x + 1.0 - var->player.pos_x) * var->cam.delta_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_y = (var->player.pos_y - ray->map_y) * var->cam.delta_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_y = (ray->map_y + 1 - var->player.pos_y) * var->cam.delta_y;
    }
}

void raycast_setup(t_var *var, t_ray *ray, int x)
{
    var->cam.cam_x = (2 * x) / (double)var->width - 1;
    ray->dir_x = var->cam.dir_x + var->cam.plane_x * var->cam.cam_x;
    ray->dir_y = var->cam.dir_y + var->cam.plane_y * var->cam.cam_x;
    ray->map_x = (int)var->player.pos_x; // determine la case dans laquelle se trouve la cam
    ray->map_y = (int)var->player.pos_y;
    var->cam.delta_x = fabs(1 / ray->dir_x);
    var->cam.delta_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
}

int raycast(t_var *var, t_ray *ray)
{
    int x;
    double zbuffer[var->width];

    x = 0;
    while (x < var->width)
    {
        raycast_setup(var, ray, x);
        raycast_step(var, ray);
        raycast_walls(var, ray);
        raycast_scale(var, ray);
        zbuffer[x] = ray->wall_dist;
        texture_copy(var, ray, x++);
    }
    if (var->sprites)
        sprites_manager(var, zbuffer);
    return (0);
}

int game(t_var *var)
{
    t_ray ray;

    initialize_ray(&ray);
    initialize_tex(var);
    create_image(&var->screen, var->mlx, var->width, var->height);
    raycast(var, &ray);
    if (var->save)
        create_bmp(var);
    mlx_put_image_to_window(var->mlx, var->win, var->screen.ptr, 0, 0);
    mlx_destroy_image(var->mlx, var->screen.ptr);
    keys(var);
    return (0);
}

int main(int ac, char **av)
{
    t_var var;
    int fd;

    initialize_var(&var);
    if (ac == 2 || ac == 3)
    {
        check_argument(&var, av[1], ".cub", 1);
        fd = open(av[1], O_RDONLY);
        cub_parser(&var, fd);
        if (ac == 3 && !check_argument(&var, av[2], "--save", 2))
            var.save = 1;
        var.mlx = mlx_init();
        var.win = mlx_new_window(var.mlx, var.width, var.height, "Cub3D");
        mlx_hook(var.win, 2, 0, key_press, &var);
        mlx_hook(var.win, 3, 0, key_release, &var);
        mlx_hook(var.win, 17, 0, close_window, &var);
        mlx_loop_hook(var.mlx, game, &var);
        mlx_loop(var.mlx);
    }
    close_game(&var, "Number of arguments specified is incorrect.");
    return (0);
}