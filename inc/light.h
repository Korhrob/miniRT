/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:34:40 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:34:40 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"
# include "color.h"
# include "scene.h"
# include "hit.h"

t_color	calc_light(t_hit *rec, t_scene *scene);

#endif
