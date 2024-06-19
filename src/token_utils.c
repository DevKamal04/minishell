/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:25:45 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 09:35:27 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_redir_call(t_tokens **tokens)
{
	t_command	*ptr;

	while ((*tokens) != NULL)
	{
		ft_redir(*tokens);
		ptr = (*tokens)->command;
		(*tokens)->command = ft_clean_redir(*tokens);
		if (ptr)
			free(ptr);
		(*tokens) = (*tokens)->next;
	}
}

void	ft_token_fix_helper(t_tokens **tokens)
{
	t_tokens	*head;

	head = (*tokens);
	while (head)
	{
		if (ft_strlen((*tokens)->command->cmd))
		{
			head->command->f_table = splt_space(head->command,
					head->command->cmd, head->command->line);
		}
		head = head->next;
	}
	head = (*tokens);
	while (head)
	{
		if (ft_strlen((*tokens)->command->cmd))
		{
			ft_change_q(head->command->c_table,
				head->command->f_table, head->command);
		}
		head = head->next;
	}
}
