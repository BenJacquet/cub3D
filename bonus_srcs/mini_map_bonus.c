/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:51:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/03 12:44:30 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

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