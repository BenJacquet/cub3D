/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 13:50:48 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/02 19:02:44 by jabenjam         ###   ########.fr       */
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
#include "ft_split.c"

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
    int     x;

    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9' && *line != ' ')
        x = (x * 10) + (*(line++) - '0');
    var->size_x = x;
    x = 0;
    while (line && *line == ' ')
        line++;
    while (line && *line >= '0' && *line <= '9')
        x = (x * 10) + (*(line++) - '0');
    var->size_y = x;
    return;
}

char    *get_path(char *line)
{
    char    *path;

    while (line && *line == ' ')
        line++;
    path = ft_strdup(line);
    return(path);
}

int     get_rgb(char *line)
{
    int     rgb;
    int     x;
    int     colors;

    rgb = 0;
    x = 0;
    colors = 0;
    while (line && *line == ' ')
        line++;
	while (line && colors < 3)
    {
 	    while (*line >= '0' && *line <= '9')
		    x = (x * 10) + (*(line++) - '0');
        rgb = (colors == 0 ? rgb = x : (rgb << 8) + x);
        printf("x=%d\nrgb=%d\n", x, rgb);
        x = 0;
        colors++;
        if (*line == ',')
            line++;
        /*if (x < 0 || x > 255)
            erreur, color "out of range"*/
    }
    return (rgb);
}


void    elem_parser(t_var *var, char *line)
{
    if (line && line[0] == 'R' && var->size_x == 0 && var->size_y == 0)
        get_window_size(var, ++line);
    else if (line && line[0] == 'F' && var->f_color == 0)
        var->f_color = get_rgb(++line);
    else if (line && line[0] == 'C' && var->c_color == 0)
        var->c_color = get_rgb(++line);
    else if (line && line[0] == 'N' && line[1] == 'O' && var->no_path == 0)
        var->no_path = get_path(2 + line);
    else if (line && line[0] == 'S' && line[1] == 'O' && var->so_path == 0)
        var->so_path = get_path(2 + line);
    else if (line && line[0] == 'W' && line[1] == 'E' && var->we_path == 0)
        var->we_path = get_path(2 + line);
    else if (line && line[0] == 'E' && line[1] == 'A' && var->ea_path == 0)
        var->ea_path = get_path(2 + line);
    else if (line && line[0] == 'S' && var->s_path == 0)
        var->s_path = get_path(++line);
}

void    cub_parser(t_var *var, char *cub)
{
    (void)var; // a virer plus tard
    int     fd;
    int     out;
    char    **params;
    char    *buffer;

    fd = open(cub, O_RDONLY);
    while (out != 0)
    {
        params = read(fd, buffer, 4096);
        
    }
    // ajouter verification d'erreurs dans la map
    while (*params != 0)
	{
        elem_parser(var, *(params++));
		free(params);
	}
	free(params);
    close(fd);
    return;
}

int     main(int ac, char **av)
{
    t_var   var;

    initialize_var(&var);
    if (ac == 2 || ac == 3)
    {
        // ajouter verification d'erreurs dans les arguments [if (a || b)]
        cub_parser(&var, av[1]);
        var.mlx = mlx_init();
        var.win = mlx_new_window(var.mlx, var.size_x, var.size_y, "Cub3D");
        printf("VARS\nsize_x=%d\nsize_y=%d\nf_color=%d\nc_color=%d\nno_path=%s\nso_path=%s\nwe_path=%s\nea_path=%s\ns_path=%s\nmlx=%p\nwin=%p\n", var.size_x, var.size_y, var.f_color, var.c_color, var.no_path, var.so_path, var.we_path, var.ea_path, var.s_path, var.mlx, var.win);
        mlx_string_put(var.mlx, var.win, 20, 20, 0255255000, "KEY_PRESSED = ");
        mlx_loop(var.mlx);
    }
    return(0);
}