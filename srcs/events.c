/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:49:38 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 14:51:31 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int		close_window(t_var *var)
{
	close_game(var, "");
	return (0);
}

int		key_press(int key, t_var *var)
{
	if (key == K_ESC)
		close_game(var, "");
	else if (key == K_W)
		var->key.forward = 1;
	else if (key == K_S)
		var->key.backward = 1;
	else if (key == K_RIGHT)
		var->key.left = 1;
	else if (key == K_LEFT)
		var->key.right = 1;
	else if (key == K_A)
		var->key.l_strafe = 1;
	else if (key == K_D)
		var->key.r_strafe = 1;
	return (0);
}

int		key_release(int key, t_var *var)
{
	if (key == K_W)
		var->key.forward = 0;
	else if (key == K_S)
		var->key.backward = 0;
	else if (key == K_RIGHT)
		var->key.left = 0;
	else if (key == K_LEFT)
		var->key.right = 0;
	else if (key == K_A)
		var->key.l_strafe = 0;
	else if (key == K_D)
		var->key.r_strafe = 0;
	return (0);
}
