/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:32:58 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/24 23:21:48 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Initialize a 4x4 matrix as identity matrix
 * 			(so all pivots are set to 1, the rest to 0)
 * 
 * @return float** 
 */
float	**m44_init(void)
{
	float		**res;
	int			rows;
	int			cols;

	rows = 0;
	cols = 0;
	res = ft_calloc(4, sizeof(float *));
	if (res == NULL)
		return (NULL);
	while (rows < 4)
	{
		res[rows] = ft_calloc(4, sizeof(float));
		if (res[rows] == NULL)
			return (m44_free(res), NULL);
		while (cols < 4)
		{
			if (cols == rows)
				res[rows][cols] = 1;
			cols++;
		}
		cols = 0;
		rows++;
	}
	return (res);
}

/**
 * @brief Free a 4x4 matrix
 * 
 * @param matrix 
 */
void	m44_free(float **matrix)
{
	int	rows;

	rows = 0;
	while (matrix[rows] && rows < 4)
		free(matrix[rows++]);
	free (matrix);
	matrix = NULL;
}

/**
 * @brief	Copies a 4*4 matrix.
 * 
 * @param matrix 
 * @return float** 
 */
float	**m44_copy(float **matrix)
{
	int		rows;
	int		cols;
	float	**res;

	rows = 0;
	cols = 0;
	res = m44_init();
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

/**
 * @brief	Returns dot product of two matrices. Set free_m1 to 1
 * 			to free the first input matrix, so you can write
 * 
 * 			m1 = m44_dot_product(m1, m2, 1);
 * 
 * 			without leaking memory.
 * 
 * @param m1 
 * @param m2 
 * @param free_m1 
 * @return float** 
 */
float	**m44_dot_product(float **m1, float **m2, int free_m1)
{
	float	**product;
	int		rows;
	int		cols;

	product = m44_init();
	if (product == NULL)
		return (NULL);
	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		while (cols < 4)
		{
			product[rows][cols] = m1[rows][0] * m2[0][cols] + \
									m1[rows][1] * m2[1][cols] + \
									m1[rows][2] * m2[2][cols] + \
									m1[rows][3] * m2[3][cols];
			cols++;
		}
		cols = 0;
		rows++;
	}
	if (free_m1)
		m44_free(m1);
	return (product);
}

void	m44_to_identity_matrix(float **matrix)
{
	int	rows;
	int	cols;

	rows = 0;
	while (rows < 4)
	{
		cols = 0;
		while (cols < 4)
		{
			if (rows == cols)
				matrix[rows][cols] = 1;
			else
				matrix[rows][cols] = 0;
			cols++;
		}
		rows++;
	}
}

// int	m44_is_identity_matrix(float **matrix)
// {
// 	int	rows;
// 	int	cols;

// 	rows = 0;
// 	while (rows < 4)
// 	{
// 		cols = 0;
// 		while (cols < 4)
// 		{
// 			if (rows == cols)
// 			{
// 				if (matrix[rows][cols] != 1)
// 					return (0);
// 			}
// 			else
// 				if (matrix[rows][cols] != 0)
// 					return (0);
// 			cols++;
// 		}
// 		rows++;
// 	}
// 	return (1);
// }
