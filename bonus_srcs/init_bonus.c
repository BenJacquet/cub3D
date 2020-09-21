/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:42:57 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/20 22:31:42 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

void	initialize_var2(t_var *var)
{
	var->tex[0].path = NULL;
	var->tex[1].path = NULL;
	var->tex[2].path = NULL;
	var->tex[3].path = NULL;
	var->tex[4].path = NULL;
	var->sprites = NULL;
	var->win = NULL;
	var->map = NULL;
}

void	initialize_var(t_var *var)
{
	var->width = 0;
	var->height = 0;
	var->size_x = 0;
	var->size_y = 0;
	var->f_color = 0;
	var->c_color = 0;
	var->colors = 0;
	var->number = 0;
	var->bpp = 32;
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
	initialize_var2(var);
}

void	initialize_key(t_key *key)
{
	key->forward = 0;
	key->backward = 0;
	key->left = 0;
	key->right = 0;
	key->l_strafe = 0;
	key->r_strafe = 0;
	key->size = 0;
	key->map = 0;
	key->t = 0;
	key->play = 0;
}

void	initialize_ray(t_ray *ray)
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

void	initialize_tex(t_var *var)
{
	int	i;
	int	endian;
	int	sl;

	i = 0;
	endian = 0;
	while (i <= 4)
	{
		check_argument(var, var->tex[i].path, ".xpm", 1);
		var->tex[i].width = 64;
		var->tex[i].height = 64;
		sl = var->tex[i].width * 4;
		var->tex[i].ptr = mlx_xpm_file_to_image(var->mlx, var->tex[i].path,
						&var->tex[i].width, &var->tex[i].height);
		if (var->tex[i].ptr == NULL)
			close_game(var, "Texture file is corrupted.\n");
		var->tex[i].dat = mlx_get_data_addr(var->tex[i].ptr, &var->bpp,
						&sl, &endian);
		i++;
	}
}
