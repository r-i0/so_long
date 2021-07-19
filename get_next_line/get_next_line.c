#include "get_next_line.h"

int	put_to_memo(char *str, char **memo)
{
	char	*joined;
	int		i;

	i = -1;
	if (!*memo)
		joined = (char *)malloc(ft_strlen(str) + 1);
	else
		joined = (char *)malloc(ft_strlen(str) + ft_strlen(*memo) + 1);
	if (!joined)
		return (-1);
	if (*memo)
	{
		while ((*memo)[++i])
			joined[i] = (*memo)[i];
		free(*memo);
	}
	else
		i++;
	ft_strlcpy(&joined[i], str, ft_strlen(str) + 1);
	*memo = ft_strdup(joined);
	free(joined);
	if (!*memo)
		return (-1);
	return (check_memo(*memo));
}

int	put_to_line(char **memo, char **line)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	while ((*memo)[i] != '\n')
		i++;
	*line = (char *)malloc(sizeof(char) * (i + 1));
	if (!*line)
		return (-1);
	ft_strlcpy(*line, *memo, i + 1);
	while ((*memo)[i + j] != '\0')
		j++;
	tmp = (char *)malloc(sizeof(char) * j);
	if (!tmp)
		return (-1);
	ft_strlcpy(tmp, &(*memo)[i + 1], j);
	free(*memo);
	*memo = ft_strdup(tmp);
	free(tmp);
	if (!*memo)
		return (-1);
	return (1);
}

int	check_memo(char *memo)
{
	if (!memo)
		return (0);
	if (ft_strchr(memo, '\n'))
		return (1);
	else
		return (0);
}

int	put_to_line_eof(char **memo, char **line)
{
	int	i;

	i = 0;
	*line = ft_strdup(*memo);
	free(*memo);
	*memo = NULL;
	if (!*line)
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*memo;
	char		*tmp;
	ssize_t		rc;
	int			sign;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	sign = check_memo(memo);
	rc = 1;
	while (sign == 0 && rc != 0 )
	{
		tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		rc = read(fd, tmp, BUFFER_SIZE);
		if (rc == -1)
			return (free_and_return(&tmp));
		tmp[rc] = '\0';
		sign = put_to_memo(tmp, &memo);
		free(tmp);
	}
	if (rc == 0 && sign >= 0)
		sign = put_to_line_eof(&memo, line);
	else if (ft_strchr(memo, '\n') && sign >= 0)
		sign = put_to_line(&memo, line);
	return (sign);
}
