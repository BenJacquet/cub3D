/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:16:22 by jabenjam          #+#    #+#             */
/*   Updated: 2019/11/19 15:51:24 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int beg;
	int end;
	int tmp;

	beg = 0;
	end = ft_strlen(str);
	while (beg < (end / 2))
	{
		tmp = str[end - 1 - beg];
		str[end - 1 - beg] = str[beg];
		str[beg] = tmp;
		beg++;
	}
	return (str);
}
