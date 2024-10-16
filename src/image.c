/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:24:50 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:24:51 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
