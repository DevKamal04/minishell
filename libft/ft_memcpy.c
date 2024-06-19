/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:16:11 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/13 13:44:32 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	char				*char_dest;
	const char			*char_src;

	char_src = (char *) src;
	char_dest = (char *) dest;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (n > 0)
	{
		char_dest[i] = char_src[i];
		i++;
		n--;
	}
	return (dest);
}
