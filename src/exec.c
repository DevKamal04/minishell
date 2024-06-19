/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:36:34 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 11:07:48 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pp_strjoin(char *s1, char *s2, int free_flag)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = malloc(s1_len + s2_len + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy (dest, s1, s1_len + 1);
	ft_strlcpy (dest + s1_len, s2, s2_len + 1);
	if (free_flag & (1 << 0))
		free (s1);
	if (free_flag & (1 << 1))
		free (s2);
	return (dest);
}

char	*pp_arrcmp(void **arr, void *keyword)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (!ft_strncmp(keyword, arr[i], ft_strlen(keyword)))
			break ;
	}
	return (arr[i]);
}

char	*pp_path_helper(char *tmp)
{
	while (*tmp && *tmp != ':')
		tmp++;
	if (*tmp && *tmp == ':')
		*tmp++ = '\0';
	return (tmp);
}
