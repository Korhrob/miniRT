/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:27 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:34:27 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "vector.h"

typedef t_vec3	t_color;

t_color	color(double r, double g, double b);
double	linear_to_gamma(double lin);

#endif
