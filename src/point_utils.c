/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:58:20 by avan-and          #+#    #+#             */
/*   Updated: 2023/02/27 22:19:06 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	copy_point(t_point *src, t_point *dst);

/**
 * @brief	Multiply a point (3 dimension vector) by a 4x4 matrix
 * 
 * @param m the matrix
 * @param p the point
 */
void	m44_multiply_point(float **m, t_point *p)
{
	float	x;
	float	y;
	float	z;

	x = p->x * m[0][0] + p->y * m[1][0] + p->z * m[2][0] + m[3][0];
	y = p->x * m[0][1] + p->y * m[1][1] + p->z * m[2][1] + m[3][1];
	z = p->x * m[0][2] + p->y * m[1][2] + p->z * m[2][2] + m[3][2];
	p->x = x;
	p->y = y;
	p->z = z;
}

t_pixel	point_to_pixel_parallel(t_point *point, t_meta *m)
{
	t_point	point_tf;
	t_pixel	res;
	float	x;
	float	y;

	copy_point(point, &point_tf);
	m44_multiply_point(m->transformer, &point_tf);
	x = (point_tf.x - point_tf.y * cos(ft_rad(30))) / 15;
	y = ((-point_tf.z + point_tf.y + point_tf.x) * sin(ft_rad(30))) / 15;
	x = (x + m->canvas_w / 2) / m->canvas_w;
	y = (y + m->canvas_h / 2) / m->canvas_h;
	res.x = x * m->window_w;
	res.y = (1 - y) * m->window_h;
	if (m->color_scheme)
		res.color = m->color_scheme(point->z);
	else
		res.color = point->color;
	res.enabled = 1;
	return (res);
}

t_pixel	point_to_pixel_perspective(t_point *point, t_meta *m)
{
	t_point	point_transformed;
	t_pixel	res;
	float	x;
	float	y;

	copy_point(point, &point_transformed);
	m44_multiply_point(m->transformer, &point_transformed);
	x = point_transformed.x / -point_transformed.z;
	y = point_transformed.y / -point_transformed.z;
	x = (x + m->canvas_w / 2) / m->canvas_w;
	y = (y + m->canvas_h / 2) / m->canvas_h;
	res.x = x * m->window_w;
	res.y = (1 - y) * m->window_h;
	if (m->color_scheme)
		res.color = m->color_scheme(point->z);
	else
		res.color = point->color;
	if (m->fade_alpha)
		fade_alpha_with_z(point_transformed, &res);
	res.enabled = 1;
	if (point_transformed.z < 0)
		res.enabled = 0;
	return (res);
}

t_pixel	*points_to_pixels(t_meta *m)
{
	int		i;
	t_list	*head;
	t_pixel	*res;
	float	**inverse;

	head = m->points;
	res = exit_on_null(malloc(sizeof(t_pixel) * (m->total_px)), m);
	i = m->total_px - 1;
	inverse = exit_on_null(m44_invert(m->camera, m), m);
	m44_free(m->transformer);
	m->transformer = \
				exit_on_null(m44_dot_product(m->world, inverse, KEEP_M1), m);
	while (i >= 0)
	{
		if (m->projection == PERSPECTIVE)
			res[i] = point_to_pixel_perspective((t_point *)head->content, m);
		else
			res[i] = point_to_pixel_parallel((t_point *)head->content, m);
		head = head->next;
		i--;
	}
	m44_free(inverse);
	return (res);
}

static void	copy_point(t_point *src, t_point *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
	dst->color = src->color;
}
