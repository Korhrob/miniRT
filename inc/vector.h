/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkorhone <rkorhone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:35:15 by rkorhone          #+#    #+#             */
/*   Updated: 2024/10/03 15:35:16 by rkorhone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3	t_point;

t_vec3	vec3(double x, double y, double z);
t_vec3	vvec3(t_vec3 v);
t_vec3	v_mul(t_vec3 v, double t);
t_vec3	v_div(t_vec3 v, double t);
double	v_len(t_vec3 v);
double	v_len_squared(t_vec3 v);
t_vec3	vv_sum(t_vec3 a, t_vec3 b);
t_vec3	vv_sub(t_vec3 a, t_vec3 b);
t_vec3	vv_mul(t_vec3 a, t_vec3 b);
double	vv_dot(t_vec3 a, t_vec3 b);
t_vec3	unit_vector(t_vec3 v);
t_vec3	cross(t_vec3 a, t_vec3 b);

#endif
