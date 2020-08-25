/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:03:49 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/22 14:41:05 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*ndst;
	const unsigned char		*nsrc;

	ndst = dst;
	nsrc = src;
	if (n == 0 || src == dst)
		return (NULL);
	while (n--)
	{
		if ((*ndst++ = *nsrc++) == (unsigned char)c)
			return (ndst);
	}
	return (NULL);
}
