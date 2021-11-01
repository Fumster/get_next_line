/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 06:43:19 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/01 23:39:55 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*list_add_back(t_list *list, int fd)
{
	t_list	*new_list;
	new_list = (t_list *)malloc(sizeof (*t_list));
	if (!list)
		return (NULL);
	new_list->string = NULL;
	new_list->fd = fd;
	if (list)
		list->next = new_list;
	return (new_list);
}


int	ft_is_line(char *str, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		if (str[i] == '\n')
			return (1);
		i++;
		len --;
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *buf, char *string)
{
	char	*join;
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(buf) + ft_strlen(string);
	join = (char *)malloc(sizeof (char) * i + 1);
	i = 0;
	while (buf[i])
	{
		join[i] = buf[i];
		i++;
	}
	while (string [j])
	{
		join[i] = string[j];
		i++;
		j++;
	}
	return (join);
}


t_list	*find_list_by_fd(int fd, t_list *list)
{
	while (list->next && list->fd != fd)
		list = list->next;
	if (list->fd != fd)
		list = list_add_back(list, fd);
	return (list);
}

t_list	*read_file_to_list(int fd, t_list *list)
{
	char buf[BUFFER_SIZE + 1];
	char *string;
	int readed_char_num;
	int is_line;
	int i;
	
	is_line = 0;
	while (!is_line)
	{
		readed_char_num = read (fd, buf, BUFFER_SIZE);
		if  (readed_char_num > 0)
		{
			buf[readed_char_num] = 0;
			is_line = ft_is_line(buf, readed_char_num);
			list->string = ft_strjoin(buf, list->string);
		}
	}
	return (list);
}


char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*this_list;
	char			*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!list)
		list = list_add_back(NULL, fd);
	if (!list)
		return (NULL);
	this_list = find_list_by_fd(fd, list);
	if (!this_list.string || !this_list->string)
		read_file_to_list(fd, this_list);
	if (!this_list->string)
	{
		clear_list(this_list);
		if (this_list == list)
			list = NULL;
		this_list = NULL;
		return (NULL);
	}
	fill_ret_string_in_list(this_list);
	}
	line = this_list->string;//this string for test reading of file
	return (this_list->ret_string);
}
