/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aesthetic_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:05:46 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 19:01:34 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

/*
** Key.t == 0 : Off
** Key.t == 1 : On
*/

void	music_player(t_var *var)
{
	if (var->key.play == 0 && var->key.t == 1)
	{
		system("mpg321 -g 50 bonus_sound/aesthetic.mp3 > /dev/null &");
		var->key.play = 1;
	}
	if (var->key.play == 1 && var->key.t == 0)
	{
		system("killall mpg321 > /dev/null &");
		var->key.play = 0;
	}
}

void	aesthetic_wall(t_var *var, t_ray *ray, int x)
{
	int	i;

	while (ray->start <= ray->end && ray->end >= 0) // walls;
	{
		i = ray->start * var->width * 4 + x * 4;
		var->screen.dat[i++] = (ray->side <= 1 ? 0x0000D5: 0x00004B);// B
		var->screen.dat[i++] = (ray->side <= 1 ? 0x000003: 0x000000);// G
		var->screen.dat[i++] = (ray->side <= 1 ? 0x0000DF: 0x00000C);// R
		var->screen.dat[i] = 0x0;     // A
		ray->start++;
		ray->tex_pos += ray->step_t;
	}
}

void	aesthetic_fc(t_var *var, t_ray *ray, int x)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (y < ray->start) // ceiling
	{
		i = y * var->width * 4 + x * 4;
		var->screen.dat[i++] = 0x000056;    // B
		var->screen.dat[i++] = 0x000050;    // G
		var->screen.dat[i++] = 0x0000FB;    // R
		var->screen.dat[i] = 0x0;           // A
		y++;
	}
	aesthetic_wall(var, ray, x);
	while (ray->end < var->height && ray->end >= 0) // floor
	{
		i = ray->end * var->width * 4 + x * 4;
		var->screen.dat[i++] = 0x0000D8;    // B
		var->screen.dat[i++] = 0x000013;    // G
		var->screen.dat[i++] = 0x000045;    // R
		var->screen.dat[i] = 0x0;           // A
		ray->end++;
	}
}
