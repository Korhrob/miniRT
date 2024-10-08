#ifndef PARSING_H
# define PARSING_H

# include "vector.h"
# include "color.h"

typedef enum e_id
{
	NONE,
	ID_AMBIENT,
	ID_CAMERA,
	ID_LIGHT,
	ID_SPHERE,
	ID_PLANE,
	ID_CYLINDER,
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

int 	create_vector(char *str, t_vec3 *out);
int		parse_ambient(char **arr, t_parse *info);
int		parse_camera(char **arr, t_parse *info);
int		parse_light(char **arr, t_parse *info);
int		parse_sphere(char **arr, t_parse *info);
int		parse_plane(char **arr, t_parse *info);
int		parse_cylinder(char **arr, t_parse *info);

#endif