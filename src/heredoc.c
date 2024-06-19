/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:00:43 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 08:56:47 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_end_check(char *eof, char *line)
{
	if (ft_strncmp(eof, line, ft_strlen(eof)) == 0)
		return (1);
	return (0);
}

char	*eof_fixer(char *eof)
{
	int	i;
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(eof) - 1;
	while (eof[start] && (eof[start] == '<'
			|| eof[start] == '>' || eof[start] == ' '))
		start++;
	while ((end >= start) && eof[end] && eof[end] == ' ')
		end--;
	i = start;
	while (i <= end)
	{
		eof[i - start] = eof[i];
		i++;
	}
	eof[i - start] = '\0';
	return (eof);
}

int	ft_heredoc(t_tokens *tokens)
{
	int		fd[2];
	char	*prompt;
	char	*line;

	prompt = "> ";
	line = NULL;
	if (pipe(fd) == -1)
		return (ft_error("Failed to create heredoc file."), -1);
	while (1)
	{
		line = readline(prompt);
		if (!line)
			break ;
		if (ft_end_check(eof_fixer(tokens->command->cmd), line) == 1)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
	}
	close(fd[1]);
	close(fd[0]);
	return (0);
}
