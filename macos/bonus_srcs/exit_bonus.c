/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:39:03 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/11 16:05:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

void		close_game(t_var *var, char *error)
{
	void *current;

	while (var->sprites)
	{
		current = var->sprites;
		var->sprites = var->sprites->next;
		free(current);
	}
	if (*error != '\0')
	{
		ft_putstr_fd("Error : ", 2);
		ft_putstr_fd(error, 2);
	}
	while (var->map && *var->map)
		free(*var->map++);
	if (var->mlx && var->win)
		mlx_destroy_window(var->mlx, var->win);
	if (var->key.play == 1 && !system("pgrep afplay"))
		system("killall afplay");
	exit(0);
}
