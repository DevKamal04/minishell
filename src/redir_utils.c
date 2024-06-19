/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:18:56 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 09:34:20 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_name_len(int start, char *line, char *flags)
{
	int	i;

	i = start;
	while (line[i])
	{
		if (line[i] == ' ' && flags[i] == '0')
			return (i - start);
		else if ((line[i] == '>' || line[i] == '<') && flags[i] == '0')
			return (i - start);
		else
			i++;
	}
	return (i - start);
}

int	skip_leading_spaces(char *line, char *flags, int pos)
{
	while (line[pos])
	{
		if (line[pos] == ' ' && flags[pos] == '0')
			pos++;
		else
			return (pos);
	}
	return (pos);
}

void	redir_check(char *fname, int flag, t_tokens *tokens)
{
	if (access(fname, F_OK) == 0)
	{
		if (access(fname, W_OK) == 0)
		{
			if (flag == '>')
				tokens->command->out_fd = open(fname, O_WRONLY | O_TRUNC, 0644);
			else
				tokens->command->out_fd
					= open(fname, O_WRONLY | O_APPEND, 0644);
		}
		else
			ft_error("No write permission.");
	}
	else
		tokens->command->out_fd = open(fname, O_WRONLY | O_CREAT, 0644);
}

int	fix_cmd_helper(t_command *cmd, int i, char *t_a, char *t_b)
{
	int		j;
	int		len;
	char	*before;
	char	*after;
	int		z;

	j = i++;
	if ((cmd->cmd[i] == '>' || cmd->cmd[i] == '<') && cmd->line[i] == '0')
		i++;
	i = skip_leading_spaces(cmd->cmd, cmd->line, i);
	z = i - j;
	len = get_name_len(i, cmd->cmd, cmd->line);
	before = ft_substr(cmd->cmd, 0, j);
	t_b = ft_substr(cmd->line, 0, j);
	after = ft_substr(cmd->cmd, j + len + z, ft_strlen(cmd->cmd));
	t_a = ft_substr(cmd->line, j + len + z, ft_strlen(cmd->cmd));
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->line)
		free(cmd->line);
	cmd->cmd = ft_strjoin(before, after);
	cmd->line = ft_strjoin(t_b, t_a);
	free_fix_cmd(t_a, t_b, before, after);
	i = j;
	return (i);
}

void	fix_cmd_cont(t_command *cmd)
{
	int		i;
	char	*t_b;
	char	*t_a;

	i = 0;
	t_b = NULL;
	t_a = NULL;
	while (cmd->cmd[i])
	{
		if ((cmd->cmd[i] == '"' || cmd->cmd[i] == '\'') && cmd->line[i] == '0')
			i = skip_tok(cmd->cmd, cmd->line, i + 1, cmd->cmd[i]);
		if ((cmd->cmd[i] == '>' || cmd->cmd[i] == '<') && cmd->line[i] == '0')
			i = fix_cmd_helper(cmd, i, t_a, t_b);
		else
			i++;
	}
}
