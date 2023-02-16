/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:58:20 by avan-and          #+#    #+#             */
/*   Updated: 2023/02/16 16:10:39 by avan-and         ###   ########.fr       */
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

t_pixel	*point_to_pix(t_meta *m)
{
	int		cols;
	int		rows;
	int		i;
	t_list	*head;
	t_pixel	*res;
	t_point	*point;

// ft_printf("ptp1\n");
	cols = m->drawing_w;
	rows = m->drawing_h;
	head = m->points;
	res = malloc(sizeof(t_pixel) * (m->drawing_w * m->drawing_h));
	i = m->drawing_w * m->drawing_h - 1;
	// ft_printf("size: %i\n", m->drawing_w * m->drawing_h);
	if (res == NULL)
		exit_error(ERROR_MEM);
		// ft_printf("ptp2\n");
	while (rows > 0)
	{
		while (cols > 0)
		{
			point = (t_point *)head->content;
			// ft_printf("point: %f, %f, %f\n", point->x, point->y, point->z);
			res[i].x = point->x / point->z;
			res[i].y = point->y / point->z;
			res[i].color = point->color;
			res[i].enabled = 1;
			if (point->z < 0)
				res[i].enabled = 0;
			// ft_printf("%i: %i, %i @ %#x\n", i, res[i].x, res[i].y, res[i].color);
			head = head->next;
			i--;
			cols--;
		}
		rows--;
		cols = m->drawing_w;
	}	
	// ft_printf("ptp3: %i\n", i);
	return (res);
}
