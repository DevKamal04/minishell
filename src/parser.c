/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:31:24 by richardh          #+#    #+#             */
/*   Updated: 2024/06/13 09:48:03 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_parse(t_tokens *tokens)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(1, ft_strlen(tokens->command->line) + 1);
	while (tokens->command->line[i] == ' ')
		i++;
	while (tokens->command->line[i])
	{
		if (tokens->command->line[i] == '|')
		{
			i++;
			while (tokens->command->line[i] == ' ')
				i++;
		}
		else
			tmp[j++] = tokens->command->line[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

void	rell_help(char	*tmp, char *tmp2, int j)
{
	tmp[j] = '\0';
	tmp2[j] = '\0';
}

void	rell_help_2(t_command *cmd, int line, char *tmp, char *tmp2)
{
	if (cmd->c_table[line])
		free(cmd->c_table[line]);
	if (cmd->f_table[line])
		free(cmd->f_table[line]);
	cmd->c_table[line] = tmp;
	cmd->f_table[line] = tmp2;
}

void	ft_rell(int line, int ind, t_command *cmd)
{
	int		z;
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;

	z = skip_tok(cmd->c_table[line], cmd->f_table[line],
			ind + 1, cmd->c_table[line][ind]);
	z--;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(cmd->c_table[line]) - 2);
	tmp2 = (char *)malloc(sizeof(char) * ft_strlen(cmd->f_table[line]) - 2);
	i = 0;
	j = 0;
	while (cmd->c_table[line][i])
	{
		if (i == ind || i == z)
			i++;
		else
		{
			tmp[j] = cmd->c_table[line][i];
			tmp2[j++] = cmd->f_table[line][i++];
		}
	}
	rell_help(tmp, tmp2, j);
	rell_help_2(cmd, line, tmp, tmp2);
}

void	ft_change_q(char **c, char **f, t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (c[i] && f[i])
	{
		j = 0;
		while (c[i][j] && f[i][j])
		{
			if ((c[i][j] == '\'' || c[i][j] == '"') && f[i][j] == '0')
			{
				ft_rell(i, j, cmd);
				j = 0;
			}
			else
				j++;
		}
		i++;
	}
}
