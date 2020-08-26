/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:49:38 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/26 10:51:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

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
	else if (key == K_T)
		var->key.t = (var->key.t ? 0 : 1);
	else if (key == K_M)
		var->key.map = 1;
	else if (key == K_PLUS)
	{
		printf("before= key.size=%d\n", var->key.size);
		var->key.size += (var->key.size < var->width / 400);
		printf("after= key.size=%d\n", var->key.size);
	}
	else if (key == K_MINUS)
	{
		printf("before= key.size=%d\n", var->key.size);
		var->key.size -= (var->key.size > -4);
		printf("after= key.size=%d\n", var->key.size);
	}
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
	else if (key == K_M)
		var->key.map = 0;
	return (0);
}
