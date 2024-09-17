

#include <fcntl.h> // open
#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <unistd.h> // close

#include "image.h"

t_image	init_image(double aspect_ratio, int width)
{
	t_image	image;

	image.aspect_ratio = 16.0 / 9.0;
	image.width = width;

	image.height = (int)((double)width / aspect_ratio);
	if (image.height < 1)
		image.height = 1;
	return (image);
}
