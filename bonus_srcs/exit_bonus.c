/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:39:03 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/26 10:54:44 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_incs/cub3d_bonus.h"

void		close_game2(t_var *var)
{
	int i;

	i = 0;
	while (i <= 4)
	{
		if (var->tex[i].path != NULL)
		{
			free(var->tex[i].path);
		}
		i++;
	}
	if (var->win != NULL)
		mlx_destroy_window(var->mlx, var->win);
	if (var->key.play == 1 && !system("pgrep mpg321"))
		system("killall mpg321");
}

void		close_game(t_var *var, char *error)
{
	t_sprite	*current;

	if (var->sprites)
	{
		while (var->sprites != NULL)
		{
			current = var->sprites;
			var->sprites = var->sprites->next;
			free(current);
		}
	}
	if (*error != '\0')
	{
		ft_putstr_fd("Error : ", 2);
		ft_putstr_fd(error, 2);
	}
	if (var->map)
	{
		while (var->map && *var->map)
			free(*(var->map)++);
	}
	close_game2(var);
	exit(0);
}
