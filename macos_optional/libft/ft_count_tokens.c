/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:40:17 by jabenjam          #+#    #+#             */
/*   Updated: 2019/10/09 16:34:27 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_count_tokens(const char *str, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}
