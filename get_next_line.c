/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 06:43:19 by fchrysta          #+#    #+#             */
/*   Updated: 2021/10/26 09:05:05 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_to_list(int fd, t_list **list_str)
{
	char buf[BUFFER_SIZE];
	int endline;
	int readed;
	while (!endcode)
	{
		readed = read (fd, buf, BUF_SIZE);
		endcode = get_endcode(buf);
		list_put_end(buf, list_str)
	}
	return (endcode);
}

char	*get_next_line(int fd)
{
	static char	*next_line_begin
	char		*line
	t_list		*list_str;
	int			endcode;

	if (fd)
	{
		list_str = (t_list *)malloc(sizeof(t_list)
		endcode = read_to_list(fd, &list_str);
		line = parse_list(&list_str, &next_line_begin);
		free_memory(&list_str, &next_line_begin, endcode); // if endcode = 2 free next_line_begin too
	}
	return (line);
}
