#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"
#include "list.h"
#include "sphere.h"
#include "plane.h"
#include "image.h"
#include "camera.h"

void displayProgressBar(int progress, int total) {
    int barWidth = 16;  // Width of the progress bar in characters
    float percentage = (float)(progress + 1) / total;  // Calculate the completion ratio
    int position = barWidth * percentage;  // Determine the current position on the bar

    // Print the progress bar
    printf("[");
    for (int i = 0; i < barWidth; i++) {
        if (i < position) printf("#");  // Filled portion of the bar
        else printf(" ");  // Unfilled portion of the bar
    }
    printf("] %d%%\r", (int)(percentage * 100));  // Print the percentage complete and carriage return

    fflush(stdout);  // Flush the output buffer to ensure immediate display
}

int	main(void)
{
	t_image		image = init_image(16.0 / 9.0, 400);
	t_camera	camera = init_camera(image, 90.0);

	// Object list - fake list for now
	t_list *list;
	t_list *temp;

	t_sphere *data = new_sphere(vec3(0, 0, -1), 0.5);
	temp = new_list(data, SPHERE);
	list_add(&list, temp);

	t_sphere *data_1 = new_sphere(vec3(0, -100.5, -1), 100);
	temp = new_list(data_1, SPHERE);
	list_add(&list, temp);

	t_sphere *data_2 = new_sphere(vec3(2.5, 1.5, -2), 0.25);
	temp = new_list(data_2, SPHERE);
	list_add(&list, temp);

	//t_plane *data_3 = new_plane(vec3(0, -2, -1), vec3(2, 2, 0), vec3(0.5, 0.5, 0));
	// temp = new_list(data_3, PLANE);
	// list_add(&list, temp);

	render(camera, image, list);
}