/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:16:08 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 11:41:34 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_fix_cmd(char *t_a, char *t_b, char *before, char *after)
{
	if (t_a)
		free(t_a);
	if (t_b)
		free(t_b);
	if (before)
		free(before);
	if (after)
		free(after);
}

void	free_init(t_terminal *term)
{
	if (term->env)
		free_mat(term->env);
}

void	free_cmd_2(t_tokens *current)
{
	if (current->command->cmd)
		free(current->command->cmd);
	if (current->command->c_table)
		free_mat(current->command->c_table);
	if (current->command->f_table)
		free_mat(current->command->f_table);
	if (current->command)
		free(current->command);
	if (current)
		free(current);
}

void	free_cmd(t_tokens *lst)
{
	t_tokens	*current;
	t_tokens	*next;

	if (lst)
	{
		current = lst;
		while (current != NULL)
		{
			if (current->next != NULL)
				next = current->next;
			else
				next = NULL;
			if (current->cmd)
				free(current->cmd);
			if (current->command->line)
				free(current->command->line);
			free_cmd_2(current);
			current = next;
		}
	}
}
