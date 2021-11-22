/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:40:27 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/22 20:41:15 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
char	*cut_line(char *src, int begin, int end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof (char) * (end - begin + 1));
	if (!dest)
	{
		free(src);
		return (NULL);
	}
	while (src[begin])
	{
		dest[i] = src[begin];
		i++;
		begin++;
	}
	dest[i] = 0;
	free (src);
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
	free(begin);
	return (dst);
}

// 5 function
char	*cpy_string(char *str, int len)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str || (str[0] == 0))
		return (NULL);
	new_str = (char *)malloc(sizeof (char) * len + 1);
	if (new_str)
	{
		while (i < len)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = 0;
	}
	return (new_str);
}
