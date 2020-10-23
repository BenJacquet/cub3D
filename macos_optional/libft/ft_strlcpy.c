/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:57:13 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/21 17:06:58 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			len;

	i = 0;
	len = 0;
	if (!src)
		return (size);
	while (src[len] != '\0')
		len++;
	if (!(size))
		return (len);
	while ((dst[i] = src[i]) != '\0' && i < size - 1)
		i++;
	dst[i] = '\0';
	return (len);
}
