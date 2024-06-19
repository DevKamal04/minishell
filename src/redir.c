/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:12:27 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/12 23:24:17 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_redir(char *fname, int flag, t_tokens *tokens)
{
	if (flag == '>' || flag == '?')
		redir_check(fname, flag, tokens);
	else if (flag == '<')
	{
		if (access(fname, F_OK) == 0)
		{
			if (access(fname, R_OK) == 0)
				tokens->command->in_fd = open(fname, O_RDONLY);
			else
				ft_error("No read permission");
		}
		else
			ft_error("No such file or directory");
	}
	else if (flag == '=')
		ft_heredoc(tokens);
	return (0);
}

t_command	*ft_clean_redir(t_tokens *tokens)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->in_fd = tokens->command->in_fd;
	command->out_fd = tokens->command->out_fd;
	command->c_table = tokens->command->c_table;
	command->line = tokens->command->line;
	command->cmd = tokens->command->cmd;
	fix_cmd_cont(command);
	return (command);
}

int	ft_redir_helper(int i, char *line, t_tokens *tokens)
{
	char	*fname;
	int		len;
	int		j;
	int		flag;

	flag = line[i];
	j = i + 1;
	if (line[j] == line[i] && tokens->command->line[j] == '0')
	{
		j = skip_leading_spaces(line, tokens->command->line, j + 1);
		flag += 1;
	}
	else
		j = skip_leading_spaces(line, tokens->command->line, j);
	len = get_name_len(j, line, tokens->command->line);
	fname = ft_substr(line, j, len);
	handle_redir(fname, flag, tokens);
	i = j + len;
	return (i);
}

void	ft_redir(t_tokens *tokens)
{
	char	*line;
	int		i;

	line = tokens->command->cmd;
	i = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"')
			&& tokens->command->line[i] == '0')
			i = skip_tok(line, tokens->command->line, i + 1, line[i]);
		if ((line[i] == '>' || line [i] == '<')
			&& tokens->command->line[i] == '0')
			i = ft_redir_helper(i, line, tokens);
		else
			i++;
	}
}
