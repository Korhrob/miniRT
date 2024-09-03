

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

	printf("create file\n");
	image.fd = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (image.fd == -1)
	{
		printf("failed to create file\n");
		exit(1);
	}
	close(image.fd);
	image.fd = open("image.ppm", O_WRONLY | O_CREAT | O_APPEND);
	dprintf(image.fd, "P3\n%d %d\n255\n", image.width, image.height);
	return (image);
}