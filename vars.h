/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:10:28 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/20 18:30:31 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

typedef struct  s_player
{
    double       pos_x;
    double       pos_y;
    double       speed;
}               t_player;

typedef struct  s_sprite
{
    int         pos_x;
    int         pos_y;
    void        *next;
}               t_sprite;

typedef struct s_key
{
    int         forward;
    int         backward;
    int         left;
    int         right;
    int         l_strafe;
    int         r_strafe;
    int         size;
    int         map;
}               t_key;

typedef struct  s_ray
{
    int         hit;
    int         side;
    int         step_x;
    int         step_y;
    int         line_h;
    double      wall_dist;
    double      wall_x;
    double      dir_x;
    double      dir_y;
    double      side_x;
    double      side_y;
    int         map_x;
    int         map_y;
    int         tex_x;
    int         tex_y;
    double      tex_pos;
    double      step_t;
    int         start;
    int         end;
}               t_ray;

typedef struct  s_cam
{
    double       delta_x;
    double       delta_y;
    double       plane_x;
    double       plane_y;
    double       cam_x;
    double       dir_x;
    double       dir_y;
}               t_cam;


typedef struct  s_tex
{
    char        *path;
    void        *ptr;
    char        *dat;
    int         length;
    int         height;
}               t_tex;

typedef struct s_img
{
    void        *ptr;
    char        *dat;
    int         length;
    int         bpp;
    int         sl;
    int         end;
}               t_img;

typedef struct	s_struct
{
    int         length; /* window length */
    int         height; /* window height */
    int         f_color; /* floor color */
    int         c_color; /* ceiling color */
    char        *s_path; /* path to sprite texture */
    int         number; /* number of parameters received */
    char        **map; /* map */
    int         size_x; /* taille de la map en x */
    int         size_y; /* taille de la map en y */
    void        *mlx; /* screen connection identifier */
    void        *win; /* window identifier */
    int         save;
    t_key       key;
    t_player    player;
    t_cam       cam;
    t_tex       tex[4];
    t_sprite    *sprite;
    t_img       screen;
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
