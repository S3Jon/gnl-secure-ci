/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonsanch <jonsanch@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:49:08 by jonsanch          #+#    #+#             */
/*   Updated: 2023/08/01 15:08:19 by jonsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*alt;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	alt = malloc((1 + i) * sizeof(char) + 1);
	if (!alt)
		return (0);
	while (j < i)
	{
		alt[j] = s1[j];
		j++;
	}
	alt[i] = '\0';
	return (alt);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (ft_strlen(s) < start && start != 0 && len != 1)
	{
		str = (char *)malloc(1);
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(1 + len);
	if (!str)
		return (0);
	while (s[i + j] != '\0' && j < len)
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*aux;

	aux = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!aux)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		aux[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		aux[i + j] = s2[j];
		j++;
	}
	aux[i + j] = '\0';
	free((char *)s1);
	return (aux);
}
