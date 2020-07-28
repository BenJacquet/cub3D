/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/28 18:19:15 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "keys.h"

int main(int ac, char **av)
{
    t_var var;
    int fd;

    initialize_var(&var);
    if (ac == 2 || ac == 3)
    {
        check_argument(&var, av[1], ".cub", 1);
        fd = open(av[1], O_RDONLY);
        cub_parser(&var, fd);
        if (ac == 3 && !check_argument(&var, av[2], "--save", 2))
            var.save = 1;
        var.mlx = mlx_init();
        var.win = mlx_new_window(var.mlx, var.width, var.height, "Cub3D");
        mlx_hook(var.win, 2, 0, key_press, &var);
        mlx_hook(var.win, 3, 0, key_release, &var);
        mlx_hook(var.win, 17, 0, close_window, &var);
        mlx_loop_hook(var.mlx, game, &var);
        mlx_loop(var.mlx);
    }
    close_game(&var, "Number of arguments specified is incorrect.");
    return (0);
}