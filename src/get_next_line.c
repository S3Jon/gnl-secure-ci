/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonsanch <jonsanch@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:48:46 by jonsanch          #+#    #+#             */
/*   Updated: 2023/08/01 15:03:39 by jonsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_isthisline(char *c)
{
	size_t	pos;

	pos = 0;
	while (c[pos] != '\0')
	{
		if (c[pos] == '\n')
			return (pos);
		pos++;
	}
	return (-1);
}

static int	ft_read_fd(int fd, char **c)
{
	int		read_bits;
	char	*temp;

	read_bits = 1;
	while (read_bits > 0)
	{
		temp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!temp)
			return (0);
		read_bits = read(fd, temp, BUFFER_SIZE);
		if (read_bits == -1)
		{
			free(temp);
			return (-1);
		}
		temp[read_bits] = '\0';
		if (*c == NULL)
			*c = ft_strdup(temp);
		else
			*c = ft_strjoin(*c, temp);
		free(temp);
		if (ft_isthisline(*c) != -1)
			return (0);
	}
	return (0);
}

static char	*ft_trimem(char **c)
{
	char	*aux;
	char	*ret_line;
	size_t	sum;

	sum = 0;
	aux = ft_strdup(*c);
	free(*c);
	*c = NULL;
	if (!aux)
		return (NULL);
	if (ft_isthisline(aux) == -1)
		return (aux);
	sum = (size_t)ft_isthisline(aux) + 1;
	ret_line = ft_substr(aux, 0, sum);
	*c = ft_substr(aux, sum, (ft_strlen(aux) - sum));
	free (aux);
	return (ret_line);
}

char	*get_next_line(int fd)
{
	static char	*bank;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	if (bank && ft_isthisline(bank) != -1)
		return (ft_trimem(&bank));
	if (ft_read_fd(fd, &bank) == -1)
	{
		free(bank);
		bank = NULL;
		return (NULL);
	}
	if (!bank || bank[0] == '\0')
	{
		free(bank);
		bank = NULL;
		return (NULL);
	}
	return (ft_trimem(&bank));
}
