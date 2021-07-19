#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
int		check_memo(char *memo);
int		free_and_return(char **tmp);
int		get_next_line(int fd, char **line);
#endif