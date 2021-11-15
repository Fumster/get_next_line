/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:40:27 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/15 21:03:06 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 1 function
int	ft_strlen(char *str)
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

// 2 function
int	ft_get_endline_index(char *str)
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

// 3 function
char	*cut_line(char **src, int begin, int end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof (char) * (end - begin + 2));
	if (!dest)
		return (NULL);
	while (begin < end)
	{
		dest[i] = *src[begin];
		i++;
		begin++;
	}
	dest[i] = 0;
	free (src)
	return (dest);
}

// 4 function
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
		while (end && end[j])
		{
			dst[i] = end[j];
			i++;
			j++;
		}
		dst[i] = 0;
	}
	return (dst);
}
