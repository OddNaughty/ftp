/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:53:55 by cwagner           #+#    #+#             */
/*   Updated: 2014/03/27 11:57:28 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char			*cp1;
	unsigned const char		*cp2;

	cp1 = s1;
	cp2 = s2;
	while (n--)
		*cp1++ = *cp2++;
	return (s1);
}
