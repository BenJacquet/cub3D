/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:28:53 by jabenjam          #+#    #+#             */
/*   Updated: 2019/11/20 14:35:15 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*nbr;
	int				i;
	int				sign;
	unsigned int	nb;

	i = 0;
	if (!(nbr = malloc(sizeof(char) * (ft_ilen(n) + 1))))
		return (0);
	sign = n < 0 ? 1 : 0;
	nb = ft_abs(n);
	while (nb >= 10)
	{
		nbr[i++] = nb % 10 + '0';
		nb /= 10;
	}
	nbr[i++] = nb % 10 + '0';
	if (sign)
		nbr[i++] = '-';
	nbr[i] = '\0';
	return (ft_strrev(nbr));
}
