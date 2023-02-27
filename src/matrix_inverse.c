/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:09:52 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/27 22:17:39 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	set_pivot_to_nonzero(int col, float **matrix, float **inverse);
static void	reduce_under_diagonal(float **matrix, float **inverse);
static void	scale_pivots(float **matrix, float **inverse);
static void	reduce_above_diagnonal(float **matrix, float **inverse);

/**
 * @brief Invert matrix with Gauss-Jordan method.
 * 
 * @param input 
 * @return float** 
 */
float	**m44_invert(float **input, t_meta *m)
{
	float	**matrix;
	float	**inverse;
	int		cols;

	matrix = exit_on_null(m44_copy(input), m);
	inverse = exit_on_null(m44_init(), m);
	cols = 0;
	while (cols < 4)
	{
		if (matrix[cols][cols] == 0)
		{
			if (!set_pivot_to_nonzero(cols, matrix, inverse))
				return (ft_printf("Matrix inverse failed!\n"), NULL);
		}
		cols++;
	}
	reduce_under_diagonal(matrix, inverse);
	scale_pivots(matrix, inverse);
	reduce_above_diagnonal(matrix, inverse);
	m44_free(matrix);
	return (inverse);
}

/**
 * @brief	Subfunction for m44_inverse. Gets called whenever a pivot
 * 			of a matrix (ie m[1,1] or m[3,3]) is zero. Swaps it out for the 
 * 			highest absolute number in the column of the given pivot, unless
 * 			this puts a zero on a pivot place left of the current column.
 * 			Returns zero if no swap is possible.
 * 
 * @param col 
 * @param matrix 
 * @param inverse 
 * @return int 
 */
static int	set_pivot_to_nonzero(int col, float **matrix, float **inverse)
{
	float	*buf;
	int		biggest_row;
	int		row;

	biggest_row = col;
	row = 0;
	while (row < 4)
	{
		if (fabsf(matrix[row][col]) > fabsf(matrix[biggest_row][col]))
			if (!(row < col && matrix[col][row] == 0))
				biggest_row = row;
		row++;
	}
	if (biggest_row == col)
		return (0);
	buf = matrix[biggest_row];
	matrix[biggest_row] = matrix[col];
	matrix[col] = buf;
	buf = inverse[biggest_row];
	inverse[biggest_row] = inverse[col];
	inverse[col] = buf;
	return (1);
}

/**
 * @brief	Reduce all coefficients under the diagonal to zero.
 * 
 * @param matrix 
 * @param inverse 
 */
static void	reduce_under_diagonal(float **matrix, float **inverse)
{
	int		cols;
	int		rows;
	int		i;
	float	reducer;

	cols = 0;
	i = 0;
	while (cols < 3)
	{
		rows = cols + 1;
		while (rows < 4)
		{
			reducer = matrix[rows][cols] / matrix[cols][cols];
			while (i < 4)
			{
				matrix[rows][i] -= reducer * matrix[cols][i];
				inverse[rows][i] -= reducer * inverse[cols][i];
				i++;
			}
			matrix[rows][cols] = 0;
			i = 0;
			rows++;
		}
		cols++;
	}
}

/**
 * @brief Scale all pivots to 1.
 * 
 * @param matrix 
 * @param inverse 
 */
static void	scale_pivots(float **matrix, float **inverse)
{
	int		cols;
	int		rows;
	float	reducer;

	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		reducer = matrix[rows][rows];
		while (cols < 4)
		{
			matrix[rows][cols] /= reducer;
			inverse[rows][cols] /= reducer;
			cols++;
		}
		cols = 0;
		rows++;
	}
}

/**
 * @brief	Reduce all coefficients above the diagonal to 0
 * 
 * 
 * @param matrix 
 * @param inverse 
 */
static void	reduce_above_diagnonal(float **matrix, float **inverse)
{
	int		rows;
	int		cols;
	int		i;
	float	reducer;

	rows = 0;
	i = 0;
	while (rows < 4)
	{
		cols = rows + 1;
		while (cols < 4)
		{
			reducer = matrix[rows][cols];
			while (i < 4)
			{
				matrix[rows][i] -= matrix[cols][i] * reducer;
				inverse[rows][i] -= inverse[cols][i] * reducer;
				i++;
			}
			matrix[rows][cols] = 0;
			i = 0;
			cols++;
		}
		rows++;
	}
}
