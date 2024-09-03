#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minirt.h"
#include "list.h"
#include "sphere.h"
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
	t_camera	camera = init_camera(image);

	// Object list - fake list for now
	t_list *list;
	list = malloc(sizeof(t_list));
	t_sphere *data = new_sphere(vec3(0, 0, -1), 0.5);
	list->data = data;
	list->next = NULL;
	list->type = SPHERE;

	t_list *list_temp;
	list_temp = malloc(sizeof(t_list));
	t_sphere *data_temp = new_sphere(vec3(0, -100.5, -1), 100);
	list_temp->data = data_temp;
	list_temp->next = NULL;
	list_temp->type = SPHERE;
	list->next = list_temp;

	render(camera, image, list);
}