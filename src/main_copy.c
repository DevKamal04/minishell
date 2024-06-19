/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:46 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 11:15:08 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*pp_getpath(char **env, char *f_cmd)
{
	int		it;
	char	*path;
	char	*tmp;
	char	*s_tmp;
	char	*holder;

	it = 1;
	s_tmp = NULL;
	tmp = pp_arrcmp((void **)env, "PATH=");
	if (!tmp)
		return (NULL);
	path = ft_strdup(tmp + 5);
	tmp = path;
	holder = path;
	while (*path && (it || access(s_tmp, X_OK)))
	{
		it = 0;
		if (s_tmp)
			free(s_tmp);
		path = tmp;
		tmp = pp_path_helper(tmp);
		s_tmp = pp_strjoin(path, pp_strjoin("/", f_cmd, 0), (1 << 1));
	}
	free(holder);
	return (s_tmp);
}

int	execute(t_command *cmd, t_terminal *terminal, int stdin)
{
	char	*path;

	dup2(stdin, STDIN_FILENO);
	close(stdin);
	if (cmd->in_fd != 0)
		dup2(cmd->in_fd, 0);
	if (cmd->out_fd != 1)
		dup2(cmd->out_fd, 1);
	if (check_fork(cmd->c_table))
		return (check_builtins(cmd->c_table, terminal, 1));
	path = pp_getpath(terminal->env, cmd->c_table[0]);
	if (path)
		execve(path, cmd->c_table, terminal->env);
	if (path)
		free(path);
	write(2, "minishell: command not found\n", 30);
	return (127);
}

void	actual_exec(t_tokens *tokens, t_terminal *terminal)
{
	int			stdin;
	t_tokens	*tmp;
	int			status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (terminal->n_cmd == 1 && !ft_strlen(tokens->command->cmd))
		return ;
	stdin = dup(STDIN_FILENO);
	tmp = tokens;
	if (!tmp->next && check_fork(tmp->command->c_table))
		terminal->exit_status = check_builtins
			(tmp->command->c_table, terminal, 0);
	else
	{
		while (tmp)
		{
			if (!tmp->next)
				lo(tmp, terminal, stdin, &status);
			else
				stdin = tf(stdin, tmp, terminal);
			tmp = tmp->next;
		}
	}
	close(stdin);
}

void	lo(t_tokens *tokens, t_terminal *term, int stdin, int *status)
{
	if (fork() == 0)
	{
		exit(execute(tokens->command, term, stdin));
	}
	close(stdin);
	while (waitpid(-1, status, WUNTRACED) != -1)
		;
	term->exit_status = (*status >> 8) & 0x000000ff;
	stdin = dup(STDIN_FILENO);
}

int	tf(int stdin, t_tokens *tokens, t_terminal *term)
{
	int	fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(execute(tokens->command, term, stdin));
	}
	close(fd[1]);
	close(stdin);
	return (fd[0]);
}
