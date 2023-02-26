/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_schemes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 00:00:26 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/26 14:21:54 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	weird_purple_colors(float z)
{
	if (z > 100)
		return (0xFFDF8DFF);
	if (z > 75)
		return (0xFFDE7AFF);
	if (z > 50)
		return (0xFFC568FF);
	if (z > 25)
		return (0xFD996BFF);
	if (z > 15)
		return (0xF7856CFF);
	if (z > 10)
		return (0xF06E6CFF);
	if (z > 5)
		return (0xD9576BFF);
	if (z > 0)
		return (0xA44369FF);
	if (z > -10)
		return (0x833F68FF);
	if (z > -20)
		return (0x833F68FF);
	if (z > -50)
		return (0x5E3C65FF);
	return (0x3F3A63FF);
}

int	rainbow(float z)
{
	if (z > 100)
		return (0xff0000ff);
	if (z > 75)
		return (0xff8000ff);
	if (z > 50)
		return (0xffff00ff);
	if (z > 25)
		return (0x80ff00ff);
	if (z > 15)
		return (0x00ff00ff);
	if (z > 10)
		return (0x00ff80ff);
	if (z > 5)
		return (0x00ffffff);
	if (z > 0)
		return (0x0080ffff);
	if (z > -10)
		return (0x0000ffff);
	if (z > -20)
		return (0x8000ffff);
	if (z > -50)
		return (0xff00ffff);
	return (0xff0080ff);
}

int	atlas_colors(float z)
{
	if (z > 100)
		return (0xe5c7bcff);
	if (z > 75)
		return (0xf1c9b0ff);
	if (z > 50)
		return (0xf3d7a2ff);
	if (z > 25)
		return (0xfcfbbdff);
	if (z > 15)
		return (0xfff7e4ff);
	if (z > 10)
		return (0xdfeeddff);
	if (z > 5)
		return (0xd4e6deff);
	if (z > 0)
		return (0xb4dacdff);
	if (z > -10)
		return (0x93c1b6ff);
	if (z > -20)
		return (0x84b9aeff);
	if (z > -50)
		return (0x4fad93ff);
	return (0xecefe8ff);
}

int	minecraft_colors(float z)
{
	if (z > 70)
		return (0xE9EAF0FF);
	if (z > 62)
		return (0xC4C1BDFF);
	if (z > 50)
		return (0x4C591AFF);
	if (z > 10)
		return (0x4C591AFF);
	if (z > 1)
		return (0x4D5E36FF);
	if (z > 0)
		return (0xD8D19CFF);
	if (z > -5)
		return (0x444CC6FF);
	if (z > -10)
		return (0x2A2EAEFF);
	if (z > -30)
		return (0x3D497CFF);
	return (0x05093dFF);
}
