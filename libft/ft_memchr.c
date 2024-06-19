/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:07 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/11 14:11:04 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char		*src;
	unsigned char			uc;

	uc = c;
	src = (const unsigned char *) str;
	while (n-- > 0)
	{
		if (*src == uc)
			return ((void *)src);
		src++;
	}
	return (NULL);
}
