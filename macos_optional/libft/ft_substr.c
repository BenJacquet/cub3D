/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:40:15 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/30 16:55:00 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (!(new = malloc(sizeof(char) * len + 1)))
		return (0);
	while (s[i + start] && i < len && start < ft_strlen(s))
	{
		new[i] = s[i + start];
		i++;
	}
	new[i] = '\0';
	return (new);
}
