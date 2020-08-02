/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:04:00 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/02 16:35:56 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void create_image(t_img *img, void *mlx, int width, int height)
{
    img->bpp = 32;
    img->sl = width * 4;
    img->end = 0;
    img->ptr = mlx_new_image(mlx, width, height);
    img->dat = mlx_get_data_addr(img->ptr, &img->bpp, &img->sl, &img->end);
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
    create_image(&var->screen, var->mlx, var->width, var->height);
    raycast(var, &ray);
    mlx_put_image_to_window(var->mlx, var->win, var->screen.ptr, 0, 0);
    mlx_destroy_image(var->mlx, var->screen.ptr);
    keys(var);
    return (0);
}

void save(t_var *var)
{
    t_ray ray;

    initialize_ray(&ray);
    create_image(&var->screen, var->mlx, var->width, var->height);
    raycast(var, &ray);
    create_bmp(var);
}