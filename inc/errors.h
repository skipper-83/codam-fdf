/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:21:40 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/27 22:01:51 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "fdf.h"

# define ERROR_FILE "Erroneous map file provided"
# define ERROR_MEM "Memory allocation error"
# define ERROR_MAP_SQUARE "Map not rectangular"
# define ERROR_MAP_NUMBERS "Map does not contain all numbers"
# define ERROR_MLX "Error in MLX42 function"
# define ERROR_NO_MAP "No map provided! Usage: ./fdf [PATH_TO_MAP]"
# define ERROR_PATH "Path to map is corrupt!"
# define ERROR_MAP_CORRUPT "Map file is corrupt!"

#endif