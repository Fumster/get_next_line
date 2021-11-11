/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 06:43:19 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/11 22:17:53 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // test string

t_list	*find_list_by_fd(int fd, t_list **list) // ready, return list with fd or new list, if error return NULL
{
	t_list *last_list;
	t_list *new_list;

	last_list = *list;
	if (!*list)
	{
		*list = (t_list *)malloc(sizeof(t_list));
		*list->fd = fd;
		return(*list);
	}	
	while (last_list->next)
	{
		last_list = last_list->next;
		if (last_list->fd == fd)
			return (last_list);
	}
	new_list = (t_list *)malloc(sizeof(t_list));
	if(!new_list)
		return(NULL);
	new_list->tmp_string = NULL;
	new_list->fd = fd;
	last_list->next = new_list;
	return (new_list);
}

void	read_file_to_list(t_list *list) // ready, write to tmp_str or do nothing
{
	char	buf[BUFFER_SIZE + 1];
	int		readed_char_num;
	int		is_readed_full_line;

	is_readed_full_line = 0;
	while (!is_readed_full_line)
	{
		i = 0;
		readed_char_num = read (fd, buf, BUFFER_SIZE);
		if (readed_char_num <= 0)
			is_readed_full_line = 1;
		else
		{
			buf[readed_char_num] = 0;
			if (ft_get_endline_index(buf) >= 0)
				is_readed_full_line = 1;
			list->tmp_line = ft_append_line(list->tmp_string, buf);
			if (!list->tmp_line)
				break;
		}
	}
}

void	clear_lists(int fd, t_list **this_list, t_list **list)
{
	t_list	*del_list;
	t_list	*tmp_list;

	del_list = *this_list;
	tmp_list = *list;
	while (tmp_list->next && tmp_list->next != del_list)
		tmp_list = tmp_list->next;
	if (tmp_list->next == del_list)
		tmp_list->next = del_list->next;
	free ((*this_list)->string);
	if (*this_list == *list)
		*list = NULL;
	free(*this_list);
	*this_list = NULL;
}

void	fill_ret_string_in_list(t_list *list)
{
	int		string_len;
	int		pos;
	int		i;
	char	*string;

	string_len = ft_strlen(list->string);
	pos = 0;
	i = 0;
	while (list->string[pos] != '\n' && list->string[pos])
		pos++;
	if (list->ret_string)
		free(list->ret_string);
	list->ret_string = (char *)malloc(sizeof (char) * pos + 1);
	while (i < pos)
	{
		list->ret_string[i] = list->string[i];
		i++;
	}
	string = (char *)malloc(sizeof (char) * string_len - i + 1);
	i = 0;
	while (list->string[pos + i])
	{
		string[i] = list->string[pos + i];
		i++;
	}
	string[i] = 0;
	free(list->string);
	list->string = string;
}

char	*get_next_line(int fd)
{
	static t_list	list;
	t_list			*this_list;
	char			*ret_string;


	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	this_list = find_list_by_fd(fd, &list);
	if (!this_list)
		return (NULL);
	if (ft_get_endline_index(this_list->tmp_string) < 0)
		read_file_to_list(this_list);
	if (this_list && this_list->tmp_string)
		fill_ret_string_in_list(this_list);
	if (this_list && !this_list->ret_string)
		delete_list(&list, &this_list);
	if (this_list)
		return (this_list->ret_string);
	else
		return (NULL);
}
