/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:33:54 by rhorvath          #+#    #+#             */
/*   Updated: 2023/04/11 15:06:17 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char	*s, int c)
{
	char	*p;
	char	*ret;

	ret = 0;
	p = (char *)s;
	while (*p)
	{
		if (*p == (char)c)
			ret = p;
		p++;
	}
	if ((char)c == '\0')
		ret = p;
	return (ret);
}
