#ifndef PARSING_H
# define PARSING_H

# include "vector.h"
# include "color.h"

typedef enum e_id
{
	NONE,
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	ID_MAX
}	t_id;

typedef struct s_parse
{
	int		id;
	t_vec3	pos;
	t_vec3	orien;
	t_color	color;
	double	v1;
	double	v2;
}	t_parse;

int		check_valid(char *line);
void	set_info(char *line, t_parse *info);

#endif