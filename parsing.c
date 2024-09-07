#include "parsing.h"
#include <stdio.h>

void	skip_spaces(char *line)
{
	while (*line == ' ')
		line++;
}

int	check_valid(char *line)
{
	if (!line)
		return (1);
	skip_spaces(line);
	if (*line == '\n')
		return (1);
	printf("Identifier = [%c%c]", *line, *(line+1));
	return (0);
}

int	count_form(char *str)
{
	int i;

	i = 0;
	while (str)
	{
		if (*str == ',')
			i++;
		str++;
	}
	return (i);
}

t_parse	set_info(char *line)
{
	t_parse	info;
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(line, ' ');
	info.id = arr[i];
	i++;
	
	return (info);
}