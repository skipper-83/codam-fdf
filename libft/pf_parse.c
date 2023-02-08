/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:24:41 by albertvanan       #+#    #+#             */
/*   Updated: 2022/11/17 14:35:59 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/**
 * @brief	As printf, but homebrewn. 
 * 			Writes input string with all parameters passed
 * 			(Width, precision, #- 0 work as do l, ll h, hh and z)
 * 			Return length of the string written
 * 
 * @param input 
 * @param ... 
 * @return int 
 */
int	ft_printf(const char *input, ...)
{
	va_list	ap;
	char	*res;
	size_t	rlen;

	va_start(ap, input);
	rlen = 0;
	res = parse(input, ap, &rlen);
	va_end(ap);
	if (res == NULL)
		return (-1);
	rlen = write(1, res, rlen);
	free(res);
	return (rlen);
}

/**
 * @brief 	As sprintf, but homebrewn. 
 * 			Writes input string with all parameters passed
 * 			(Width, precision, #- 0 work as do l, ll h, hh and z)
 * 			Put string in *ret
 * 			Return length of the string written
 * 
 * @param ret 
 * @param input 
 * @param ... 
 * @return int 
 */
int	ft_sprintf(char *ret, const char *input, ...)
{
	va_list	ap;
	char	*res;
	size_t	rlen;

	va_start(ap, input);
	rlen = 0;
	res = parse(input, ap, &rlen);
	va_end(ap);
	if (res == NULL)
		return (-1);
	ft_strlcpy(ret, res, rlen + 1);
	free(res);
	return (rlen);
}

/**
 * @brief 	Parse through input string, call function convert()
 * 			to create the conversions when an % is found
 * 
 * @param input 
 * @param ap 
 * @param rlen 
 * @return char* 
 */
char	*parse(const char *input, va_list ap, size_t *rlen)
{
	size_t	ilen;
	size_t	slen;
	char	*res;

	ilen = 0;
	slen = 0;
	res = NULL;
	while (input[ilen])
	{
		if (input[ilen] == '%')
		{
			res = stitch(res, ft_substr(input, ilen - slen, slen), rlen, slen);
			if (res == NULL)
				return (NULL);
			ilen++;
			res = stitch(res, convert(input, ap, &ilen, &slen), rlen, slen);
			if (res == NULL)
				return (NULL);
			slen = 0;
		}
		else
			slen++;
		ilen++;
	}
	return (stitch(res, ft_substr(input, ilen - slen, slen), rlen, slen));
}

/**
 * @brief 	Parse conversion: set the correct flags and subsequently
 * 			call select_conversion to select the correct handler function
 * 			for the conversion at hand. Supperted [csdiuxXp]
 * 
 * @param input 
 * @param ap 
 * @param ilen 
 * @param slen 
 * @return char* 
 */
char	*convert(char const *input, va_list ap, size_t *ilen, size_t *slen)
{
	char	*res;
	t_flags	*flags;

	res = NULL;
	flags = (t_flags *)ft_calloc(1, sizeof(t_flags));
	if (flags == NULL)
		return (NULL);
	while (set_flags(input[*ilen], flags))
		(*ilen)++;
	if (input[*ilen] == '*')
	{
		flags->width = -1;
		++(*ilen);
	}
	else if (ft_isdigit(input[*ilen]))
		flags->width = ft_atoi(&input[*ilen]);
	while (ft_isdigit(input[*ilen]))
		++(*ilen);
	set_precision_type(input, flags, ilen);
	if (flags->type)
		res = select_conversion(ap, flags, slen);
	else
		return (free(flags), --(*ilen), ft_strdup(""));
	return (free(flags), res);
}
