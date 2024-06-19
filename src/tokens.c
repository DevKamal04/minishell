/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:28:21 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 11:33:43 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//parses the tokens, will call expander and redirections 

// tokens->command->cmd ------> one command after expansion
// tokens->command->line ----> contains expansion flags

void	ft_token_fixer(t_tokens **tokens, t_terminal *terminal)
{
	t_tokens	*head;

	head = (*tokens);
	terminal->head = head;
	while ((*tokens) != NULL)
	{
		(*tokens)->command = (t_command *)malloc(sizeof(t_command));
		(*tokens)->command->line = ft_strdup((*tokens)->cmd);
		(*tokens)->command->cmd = ft_parse((*tokens));
		terminal->ptr = (*tokens)->command->cmd;
		(*tokens)->command->in_fd = 0;
		(*tokens)->command->out_fd = 1;
		(*tokens) = (*tokens)->next;
	}
	(*tokens) = head;
	while (head)
	{
		head->command->cmd = ft_expand(head->command->cmd,
				&head->command->line, terminal);
		head = head->next;
	}
	head = (*tokens);
	ft_redir_call(tokens);
	(*tokens) = head;
	ft_token_fix_helper(tokens);
}

//main tokenizer function

int	ft_tokenizer(t_terminal *terminal, t_tokens **tokens, char *line)
{
	terminal->n_cmd = numof_cmds(line);
	if (terminal->n_cmd <= 0)
	{
		printf("No commands found \n");
		return (-1);
	}
	*tokens = ft_tokens(line, terminal->n_cmd);
	if (!tokens)
		return (-1);
	ft_token_fixer(tokens, terminal);
	return (0);
}

//creates tokens linked list based on number of commands

t_tokens	*ft_tokens(char *line, int n_cmd)
{
	t_tokens	*head;
	t_tokens	*curr;
	int			i;

	i = 0;
	if (n_cmd > 0)
	{
		head = (t_tokens *)malloc(sizeof(t_tokens));
		head->next = NULL;
	}
	else
		return (NULL);
	curr = head;
	while (i < n_cmd - 1)
	{
		curr->next = (t_tokens *)malloc(sizeof(t_tokens));
		curr = curr->next;
		curr->next = NULL;
		i++;
	}
	if (ft_set_tokens(&head, line) == -1)
		return (NULL);
	return (head);
}

//sets tokens of cmds on given lines of '|' delimiter

int	ft_set_tokens(t_tokens **head, char *line)
{
	int			i;
	int			start;
	t_tokens	*curr;

	curr = *head;
	start = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			curr->cmd = ft_substr(line, start, i - start);
			start = i + 1;
			if (curr->next != NULL)
				curr = curr->next;
		}
	}
	curr->cmd = ft_substr(line, start, i - start);
	return (0);
}
