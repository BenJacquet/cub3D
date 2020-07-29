/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:02:45 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/29 14:28:42 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

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