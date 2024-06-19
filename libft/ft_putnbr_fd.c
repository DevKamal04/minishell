/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:19:38 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/13 13:44:56 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char			str[11];
	unsigned int	nbr;
	int				i;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	i = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		nbr = (unsigned int)(-n);
	}
	else
		nbr = (unsigned int)n;
	while (nbr > 0)
	{
		str[i++] = (nbr % 10) + '0';
		nbr /= 10;
	}
	while (--i >= 0)
		write(fd, &str[i], 1);
}
