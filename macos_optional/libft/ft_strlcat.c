/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:07:16 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/16 13:07:18 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	len_src;
	unsigned int	len_dest;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (dstsize < len_dest)
		return (dstsize + len_src);
	i = 0;
	while (src[i] != '\0' && (len_dest + i + 1) < dstsize)
	{
		dest[len_dest + i] = (char)src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (len_dest + len_src);
}
