/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/09/20 18:30:31 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_incs/cub3d_bonus.h"

int			main(int ac, char **av)
{
	t_var	var;
	int		fd;

	initialize_var(&var);
	if (ac == 2 || ac == 3)
	{
		check_argument(&var, av[1], ".cub", 1);
		fd = open(av[1], O_RDONLY);
		cub_parser(&var, fd, ac);
		check_tex(&var);
		var.mlx = mlx_init();
		initialize_tex(&var);
		initialize_key(&var.key);
		if (ac == 3 && !check_argument(&var, av[2], "--save", 2))
			save(&var);
		var.win = mlx_new_window(var.mlx, var.width, var.height, "Cub3D");
		mlx_hook(var.win, 2, 1L << 0, key_press, &var);
		mlx_hook(var.win, 3, 1L << 1, key_release, &var);
		mlx_hook(var.win, 33, 1L << 17, close_window, &var);
		mlx_loop_hook(var.mlx, game, &var);
		mlx_loop(var.mlx);
	}
	close_game(&var, "Number of arguments specified is incorrect.\n");
	return (0);
}
