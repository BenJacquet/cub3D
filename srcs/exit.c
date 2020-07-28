/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:39:03 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/28 17:55:21 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void close_game(t_var *var, char *error)
{
    void *current;

    while (var->sprites)
    {
        current = var->sprites;
        var->sprites = var->sprites->next;
        free(current);
    }
    if (*error != '\0')
    {
        ft_putstr_fd("Error : ", 2);
        ft_putstr_fd(error, 2);
    }
    while (var->map && *var->map)
        free(*var->map++);
    if (var->mlx)
        mlx_destroy_window(var->mlx, var->win);
    exit(0);
}