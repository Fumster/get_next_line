/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchrysta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:51:59 by fchrysta          #+#    #+#             */
/*   Updated: 2021/11/22 21:59:26 by fchrysta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*tmp_string;
	int				fd;
	struct s_list	*next;
}	t_list;

int		ft_strlen(char *str);
int		ft_get_endline_index(char *str);
char	*cut_line(char *src, int begin, int end);
char	*append_lines(char *begin, char *end);
char	*get_next_line(int fd);
char	*cpy_string(char *str, int len);
#endif
