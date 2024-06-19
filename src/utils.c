/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:09:13 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/12 23:17:14 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//ft_strlen until the first space

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' '
		&& str[i] != '$' && str[i] != '\"')
		i++;
	return (i);
}

int	ft_len2(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"')
	{
		if (str[i] == '$' && i != 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_n_var(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			count++;
		i++;
	}
	return (count);
}

void	ft_error(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

int	skip_tok(char *line, char *data, int i, char tok)
{
	while (line[i])
	{
		if (line[i] == tok && data[i] == '0')
			return (i + 1);
		else
			i++;
	}
	return (i);
}
