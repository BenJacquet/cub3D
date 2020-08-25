/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:49:03 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 15:27:52 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int			forback(t_var *var, int mode)
{
	if (mode == 1)
	{
		if (var->player.pos_x + var->cam.dir_x * 0.1 >= 1 &&
				var->player.pos_x + var->cam.dir_x * 0.1 <= var->size_x - 1)
			var->player.pos_x += (var->cam.dir_x * 0.1);
		if (var->player.pos_y + var->cam.dir_y * 0.1 >= 1 &&
				var->player.pos_y + var->cam.dir_y * 0.1 <= var->size_y - 1)
			var->player.pos_y += (var->cam.dir_y * 0.1);
	}
	else
	{
		if (var->player.pos_x - var->cam.dir_x * 0.1 >= 1 &&
				var->player.pos_x - var->cam.dir_x * 0.1 <= var->size_x - 1)
			var->player.pos_x -= (var->cam.dir_x * 0.1);
		if (var->player.pos_y - var->cam.dir_y * 0.1 >= 1 &&
				var->player.pos_y - var->cam.dir_y * 0.1 <= var->size_y - 1)
			var->player.pos_y -= (var->cam.dir_y * 0.1);
	}
	return (0);
}

int			strafe(t_var *var, int mode)
{
	if (mode == 3)
	{
		if (var->player.pos_x - var->cam.plane_x * 0.1 >= 1 &&
				var->player.pos_x - var->cam.plane_x * 0.1 <= var->size_x - 1)
			var->player.pos_x -= (var->cam.plane_x * 0.1);
		if (var->player.pos_y - var->cam.plane_y * 0.1 >= 1 &&
				var->player.pos_y - var->cam.plane_y * 0.1 <= var->size_y - 1)
			var->player.pos_y -= (var->cam.plane_y * 0.1);
	}
	else
	{
		if (var->player.pos_x + var->cam.plane_x * 0.1 >= 1 &&
				var->player.pos_x + var->cam.plane_x * 0.1 <= var->size_x - 1)
			var->player.pos_x += (var->cam.plane_x * 0.1);
		if (var->player.pos_y + var->cam.plane_y * 0.1 >= 1 &&
				var->player.pos_y + var->cam.plane_y * 0.1 <= var->size_y - 1)
			var->player.pos_y += (var->cam.plane_y * 0.1);
	}
	return (0);
}

int			look(t_cam *cam, int mode)
{
	double	save_dir_x;
	double	save_plane_x;

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

int			keys(t_var *var)
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
	return (0);
}
