/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/01 18:57:41 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.c"
#include "get_next_line_utils.c"

void    initialize_var(t_var *var)
{
    var->size_x = 0;
    var->size_y = 0;
    var->f_color = 0;
    var->c_color = 0;
    var->no_path = 0;
    var->so_path = 0;
    var->we_path = 0;
    var->ea_path = 0;
    var->s_path = 0;
}

void    get_window_size(t_var *var, char *line)
{
    int     i;
    int     x;

    i = 0;
    x = 0;
    while (*line == ' ')
        line++;
    printf("resolution line = %s\n", line);
    while (line && *line >= '0' && *line <= '9' && *line != ' ')
        x = (x * 10) + (*(line++) - '0');
	printf("x = %d\n", x);
    var->size_x = x;
    x = 0;
    while (*line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9' && *line != '\n')
        x = (x * 10) + (*(line++) - '0');
    var->size_y = x;
    printf("x = %d\n", x);
    return;
}

/*char    *get_path(char *line)
{
    char    *path;
    return (path);
}

char    *get_color(char *line)
{
    int     color;

    color = 0;
    return (color);
}
*/
void    elem_parser(t_var *var, char *line)
{
    if (line && line[0] == 'R' && var->size_x == 0 && var->size_y == 0)
        get_window_size(var, ++line);
    if (line && line[0] == 'S' && var->s_path == 0)
//        var->s_path = get_path(line);
    if (line && line[0] == 'F' && var->f_color == 0)
//        var->f_color = get_color(line);
    if (line && line[0] == 'C' && var->c_color == 0)
//        var->c_color = get_color(line);
    if (line && line[0] == 'N' && line[1] == 'O' && var->no_path == 0)
//       var->no_path = get_path(line);
    if (line && line[0] == 'S' && line[1] == 'O' && var->so_path == 0)
//        var->so_path = get_path(line);
    if (line && line[0] == 'W' && line[1] == 'E' && var->we_path == 0)
//        var->we_path = get_path(line);
    if (line && line[0] == 'E' && line[1] == 'A' && var->ea_path == 0)
//        var->ea_path = get_path(line);
        {}
}

void    cub_parser(t_var *var, char *cub)
{
    (void)var; // a virer plus tard
    int     fd;
    char    *line;

    fd = open(cub, O_RDONLY);
    // ajouter verification d'erreurs dans la map
    printf("file = %s\n", cub);
    printf("fd = %d\n", fd);
    while (get_next_line(fd, &line) == 1)
	{
		printf("cub file line = %s\n", line);
        elem_parser(var, line);
		free(line);
	}
	printf("cub file line = %s\n", line);
	free(line);
    close(fd);
    return;
}

int     main(int ac, char **av)
{
    t_var  var;

    initialize_var(&var);
    if (ac == 2 || ac == 3)
    {
        // ajouter verification d'erreurs dans les arguments [if (a || b)]
        cub_parser(&var, av[1]);
        var.mlx = mlx_init();
        printf("mlx_ptr = %p\n", var.mlx);
        var.win = mlx_new_window(var.mlx, var.size_x, var.size_y, "Cub3D");
        mlx_string_put(var.mlx, var.win, 20, 20, 0255255000, "KEY_PRESSED = ");
        mlx_loop(var.mlx);
    }
    return(0);
}