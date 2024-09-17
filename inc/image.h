#ifndef IMAGE_H
# define IMAGE_H

typedef struct s_image
{
	double	aspect_ratio;
	int		width;
	int		height;
}	t_image;

t_image	init_image(double aspect_ratio, int width);

#endif