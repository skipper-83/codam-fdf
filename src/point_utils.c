/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:58:20 by avan-and          #+#    #+#             */
/*   Updated: 2023/02/20 01:43:19 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_pixel	point_to_pixel(t_point *point, t_meta *m)
{
	t_point	point_transformed;
	t_pixel	res;
	float	x;
	float	y;
	float	z;

	point_transformed.x = point->x;
	point_transformed.y = point->y;
	point_transformed.z = point->z;
	m44_multiply_point(m->transformer, &point_transformed);
	// ft_printf("point: %f, %f, %f\n", point_transformed.x, point_transformed.y, point_transformed.z);
	x = point_transformed.x / point_transformed.z;
	y = point_transformed.y / point_transformed.z;
	x = (x + CANVAS_W / 2) / CANVAS_W;
	y = (y + CANVAS_H / 2) / CANVAS_H;
	res.x = x * WIDTH;
	res.y = y * HEIGHT;
	res.color = point->color;
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
	res = malloc(sizeof(t_pixel) * (m->total_px));
	i = m->total_px - 1;
	inverse = m44_invert(m->camera);
	if (inverse == NULL)
		exit_error(ERROR_MEM);
	m44_free(m->transformer);
	m->transformer = m44_dot_product(m->world, inverse, KEEP_M1);
	if (m->transformer == NULL)
		exit_error(ERROR_MEM);
	while (i >= 0)
	{
		res[i] = point_to_pixel((t_point *)head->content, m);
		head = head->next;
		i--;
	}
	m44_free(inverse);
	return (res);
}
