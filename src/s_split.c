/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:08:26 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 01:20:57 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	skip_q(char *str, int i, char c, char *str_tok)
{
	while (str[i])
	{
		if (str[i] != c || (str[i] == c && str_tok[i] == c))
			i++;
		else if (str[i] == c && str_tok[i] != c)
			return (i);
	}
	return (-1);
}

static int	m_size(char *str, char *str_tok)
{
	int	i;
	int	size;

	size = 0;
	i = skip_spaces(str, 0);
	while (str[i])
	{
		if (is_space(str[i]))
		{
			i = skip_spaces(str, i);
			if (str[i])
				size++;
		}
		else if ((str[i] == '\'' || str[i] == '"')
			&& str_tok[i] == '0')
			i = skip_tok(str, str_tok, i + 1, str[i]) + 1;
		else
			i++;
	}
	return (size);
}

static	char	**init_all(t_command *cmd, int len, int *i)
{
	char	**mat;

	mat = (char **)malloc(sizeof(char *) * (len + 2));
	cmd->c_table = (char **)malloc(sizeof(char *) * (len + 2));
	mat[len + 1] = NULL;
	cmd->c_table[len + 1] = NULL;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	return (mat);
}

int	skip_spaces(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n'))
		i++;
	return (i);
}

char	**splt_space(t_command *cmd, char *s, char *s_t)
{
	char	**mat;
	int		i[3];

	mat = init_all(cmd, m_size(s, s_t), i);
	while (s[i[1]])
	{
		while (is_space(s[i[1]]))
			i[1]++;
		i[2] = i[1];
		while (s[i[1]] && !is_space(s[i[1]]))
		{
			if ((s[i[1]] == '\'' || s[i[1]] == '"')
				&& s_t[i[1]] == '0')
				i[1] += skip_q(&s[i[1]], 1, s[i[1]], &s_t[i[1]]);
			i[1]++;
		}
		if (is_space(s[i[1]]) || i[1] > i[2])
		{
			cmd->c_table[i[0]] = ft_substr(&s[i[2]], 0, &s[i[1]] - &s[i[2]]);
			mat[i[0]++] = ft_substr(&s_t[i[2]], 0, &s_t[i[1]]
					- &s_t[i[2]]);
			i[2] = i[1];
		}
	}
	return (mat);
}
