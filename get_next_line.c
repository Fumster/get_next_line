/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 06:43:19 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/22 21:51:28 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 1 function
t_list	*find_list_by_fd(int fd, t_list **list)
{
	t_list	*last_list;
	t_list	*new_list;

	last_list = *list;
	if (*list && ((*list)->fd == fd))
		return (*list);
	while (last_list && last_list->next)
	{
		last_list = last_list->next;
		if (last_list->fd == fd)
			return (last_list);
	}
	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	new_list->next = NULL;
	new_list->tmp_string = NULL;
	new_list->fd = fd;
	if (last_list)
		last_list->next = new_list;
	if (!*list)
		*list = new_list;
	return (new_list);
}

// 2 function
void	read_file_to_list(t_list *list)
{
	char	buf[BUFFER_SIZE + 1];
	int		readed_char_num;
	int		is_readed_full_line;

	is_readed_full_line = 0;
	while (!is_readed_full_line)
	{
		readed_char_num = read (list->fd, buf, BUFFER_SIZE);
		if (readed_char_num <= 0)
			is_readed_full_line = 1;
		else
		{
			buf[readed_char_num] = 0;
			if (ft_get_endline_index(buf) >= 0)
				is_readed_full_line = 1;
			list->tmp_string = append_lines(list->tmp_string, buf);
			if (!list->tmp_string)
				break ;
		}
	}
}

// 3 function
void	delete_list(t_list **list, t_list **this_list)
{
	t_list	*del_list;
	t_list	*tmp_list;

	del_list = *this_list;
	tmp_list = *list;
	if (!*this_list)
		return ;
	if (*list == *this_list)
	{
		*list = (*list)->next;
		if ((*this_list)->tmp_string)
			free((*this_list)->tmp_string);
	}
	else
	{
		while (tmp_list->next != del_list)
			tmp_list = tmp_list->next;
		tmp_list->next = del_list->next;
		if ((*this_list)->tmp_string)
			free ((*this_list)->tmp_string);
	}
	free(*this_list);
	*this_list = NULL;
}

// 4 function
char	*get_ret_string(t_list *list)
{
	int		tmp_string_len;
	int		endline_pos;
	char	*string;

	string = NULL;
	tmp_string_len = ft_strlen(list->tmp_string);
	endline_pos = ft_get_endline_index(list->tmp_string);
	if (endline_pos < 0)
	{
		string = cpy_string(list->tmp_string, tmp_string_len);
		free(list->tmp_string);
		(list->tmp_string) = NULL;
		return (string);
	}
	string = cpy_string(list->tmp_string, endline_pos + 1);
	if ((endline_pos + 1) == tmp_string_len)
	{
		free(list->tmp_string);
		list->tmp_string = NULL;
	}
	else
		list->tmp_string = \
				cut_line(list->tmp_string, endline_pos + 1, tmp_string_len + 1);
	return (string);
}

// 5 function
char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*this_list;
	char			*ret_string;

	ret_string = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	this_list = find_list_by_fd(fd, &list);
	if (this_list)
	{
		if (ft_get_endline_index(this_list->tmp_string) < 0)
			read_file_to_list(this_list);
		if (this_list->tmp_string)
			ret_string = get_ret_string(this_list);
		if (!this_list->tmp_string)
			delete_list(&list, &this_list);
		return (ret_string);
	}
	return (NULL);
}
