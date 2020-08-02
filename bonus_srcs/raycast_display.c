/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:01:47 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/02 16:07:35 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d.h"

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