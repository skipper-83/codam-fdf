/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:45:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/21 11:01:23 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_red(int color)
{
	return ((color >> 24) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_blue(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_alpha(int color)
{
	return (color & 0xFF);
}

int	make_color(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
