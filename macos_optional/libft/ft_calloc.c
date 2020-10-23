/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:17:18 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/15 15:37:51 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	count = (count == 0 ? 1 : count);
	size = (size == 0 ? 1 : size);
	if (!(mem = malloc(count * size)))
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}
