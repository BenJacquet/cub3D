/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:10:28 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/16 19:00:46 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

typedef struct  s_player
{
    double       pos_x;
    double       pos_y;
}               t_player;

typedef struct s_move
{
    int         forward;
    int         backward;
    int         left;
    int         right;
    int         l_strafe;
    int         r_strafe;
}               t_move;

typedef struct  s_ray
{
    int     hit;
    int     side;
    int     step_x;
    int     step_y;
    int     line_h;
    double     wall_x;
    int     tex_x;
    int     tex_y;
    double   tex_pos;
    double   step_t;
    int     start;
    int     end;
    int     color;
}               t_ray;

typedef struct  s_camera
{
    double       delta_x;
    double       delta_y;
    double       plane_x;
    double       plane_y;
    double       ray_dirx;
    double       ray_diry;
    double       side_x;
    double       side_y;
    double       cam_x;
    double       wall_dist;
    int         map_x;
    int         map_y;
    double       dir_x;
    double       dir_y;
}               t_camera;


typedef struct  s_tex
{
    char        *path;
    void        *ptr;
    char        *dat;
    int         length;
    int         height;
    int         x;
    int         y;
}               t_tex;

typedef struct s_img
{
    void        *ptr;
    char        *dat;
    int         x;
    int         y;
}               t_img;

typedef struct	s_struct
{
    int         length; /* window length */
    int         height; /* window height */
    int         f_color; /* floor color */
    int         c_color; /* ceiling color */
    char        *s_path; /* path to sky texture */
    int         number; /* number of parameters received */
    char        **map; /* map */
    int         size_x; /* taille de la map en x */
    int         size_y; /* taille de la map en y */
    void        *mlx; /* screen connection identifier */
    void        *win; /* window identifier */
    t_move      move;
    t_player    player;
    t_camera    camera;
    t_tex       tex[4];
    t_img       img;
}				t_var;

# include <stdlib.h>

char	            *ft_strdup(const char *s1);
int	                ft_atoi(char *str);
int					ft_findn(char *s);
int					get_next_line(int fd, char **line);
int		            ft_mini_atoi(char *str);
char				*get_line(char *rem);
char				*get_remain(char *rem);
int		            ft_toklen(const char *s, char c);
int		            ft_free_words(char **words);
int		            ft_count_tokens(const char *str, char c);
char	            *ft_fill_words(char *word, const char *s, char c);
char	            **ft_split(char const *s, char c);

#endif
