/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:36:36 by jabenjam          #+#    #+#             */
/*   Updated: 2020/08/25 22:24:02 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_toklen(const char *s, char c)
{
	int		len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

int			ft_free_words(char **words)
{
	int		i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (0);
}

int			ft_count_tokens(const char *str, char c)
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

char		*ft_fill_words(char *word, const char *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[j] != '\0' && s[j] == c)
		j++;
	if (!(word = malloc(sizeof(char) * (ft_toklen(s + j, c) + 1))))
		return (0);
	while (s[j] != '\0' && s[j] != c)
		word[i++] = s[j++];
	word[i] = '\0';
	return (word);
}

char		**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**words;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (!(words = malloc(sizeof(char *) * (ft_count_tokens(s, c) + 1))))
		return (0);
	while (s[j])
	{
		while (s[j] == c && s[j])
			j++;
		if (s[j] != c && s[j])
		{
			if (!(words[i] = ft_fill_words(words[i], s + j, c)))
				ft_free_words(words);
			i++;
			while (s[j] != c && s[j])
				j++;
		}
	}
	words[i] = 0;
	return (words);
}
