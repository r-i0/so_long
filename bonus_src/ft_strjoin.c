#include "../include/so_long_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*joined_str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	joined_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined_str)
		return (0);
	while (s1[i])
	{
		joined_str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		joined_str[i + j] = s2[j];
		j++;
	}
	joined_str[i + j] = '\0';
	return (joined_str);
}
