/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:42:57 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/29 15:14:48 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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

void initialize_key(t_key *key)
{
    key->forward = 0;
    key->backward = 0;
    key->left = 0;
    key->right = 0;
    key->l_strafe = 0;
    key->r_strafe = 0;
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