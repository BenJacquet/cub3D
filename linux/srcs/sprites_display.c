/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:57:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 16:08:59 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void		sprite_y(t_var *var, t_ray_s *ray)
{
	int		i;
	int		j;

	ray->d = ray->row * (var->tex[4].width * 4) -
		var->height * (var->tex[4].width * 4 / 2) +
		ray->height * (var->tex[4].width * 4) / 2;
	ray->tex_y = ((ray->d * var->tex[4].height) /
			ray->height / (var->tex[4].width * 4));
	i = ray->row * (var->width * 4) + (ray->col * 4);
	j = ray->tex_y * (var->tex[4].width * 4) + (ray->tex_x * 4);
	if (var->tex[4].dat[j] + var->tex[4].dat[j + 1] + var->tex[4].dat[j + 2] +
			var->tex[4].dat[j + 3] !=
			0x0)
	{
		var->screen.dat[i++] = var->tex[4].dat[j++]; // B
		var->screen.dat[i++] = var->tex[4].dat[j++]; // G
		var->screen.dat[i++] = var->tex[4].dat[j++]; // R
		var->screen.dat[i] = var->tex[4].dat[j];     // A
	}
	ray->row++;
}

void		sprite_x(t_var *var, t_ray_s *ray, double *zbuffer)
{
	ray->tex_x = (int)((var->tex[4].width * 4) * (ray->col - (-ray->width / 2 + ray->x_screen)) *
			var->tex[4].width / ray->width) /
		(var->tex[4].width * 4);
	if (ray->y > 0 && ray->col > 0 &&
			ray->col < var->width && ray->y < zbuffer[ray->col])
	{
		ray->row = ray->start_y;
		while (ray->row < ray->end_y)
			sprite_y(var, ray);
	}
	ray->col++;
}
