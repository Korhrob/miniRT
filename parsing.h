#ifndef PARSING_H
# define PARSING_H

# include "vector.h"
# include "color.h"

typedef struct s_parse
{
	char	id;
	t_vec3	pos;
	t_vec3	orien;
	t_color	color;
	double	v1;
	double	v2;
}	t_parse;

void	skip_spaces(char *line);
int	check_valid(char *line);
t_parse	set_info(char *line, t_parse *info);

#endif