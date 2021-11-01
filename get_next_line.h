#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE	10

typedef struct	s_list
{
	char			*string;
	char			*ret_string;
	int				fd;
	struct s_list	*next;
}	t_list;

#endif
