/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aesthetic_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 18:05:46 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/20 17:56:06 by jabenjam         ###   ########.fr       */
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
		system("afplay -v 50 bonus_sound/aesthetic.mp3 > /dev/null &");
		var->key.play = 1;
	}
	if (var->key.play == 1 && var->key.t == 0)
	{
		system("killall afplay > /dev/null &");
		var->key.play = 0;
	}
}

void	aesthetic_wall(t_var *var, t_ray *ray, int x)
{
	int	i;

	while (ray->start <= ray->end && ray->end >= 0)
	{
		i = ray->start * var->width * 4 + x * 4;
		var->screen.dat[i++] = (ray->side <= 1 ? 0x0000D5 : 0x00004B);
		var->screen.dat[i++] = (ray->side <= 1 ? 0x000003 : 0x000000);
		var->screen.dat[i++] = (ray->side <= 1 ? 0x0000DF : 0x00000C);
		var->screen.dat[i] = 0x0;
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
	while (y < ray->start)
	{
		i = y * var->width * 4 + x * 4;
		var->screen.dat[i++] = 0x000056;
		var->screen.dat[i++] = 0x000050;
		var->screen.dat[i++] = 0x0000FB;
		var->screen.dat[i] = 0x0;
		y++;
	}
	aesthetic_wall(var, ray, x);
	while (ray->end < var->height && ray->end >= 0)
	{
		i = ray->end * var->width * 4 + x * 4;
		var->screen.dat[i++] = 0x0000D8;
		var->screen.dat[i++] = 0x000013;
		var->screen.dat[i++] = 0x000045;
		var->screen.dat[i] = 0x0;
		ray->end++;
	}
}
