#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	char *string;
	struct s_list	*next;
}	t_list;

#endif
