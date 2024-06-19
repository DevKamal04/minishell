/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:10:44 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/13 13:38:21 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	ret;
	int				i;
	int				neg;

	i = 0;
	ret = 0;
	neg = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v' || \
		*str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = (str[i] - '0') + (10 * ret);
		i++;
		if ((neg * ret) > 4294967295)
			return (-1);
		if ((neg * ret) < -4294967295)
			return (0);
	}
	if (*str == '-')
		ret = ret * -1;
	return (ret);
}
