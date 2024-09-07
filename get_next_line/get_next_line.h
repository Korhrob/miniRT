#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

struct s_read_buffer
{
	int		index;
	int		start;
	int		bytes;
	char	*str;
};

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void		*ft_memset(void *b, int c, size_t len);
size_t		ft_strlen(const char *str);
char		*init_str(char **src, int add_len);
char		*copy_str(char *dest, struct s_read_buffer *buffer, int add_len);

void		init_buffer(int fd, struct s_read_buffer *buffer);
void		*free_buffer(struct s_read_buffer *buffer, char **output);
void		*malloc_fail(char *str, struct s_read_buffer *buffer);
char		*get_next_line(int fd);

#endif