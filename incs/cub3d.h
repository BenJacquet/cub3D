/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:36:27 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 23:04:48 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "keys.h"

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		speed;
}				t_player;

typedef struct	s_sprite
{
	int			x;
	int			y;
	double		dist;
	void		*next;
}				t_sprite;

typedef struct	s_ray_s
{
	double		x;
	double		y;
	double		x_screen;
	double		inv;
	int			height;
	int			width;
	int			start_x;
	int			end_x;
	int			start_y;
	int			end_y;
	int			tex_x;
	int			tex_y;
	int			col;
	int			row;
	int			d;
}				t_ray_s;

typedef struct	s_key
{
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			l_strafe;
	int			r_strafe;
}				t_key;

typedef struct	s_ray
{
	int			hit;
	int			side;
	int			step_x;
	int			step_y;
	int			line_h;
	double		wall_dist;
	double		wall_x;
	double		dir_x;
	double		dir_y;
	double		side_x;
	double		side_y;
	int			map_x;
	int			map_y;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	double		step_t;
	int			start;
	int			end;
}				t_ray;

typedef struct	s_cam
{
	double		delta_x;
	double		delta_y;
	double		plane_x;
	double		plane_y;
	double		cam_x;
	double		dir_x;
	double		dir_y;
}				t_cam;

typedef struct	s_tex
{
	char		*path;
	void		*ptr;
	char		*dat;
	int			width;
	int			height;
}				t_tex;

typedef struct	s_img
{
	void		*ptr;
	char		*dat;
	int			width;
	int			bpp;
	int			sl;
	int			end;
}				t_img;

typedef struct	s_struct
{
	int			width;
	int			height;
	int			f_color;
	int			c_color;
	int			colors;
	int			number;
	char		**map;
	int			size_x;
	int			size_y;
	void		*mlx;
	void		*win;
	int			sl;
	int			bpp;
	int			n_sprites;
	t_key		key;
	t_player	player;
	t_cam		cam;
	t_tex		tex[5];
	t_sprite	*sprites;
	t_img		screen;
}				t_var;

/*
**------INITIALIZATION----------------------------------------------------------
*/

void			initialize_var(t_var *var);
void			initialize_var2(t_var *var);
void			initialize_key(t_key *key);
void			initialize_ray(t_ray *ray);
void			initialize_tex(t_var *var);

/*
**------PARSING-----------------------------------------------------------------
*/

void			cub_parser(t_var *var, int fd, int ac);
char			**get_param(t_var *var, char **params, int ac);
int				cub_parser2(t_var *var, char *line, int ac);
void			parse_resolution(t_var *var, char *line, int ac);
char			*parse_path(char *line);
int				parse_rgb(t_var *var, char *line);
int				parse_player(t_var *var, int x, int y);
void			parse_map(t_var *var, char **params);
void			make_rectangular(t_var *var);
char			*resize_line(char *line, int spaces);
void			fill_space(t_var *var, int y, int x);
t_sprite		*store_sprite(t_var *var, int x, int y);

/*
**------CORE--------------------------------------------------------------------
*/

int				game(t_var *var);
void			create_image(t_img *img, void *mlx, int width, int height);
int				raycast(t_var *var, t_ray *ray);

/*
**------RAYCAST-----------------------------------------------------------------
*/

void			raycast_setup(t_var *var, t_ray *ray, int x);
void			raycast_step(t_var *var, t_ray *ray);
void			raycast_walls(t_var *var, t_ray *ray);
void			raycast_scale(t_var *var, t_ray *ray);
int				texture_copy(t_var *var, t_ray *ray, int x);

/*
**------SPRITES-----------------------------------------------------------------
*/

int				sprites_manager(t_var *var, double *zbuffer);
void			get_distance(t_sprite *sprites, t_player *player);
t_sprite		*sort_sprites(t_sprite *sprites);
void			swap_content(t_sprite *current, t_sprite *next);
t_ray_s			sprite_setup(t_var *var);
int				raycast_sprites(t_var *var, double *zbuffer);

/*
**------BITMAP------------------------------------------------------------------
*/

void			save(t_var *var);
void			create_bmp(t_var *var);
void			fill_bmp(int fd, t_var *var);

/*
**------RENDERING---------------------------------------------------------------
*/

void			image_fill(t_var *var, t_ray *ray, int x);
void			image_wall(t_var *var, t_ray *ray, int x);
void			sprite_x(t_var *var, t_ray_s *ray, double *zbuffer);
void			sprite_y(t_var *var, t_ray_s *ray);

/*
**------CONTROLS----------------------------------------------------------------
*/

int				keys(t_var *var);
void			look(t_cam *cam, int mode);
void			strafe(t_var *var, int mode);
void			forback(t_var *var, int mode);

/*
**------EVENTS------------------------------------------------------------------
*/

int				key_release(int key, t_var *var);
int				key_press(int key, t_var *var);
int				close_window(t_var *var);

/*
**------VERIFICATION------------------------------------------------------------
*/

void			check_map(t_var *var);
void			check_tex(t_var *var);
void			check_numbers(t_var *var, char *line, int mode);
int				check_argument(t_var *var, char *name, char *str, int mode);
int				check_parameters(t_var *var);
void			check_horizontally(t_var *var, int y);
void			check_vertically(t_var *var, int x);
void			check_segment(t_var *var, char *segment);
void			is_closed(t_var *var);

/*
**------EXIT--------------------------------------------------------------------
*/

void			close_game(t_var *var, char *error);
void			free_tex(t_tex *tex);

#endif
