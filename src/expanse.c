/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:33:06 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 05:03:59 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*init_flags(char *cmd, char **datal)
{
	char	*data;
	int		i;

	if (*datal)
		free(*datal);
	data = ft_strdup(cmd);
	i = -1;
	while (data[++i])
		data[i] = '0';
	return (data);
}

//main expander function

char	*ft_expand(char *cmd, char **data, t_terminal *terminal)
{
	int		i;
	char	*tmp;
	char	*var;

	i = 0;
	tmp = cmd;
	*data = init_flags(cmd, data);
	while (tmp[i])
	{
		i = single_q_check(tmp, i);
		if (exp_cond(tmp[i]))
		{
			var = ft_get(ft_substr(tmp, i + 1, ft_len(tmp + i + 1)), terminal);
			if (var)
			{
				tmp = ft_rep_str(tmp, i, var, data);
				i = i + ft_strlen(var);
			}
			else
				tmp = ft_rem_str(tmp, i, ft_len2(tmp + i), data);
		}
		else
			i++;
	}
	return (tmp);
}
