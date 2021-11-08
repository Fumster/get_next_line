/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 06:43:19 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/08 22:41:23 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // test string

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_append_line(char *string, t_list *list)  // todo split to  2 functions
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = string
	while (join + i)
	{
		if (list->tmp_string && list->tmp_string[i])
			i++;
		if (!join + i)
			break;
		i++;
	}
	join = (char *)malloc(sizeof (char) * i + 1);
	if (join)
	{
		if (list->tmp_string)
		{
			i = 0;
			while (string[i])
			{
				join[i] = string[i];
				i++;
			}
			while (buf [j])
			{
				join[i] = buf[j];
				i++;
				j++;
			}
			join[i] = 0;
		}
		else	
			list->tmp_string = join;
	}
}

t_list	*find_list_by_fd(int fd, t_list *list) // ready, return list with fd or new list, if error return NULL
{
	t_list *last_list;

	last_list = list;
	while (last_list && last_list->next && last_list->fd != fd)
		last_list = last_list->next;
	if (!last_list || last_list->fd != fd)
	{
		list = (t_list *) malloc(sizeof(t_list));
		if (list)
		{
			list->tmp_string = NULL;
			list->ret_string = NULL;
			list->fd = fd;
			if (last_list)
				last_list->next = list;
		}
	}
	return (list);
}

void	read_file_to_list(t_list *list) // ready, list->tmp_str comes always NULL
{
	char	buf[BUFFER_SIZE + 1];
	int		readed_char_num;
	int		is_readed_full_line;
	int		i;

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
			while (buf[i])
			{
				if (buf[i] == '\n')
						is_readed_full_line = 1;
				i++;
			}
			ft_append_line(buf, list);
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


	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	this_list = find_list_by_fd(fd, list);
	if (this_list && !this_list->tmp_string)
		read_file_to_list(this_list);
	fill_ret_string_in_list(this_list);
	clear lists(&this_list, &list);
	if (this_list)
		return (this_list->ret_string);
	else
		return (NULL);
}
