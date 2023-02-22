/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_schemes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:13:48 by avan-and          #+#    #+#             */
/*   Updated: 2023/02/22 23:39:08 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	cycle_colorschemes(t_meta *m)
{
	static const t_color_scheme	schemes[3] = {
		weird_purple_colors,
		minecraft_colors,
		NULL
	};
	static int					selector;

	m->color_scheme = schemes[selector];
	selector++;
	if (selector == 3)
		selector = 0;
	create_new_image(m);
}

void	fade_alpha_with_z(t_point p, t_pixel *px)
{
	int		alpha;
	float	coeff;
	int		offset;

	offset = 6;
	coeff = p.z * 3;
	if (coeff < offset)
		return ;
	alpha = 255 - (coeff - offset);
	px->color = px->color >> 8;
	px->color = px->color << 8;
	if (alpha > 0)
		px->color += alpha;
}

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
