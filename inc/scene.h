#ifndef SCENE_H
# define SCENE_H

#include "light.h"
#include "list.h"

typedef struct s_scene
{
	t_light	ambient;
	t_light	light;
	t_list	*objects;
}	t_scene;


#endif