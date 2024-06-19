/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:29:34 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 05:08:01 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(t_terminal *term)
{
	char	*user;
	char	*tmp;

	tmp = getenv("USER");
	user = ft_strjoin(tmp, " % ");
	term->prompt = ft_strjoin("~> ", user);
	if (user)
		free(user);
}

int	symbol_check(char c)
{
	int	flag;

	flag = 0;
	if (c && (c == '*' || c == '#'
			|| c == '&' || c == '!' || c == '('
			|| c == ')' || c == '{' || c == '}'
			|| c == '[' || c == ']' || c == ';'))
		flag = 1;
	return (flag);
}

int	checker(char	*inp)
{
	int	i;
	int	c;
	int	flag;

	flag = 0;
	i = -1;
	while (inp[++i])
	{
		if (inp[i] == '\'' || inp[i] == '\"')
		{
			c = inp[i++];
			flag = 1;
		}
		while (inp[i] && inp[i] != c && flag)
			i++;
		if (!inp[i])
			break ;
		if (inp[i] && inp[i] == c && flag)
			flag = 0;
		if (inp[i] && symbol_check(inp[i]))
			return (1);
	}
	return (flag);
}

int	numof_cmds(char *line)
{
	int	i;
	int	n;

	n = 0;
	i = -1;
	if (line[0] && line[0] != '\t' && line[0] != ' ')
		n = 1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			if (pipe_check(line, i) == -1)
				return (0);
			n++;
		}
	}
	return (n);
}

int	pipe_check(char *line, int ind)
{
	int	i;

	i = 0;
	ind++;
	while (line[ind])
	{
		if (line[ind] != ' ')
			i = 1;
		ind++;
	}
	if (i)
		return (0);
	return (-1);
}
