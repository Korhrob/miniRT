#ifndef PARSING_H
# define PARSING_H

# include "vector.h"
# include "color.h"
# include "scene.h"

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
	char	*line;
	char	*original;
}	t_parse;

int	check_valid(t_parse *info);
int	set_info(t_parse *info);

int		check_range(t_vec3 *vector, double min, double max);
int		create_vector(char *str, t_vec3 *out, double multi);
int		parse_ambient(char **arr, t_parse *info);
int		parse_camera(char **arr, t_parse *info);
int		parse_light(char **arr, t_parse *info);
int		parse_sphere(char **arr, t_parse *info);
int		parse_plane(char **arr, t_parse *info);
int		parse_cylinder(char **arr, t_parse *info);

void	init_ambient(t_scene *scene, t_parse info);
void	init_light(t_scene *scene, t_parse info);
void	init_plane(t_list **list, t_parse info, int *id);
void	init_sphere(t_list **list, t_parse info, int *id);
void	init_cylinder(t_list **list, t_parse info, int *id);

#endif