/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:40:20 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/22 15:46:20 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_point(void *param)
{
	t_point		*point;
	static int	counter;

	point = (t_point *)param;
	ft_printf("% 3i: % 3i : % 3i : % 3i : %#x; \n", \
		counter++, point->x, point->y, point->z, point->color);
}

void	print_meta(t_meta *m)
{
	ft_printf("Metadata dump:\n\n");
	ft_printf("Filename: %s\n\n", m->filename);
	ft_printf("Drawing height %5i\n", m->drawing_h);
	ft_printf("Drawing width  %5i\n", m->drawing_w);
	ft_printf("Drawing depth  %5i\n\n", m->drawing_d);
	ft_printf("Z max: %i\n", m->max_z);
	ft_printf("Z min: %i\n", m->min_z);
	ft_printf("\n");
}

/**
 * @brief	Print a 4x4 matrix
 * 
 * @param matrix 
 */
void	m44_print(float **matrix)
{
	int	rows;
	int	cols;

	if (matrix == NULL)
	{
		ft_printf("Matrix empty.\n");
		return ;
	}
	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		while (cols < 4)
		{
			ft_printf("| % 7.3f |", matrix[rows][cols]);
			cols++;
		}
		ft_printf("\n");
		cols = 0;
		rows++;
	}
	ft_printf("\n");
}

/**
 * @brief	Takes a float[4][4] as argument and converts it to
 * 			a float**.
 * 
 * @param matrix 
 * @return float** 
 */
float	**m44_arr_to_pointer(float matrix[][4])
{
	float	**res;
	int		rows;
	int		cols;

	res = m44_init();
	rows = 0;
	cols = 0;
	if (res == NULL)
		return (NULL);
	while (rows < 4)
	{
		while (cols < 4)
		{
			res[rows][cols] = matrix[rows][cols];
			cols++;
		}
		cols = 0;
		rows++;
	}
	return (res);
}
