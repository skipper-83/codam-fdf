/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scheme_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:13:48 by avan-and          #+#    #+#             */
/*   Updated: 2023/02/27 14:35:57 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_color_scheme(t_meta *m, int (*scheme)(float z))
{
	t_list	*head;
	t_point	*point;

	head = m->points;
	while (head)
	{
		point = (t_point *)head->content;
		point->color = scheme(point->z);
		head = head->next;
	}
}

void	cycle_colorschemes(t_meta *m)
{
	static const t_color_scheme	schemes[5] = {
		weird_purple_colors,
		minecraft_colors,
		atlas_colors,
		rainbow,
		NULL
	};
	static int					selector;

	m->color_scheme = schemes[selector];
	selector++;
	if (selector == 5)
		selector = 0;
	create_new_image(m);
}

void	fade_alpha_with_z(t_point p, t_pixel *px)
{
	int		alpha;
	float	coeff;
	int		offset;

	offset = 1;
	coeff = p.z * 0.5;
	if (coeff < offset)
		return ;
	alpha = 255 - (coeff - offset);
	px->color = px->color >> 8;
	px->color = px->color << 8;
	if (alpha > 0)
		px->color += alpha;
}
