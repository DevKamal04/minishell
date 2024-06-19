/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:41:57 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/13 13:44:22 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*char_ptr1;
	const unsigned char	*char_ptr2;

	i = 0;
	char_ptr1 = s1;
	char_ptr2 = s2;
	while (i < n)
	{
		if (char_ptr1[i] != char_ptr2[i])
		{
			if (char_ptr1[i] < char_ptr2[i])
				return (char_ptr1[i] - char_ptr2[i]);
			else
				return (char_ptr1[i] - char_ptr2[i]);
		}
		i++;
	}
	return (0);
}
