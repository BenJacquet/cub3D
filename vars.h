/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:10:28 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/07 18:49:10 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

typedef struct	s_struct
{
    int         size_x; /* window length */
    int         size_y; /* window width */
    int         f_color; /* floor color */
    int         c_color; /* ceiling color */
    char        *no_path; /* path to north wall texture */
    char        *so_path; /* path to south wall texture */
    char        *we_path; /* path to west wall texture */
    char        *ea_path; /* path to east wall texture */
    char        *s_path; /* path to sky texture */
    int         number; /* number of parameters received */
    char        **map; /* map */
    int         map_x; /* taille de la map en x */
    int         map_y; /* taille de la map en y */
    void        *mlx; /* screen connection identifier */
    void        *win; /* window identifier */
    void        *key; /* pressed key identifier */
}				t_var;

typedef         struct
{
    float       pos_x;
    float       pos_y;
    float       dir_x;
    float       dir_y;
}              t_player;


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
