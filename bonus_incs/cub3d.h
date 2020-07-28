/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:36:27 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/28 18:44:39 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
#define CUB3D_H

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

typedef struct s_player
{
    double pos_x;
    double pos_y;
    double speed;
} t_player;

typedef struct s_sprite
{
    int x;
    int y;
    int height;
    int width;
    double dist;
    void *ptr;
    char *dat;
    void *next;
    int  sl;
} t_sprite;

typedef struct s_ray_s
{
    double x;
    double y;
    double x_screen;
    double inv;
    int height;
    int width;
    int start_x;
    int end_x;
    int start_y;
    int end_y;
    int tex_x;
    int tex_y;
    int col;
    int row;
    int d;
} t_ray_s;

typedef struct s_key
{
    int forward;
    int backward;
    int left;
    int right;
    int l_strafe;
    int r_strafe;
    int size;
    int map;
} t_key;

typedef struct s_ray
{
    int hit;
    int side;
    int step_x;
    int step_y;
    int line_h;
    double wall_dist;
    double wall_x;
    double dir_x;
    double dir_y;
    double side_x;
    double side_y;
    int map_x;
    int map_y;
    int tex_x;
    int tex_y;
    double tex_pos;
    double step_t;
    int start;
    int end;
} t_ray;

typedef struct s_cam
{
    double delta_x;
    double delta_y;
    double plane_x;
    double plane_y;
    double cam_x;
    double dir_x;
    double dir_y;
} t_cam;

typedef struct s_tex
{
    char *path;
    void *ptr;
    char *dat;
    int width;
    int height;
} t_tex;

typedef struct s_img
{
    void *ptr;
    char *dat;
    int width;
    int bpp;
    int sl;
    int end;
} t_img;

typedef struct s_struct
{
    int width;    /* window width */
    int height;   /* window height */
    int f_color;  /* floor color */
    int c_color;  /* ceiling color */
    char *s_path; /* path to sprite texture */
    int number;   /* number of parameters received */
    char **map;   /* map */
    int size_x;   /* taille de la map en x */
    int size_y;   /* taille de la map en y */
    void *mlx;    /* screen connection identifier */
    void *win;    /* window identifier */
    int sl;
    int save;
    int n_sprites;
    t_key key;
    t_player player;
    t_cam cam;
    t_tex tex[5];
    t_sprite *sprites;
    t_img screen;
} t_var;

#endif
