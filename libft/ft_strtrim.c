/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:33:29 by jabenjam          #+#    #+#             */
/*   Updated: 2019/11/20 14:46:19 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*new;
	int				j;
	int				i;
	int				k;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	k = 0;
	while (ft_isinset(set, s1[i]))
		i++;
	while (ft_isinset(set, s1[j]))
		j--;
	if (i > j)
		return (ft_strdup(""));
	if (!(new = (char*)malloc(sizeof(char) * (j - i + 2))))
		return (NULL);
	while (i <= j)
		new[k++] = s1[i++];
	new[k] = '\0';
	return (new);
}
