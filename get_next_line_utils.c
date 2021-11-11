/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:40:27 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/11 22:17:56 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str) // 1 function
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	ft_get_endline_index(char *str) // 2 function
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

char	*cut_line(char *src, int begin, int end) // 3 function
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof (char) * (end - begin + 2));
	if (!dest)
		return (NULL);
	while (begin < end)
	{
		dest[i] = src[begin];
		i++;
		begin++;
	}
	return (dest);
}

char	*append_lines(char *begin, char *end)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * ft_strlen(begin) + ft_strlen(end) + 1);
	if (dst)
	{
		while (begin && begin[i])
		{
			dst[i] = begin [i];
			i++;
		}
		while (end[j])
		{
			dst[i] = end[j];
			i++;
			j++;
		}
	}
	return (dst);
}
