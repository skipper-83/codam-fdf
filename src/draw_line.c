/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 22:16:59 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/20 21:40:37 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// http://tech-algorithm.com/articles/drawing-line-using-bresenham-algorithm/

/**
 * @brief	Initiate x/y_step1/2 to zero. Set step to positive if
 * 			delta (width/height) is positieve and vice versa if negative.
 *			y_step2 is set in set_longest_shortest_numerator.
 * 
 * @param line 
 */
static void	set_step(t_line *line)
{
	line->x_step1 = 0;
	line->y_step1 = 0;
	line->x_step2 = 0;
	line->y_step2 = 0;
	if (line->width > 0)
	{
		line->x_step1 = 1;
		line->x_step2 = 1;
	}
	else if (line->width < 0)
	{
		line->x_step1 = -1;
		line->x_step2 = -1;
	}
	if (line->height > 0)
		line->y_step1 = 1;
	else if (line->height < 0)
		line->y_step1 = -1;
}

/**
 * @brief	Find out whether width or height is the longest
 * 			distance. Set y_step2 if height > width, and change
 * 			x_step2 to zero.
 * 			Bit shifting is faster than dividing by 2, hence the >> 1.
 * 
 * @param line Line struct passed as pointer.
 */
static void	set_longest_shortest_numerator(t_line *line)
{
	line->longest = ft_abs(line->width);
	line->shortest = ft_abs(line->height);
	if (line->shortest > line->longest)
	{
		line->longest = ft_abs(line->height);
		line->shortest = ft_abs(line->width);
		if (line->height > 0)
			line->y_step2 = 1;
		else if (line->height < 0)
			line->y_step2 = -1;
		line->x_step2 = 0;
	}
	line->numerator = line->longest >> 1;
}

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

int	delta_color(int color1, int color2, int steps)
{
	float	delta_red;
	float	delta_green;
	float	delta_blue;
	float	delta_alpha;

	delta_red = get_red(color2) - get_red(color1);
	delta_green = get_green(color2) - get_green(color1);
	delta_blue = get_blue(color2) - get_blue(color1);
	delta_alpha = get_alpha(color2) - get_alpha(color1);
	delta_red = get_red(color1) + delta_red / steps;
	delta_green = get_green(color1) + delta_green / steps;
	delta_blue = get_blue(color1) + delta_blue / steps;
	delta_alpha = get_alpha(color1) + delta_alpha / steps;
	return (make_color((int)delta_red, (int)delta_green, \
							(int)delta_blue, (int)delta_alpha));
}

/**
 * @brief	Draw line using Bresenhem algorithm. Works for all octals.
 * 			Numerator starts as half of longest from width and length,
 * 			adds shortest to numerator for every step. If numerator is
 * 			larger than longest (ie when quotient of numerator and longest
 * 			is larger than 1), write pixel for shortest (width or length)
 * 			and substract longest from numerator.
 * 			x/y_step2 are set to zero by default, if width is longest x will
 * 			be 1, if height is longest y will be 1.
 * 
 * @param px1 
 * @param px2 
 */
void	draw_line(mlx_image_t *img, t_pixel px1, t_pixel px2)
{
	t_line	line;
	int		i;
	int		color_step;
	t_pixel	buf;

	if ((px1.x == px2.x && px1.y == px2.y) || !px1.enabled || !px2.enabled)
		return ;
	if (px1.y > HEIGHT || px1.x > WIDTH || px1.x < 0 || px1.y < 0)
	{
		buf = px1;
		px1 = px2;
		px2 = buf;
	}
	line.width = px2.x - px1.x;
	line.height = px2.y - px1.y;
	set_step(&line);
	// ft_printf("width %i height %i step\n", line.width, line.height, line.step);
	set_longest_shortest_numerator(&line);
	// color_step = (px1.color - px2.color) / line.longest; //  to be fixed
	i = 0;
	while (i <= line.longest)
	{
		line.numerator += line.shortest;
		put_pixel_safe(img, px1);
		if (line.numerator >= line.longest)
		{
			line.numerator -= line.longest;
			px1.y += line.y_step1;
			px1.x += line.x_step1;
		}
		else
		{
			px1.x += line.x_step2;
			px1.y += line.y_step2;
		}
		if (px1.x > WIDTH || px1.y > HEIGHT || px1.x < 0 || px1.y < 0)
			return ;
		px1.color = delta_color(px1.color, px2.color, line.longest - i);
		i++;
	}
}
