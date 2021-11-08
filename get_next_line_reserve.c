/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 06:43:19 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/02 22:33:00 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // test string

t_list	*list_add_back(t_list *list, int fd)
{
	t_list	*new_list;

	new_list = (t_list *) malloc(sizeof(t_list *));
	if (!new_list)
		return (NULL);
	new_list->string = NULL;
	new_list->ret_string = NULL;
	new_list->fd = fd;
	if (list)
		list->next = new_list;
	return (new_list);
}

int	ft_is_line(char *str, int len)
{
	int	i;

	i = 0;
	while (len - 1 > 0)
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
	char	zero_str[1];	
	char	*join;
	int		i;
	int		j;

	zero_str[0] = 0;
	j = 0;
	if (!string)
		string = zero_str;
	i = ft_strlen(buf) + ft_strlen(string);
	join = (char *)malloc(sizeof (char) * i + 1);
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
	return (join);
}

t_list	*find_list_by_fd(int fd, t_list *list)
{
	printf("find list begin list next %p\n", list->next); //test_string
	while (list->next && list->fd != fd)
		list = list->next;
	printf("find list after while\n"); //test_string
	if (list->fd != fd)
		list = list_add_back(list, fd);
	printf("find list after if\n"); //test_string
	return (list);
}

t_list	*read_file_to_list(int fd, t_list *list)
{
	char	buf[BUFFER_SIZE + 1];
	char	*string;
	int		readed_char_num;
	int		is_line;
	int		i;

	is_line = 0;
	while (!is_line)
	{
		readed_char_num = read (fd, buf, BUFFER_SIZE);
		if (readed_char_num > 0)
		{
			buf[readed_char_num] = 0;
			is_line = ft_is_line(buf, readed_char_num);
			list->string = ft_strjoin(buf, list->string);
		}
	}
	return (list);
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
	printf("stringlen in fill_ret_str %d\n", string_len); //test_string
	pos = 0;
	i = 0;
	while (list->string[pos] != '\n' && list->string[pos])
		pos++;
	printf("pos in fill_ret_str %d\n", pos); //test_string
	if (list->ret_string)
		free(list->ret_string);
	list->ret_string = (char *)malloc(sizeof (char) * pos + 1);
	printf("after malloc in fill_ret_str\n"); //test_string
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
	static t_list	*list;
	t_list			*this_list;

	printf("bufsize %d\n", BUFFER_SIZE); //test_string
	printf("fd %d\n", fd); //test_string

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	printf("after first if\n"); //test_string
	if (!list)
		list = list_add_back(NULL, fd);
	if (!list)
		return (NULL);
	printf("after second if\n"); //test_string
	this_list = find_list_by_fd(fd, list);
	printf("after find list\n"); //test_string
	if (!this_list->string || !this_list->string[0])
		read_file_to_list(fd, this_list);
	printf("after read file to list\n"); //test_string
	printf("readed string ---%s---\n", this_list->string); //test_string
	if (!this_list->string)
	{
		clear_lists(fd, &this_list, &list);
		return (NULL);
	}
	fill_ret_string_in_list(this_list);
	return (this_list->ret_string);
}
