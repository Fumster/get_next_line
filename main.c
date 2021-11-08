#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main ()
{
	int fd;
	char *string;

	fd = open("test.txt", O_RDONLY);
	string = get_next_line(fd);
	printf("\nfirst return is ----%s----\n\n", string);
	string = get_next_line(fd);
	printf("\nsecond return is ----%s----\n\n", string);
	string = get_next_line(fd);
	printf("\nthird return is ----%s----\n\n", string);
	string = get_next_line(fd);
	printf("\nforth return is ----%s----\n\n", string);
}
