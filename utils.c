/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:56:29 by jabenjam          #+#    #+#             */
/*   Updated: 2020/07/26 18:37:57 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int i;
	unsigned char *ndst;
	const unsigned char *nsrc;

	i = 0;
	ndst = dst;
	nsrc = src;
	if (n == 0 || dst == src)
		return (dst);
	while (i < n)
	{
		ndst[i] = nsrc[i];
		i++;
	}
	return (dst);
}

char *ft_strdup(const char *s1)
{
	unsigned int len;
	char *dup;

	len = ft_strlen(s1) + 1;
	if (!(dup = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	ft_memcpy(dup, s1, len + 1);
	return (dup);
}

char *ft_strjoin(char *s1, char *s2)
{
	unsigned int i;
	unsigned int j;
	char *new;

	i = ft_strlen(s1) + ft_strlen(s2);
	j = 0;
	if (!(new = malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	free(s1);
	return (new);
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while ((s1[i] && s2[i]) && s1[i] == s2[i])
		i++;
	return ((s1[i] - s2[i] == 0 ? 1 : 0));
}

int ft_findn(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s && s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int ft_mini_atoi(char *str)
{
	int i;
	size_t result;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	return (result);
}