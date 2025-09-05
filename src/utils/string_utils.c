#include "../../include/cub3d.h"

int	is_equal(char *str1, char *str2)
{
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	if (!ft_strncmp(str1, str2, ft_strlen(str2)))
		return (1);
	return (0);
}

char	*get_first_word(char *line)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	end = i;
	return (ft_substr(line, start, end - start));
}
