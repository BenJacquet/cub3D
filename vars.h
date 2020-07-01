/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:10:28 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/01 17:41:03 by jabenjam         ###   ########.fr       */
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
    void        *mlx; /* screen connection identifier */
    void        *win; /* window identifier */
    void        *key; /* pressed key identifier */
}				t_var;

#endif
