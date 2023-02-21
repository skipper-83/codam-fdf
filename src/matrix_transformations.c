/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:28:29 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/21 11:00:46 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Rotate matrix over axis [axis] with angle [angle] (in degrees)
 * 
 * @param matrix 
 * @param angle 
 * @param axis 
 */
void	m44_rotate(float **matrix, float angle, char axis)
{
	if (axis == 'x')
	{
		matrix[1][1] = cos(ft_rad(angle));
		matrix[1][2] = sin(ft_rad(angle));
		matrix[2][1] = -1 * sin(ft_rad(angle));
		matrix[2][2] = cos(ft_rad(angle));
	}
	if (axis == 'y')
	{
		matrix[0][0] = cos(ft_rad(angle));
		matrix[0][2] = -1 * sin(ft_rad(angle));
		matrix[2][0] = sin(ft_rad(angle));
		matrix[2][2] = cos(ft_rad(angle));
	}
	if (axis == 'z')
	{
		matrix[0][0] = cos(ft_rad(angle));
		matrix[0][1] = sin(ft_rad(angle));
		matrix[1][0] = -1 * sin(ft_rad(angle));
		matrix[1][1] = cos(ft_rad(angle));
	}
}

/**
 * @brief Scale matrix
 * 
 * @param matrix 
 * @param x 
 * @param y 
 * @param z 
 */
void	m44_scale(float **matrix, float x, float y, float z)
{
	matrix[0][0] *= x;
	matrix[1][1] *= y;
	matrix[2][2] *= z;
}

/**
 * @brief Translate matrix
 * 
 * @param matrix 
 * @param x 
 * @param y 
 * @param z 
 */
void	m44_translate(float **matrix, float x, float y, float z)
{
	matrix[3][0] += x;
	matrix[3][1] += y;
	matrix[3][2] += z;
}

float	ft_rad(float angle)
{
	return (angle * (M_PI / 180.0));
}
