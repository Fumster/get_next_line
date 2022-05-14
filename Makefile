SOURCES =		get_next_line.c get_next_line_utils.c

HEADER =		get_next_line.h

CC		=		gcc

NAME =			libgetnextline.a

OBJECTS	=		$(SOURCES:.c=.o)

FLAGS =			-Wall -Wextra -Werror

.PHONY: all re clean fclean

all	:			$(NAME)


$(NAME)	:		$(OBJECTS)
					ar -rc $(NAME) $^

%.o :	%.c $(HEADER)
		$(CC) $(FLAGS) $< -c

clean :
					rm -rf $(OBJECTS)

fclean :		clean
					rm -rf $(NAME)

re:				fclean all
