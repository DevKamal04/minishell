/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:09:03 by richardh          #+#    #+#             */
/*   Updated: 2024/06/13 11:36:30 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**dup_envp(char **envp)
{
	int		len;
	char	**ev;

	len = 0;
	while (envp[len])
		len++;
	ev = malloc(sizeof(char **) * (len + 1));
	ev[len] = NULL;
	len = -1;
	while (envp[++len])
	{
		ev[len] = ft_strdup(envp[len]);
	}
	return (ev);
}

void	init(t_terminal *terminal, char **envp, char **argv, int argc)
{
	(void)argc;
	(void)argv;
	terminal->exit_status = 0;
	terminal->exit_flag = 0;
	terminal->env = dup_envp(envp);
	terminal->prompt = NULL;
}

void	signals_main(void)
{
	signal(SIGINT, sig_type);
	signal(SIGQUIT, sig_type);
	clear_sigargs();
}

int	ft_looper(t_terminal *terminal, t_tokens **tokens)
{
	char	*line;

	line = NULL;
	prompt(terminal);
	if (isatty(fileno(stdin)))
		line = readline(terminal->prompt);
	free(terminal->prompt);
	if (line && *line)
	{
		add_history(line);
		if (checker(line) == 1)
		{
			printf("Syntax error!\n");
			if (line)
				free(line);
			return (1);
		}
		if (ft_tokenizer(terminal, tokens, line) == -1)
			return (-1);
		actual_exec(*tokens, terminal);
	}
	else if (!line)
		return (-2);
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_terminal	terminal;
	t_tokens	*tokens;
	int			i;

	tokens = NULL;
	init(&terminal, envp, argv, argc);
	i = 0;
	while (1)
	{
		signals_main();
		i = ft_looper(&terminal, &tokens);
		if (i == -1)
			continue ;
		else if (i == -2)
			break ;
		if (terminal.ptr && terminal.n_cmd > 1)
		{
			free_cmd(tokens);
			free(terminal.ptr);
		}
		if (terminal.exit_flag == 1)
			break ;
	}
	return (free_init(&terminal), terminal.exit_status);
}
