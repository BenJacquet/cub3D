/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 17:57:15 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/28 17:59:02 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void sprite_y(t_var *var, t_ray_s *ray, t_sprite *head)
{
    int i;
    int j;

    ray->d = ray->row * (head->width * 4) -
             var->height * (head->width * 4 / 2) +
             ray->height * (head->width * 4) / 2;
    ray->tex_y = ((ray->d * head->height) /
                  ray->height / (head->width * 4));
    i = ray->row * (var->width * 4) + (ray->col * 4);
    j = ray->tex_y * (head->width * 4) + (ray->tex_x * 4);
    if (head->dat[j] + head->dat[j + 1] + head->dat[j + 2] +
            head->dat[j + 3] !=
        0x0)
    {
        var->screen.dat[i++] = head->dat[j++]; // B
        var->screen.dat[i++] = head->dat[j++]; // G
        var->screen.dat[i++] = head->dat[j++]; // R
        var->screen.dat[i] = head->dat[j];     // A
    }
    ray->row++;
}

void sprite_x(t_var *var, t_ray_s *ray, t_sprite *head, double *zbuffer)
{
    ray->tex_x = (int)((head->width * 4) * (ray->col - (-ray->width / 2 + ray->x_screen)) *
                       head->width / ray->width) /
                 (head->width * 4);
    if (ray->y > 0 && ray->col > 0 &&
        ray->col < var->width && ray->y < zbuffer[ray->col])
    {
        ray->row = ray->start_y;
        while (ray->row < ray->end_y)
            sprite_y(var, ray, head);
    }
    ray->col++;
}