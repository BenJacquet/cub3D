/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:15:54 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/22 14:41:19 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	uc;
	unsigned char	*ns;

	i = 0;
	uc = (unsigned char)c;
	ns = (unsigned char*)s;
	while (i < n)
	{
		if (ns[i] == uc)
			return (ns + i);
		i++;
	}
	return (0);
}
