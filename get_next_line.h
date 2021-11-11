#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	char			*tmp_string;
	int				fd;
	struct s_list	*next;
}	t_list;

char    *get_next_line(int fd);
#endif
