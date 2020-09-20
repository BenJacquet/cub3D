/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:44:06 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/15 15:40:05 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	len;
	char			*dup;

	len = ft_strlen(s1);
	if (!(dup = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	ft_memcpy(dup, s1, len + 1);
	return (dup);
}
