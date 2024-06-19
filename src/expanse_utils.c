/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:15:41 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 11:34:58 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//write functions to remove part of string

char	*ft_rem_str(char *str, int sub_start, int size, char **data)
{
	int		i;
	int		j;
	char	*tmp;
	char	*other;

	i = -1;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	other = (char *)malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	while (str[++i])
	{
		if (!(i >= sub_start && i < (sub_start + size)))
		{
			tmp[j] = str[i];
			other[j++] = data[0][i];
		}
	}
	tmp[j] = '\0';
	other[j] = '\0';
	if (*data)
		free(*data);
	*data = other;
	if (str)
		free(str);
	return (tmp);
}

//function to get value of env variable

char	*ft_get(char *name, t_terminal *terminal)
{
	int		i;
	int		len;
	char	**envp;

	envp = terminal->env;
	i = 0;
	if (ft_strncmp(name, "?", ft_strlen(name)) == 0
		&& ft_strncmp(name, "?", ft_strlen("?")) == 0)
		return (ft_itoa(terminal->exit_status));
	while (envp[i])
	{
		len = 0;
		while (envp[i][len] && envp[i][len] != '=')
			len++;
		if (ft_strncmp(name, envp[i], len) == 0 && name[len] == '\0')
		{
			if (name)
				free(name);
			return (envp[i] + len + 1);
		}
		i++;
	}
	if (name)
		free(name);
	return (NULL);
}

//function to replace part of string (allocate for each string dynamically)

char	*ft_rep_str(char *str, int sub_start, char *var, char **data)
{
	int		size;
	char	*full;
	char	*tmp;
	char	*after;
	char	*cpy_var;

	size = ft_len2(str + sub_start);
	cpy_var = ft_strdup(var);
	full = ft_strjoin(ft_strjoin(ft_substr(str, 0, sub_start), cpy_var),
			ft_substr(str, sub_start + size, ft_strlen(str)));
	if (ft_substr(str, 0, sub_start))
		free(ft_substr(str, 0, sub_start));
	size = -1;
	while (cpy_var[++size])
		cpy_var[size] = '1';
	tmp = ft_strjoin(ft_substr(*data, 0, sub_start), cpy_var);
	if (cpy_var)
		free(cpy_var);
	after = ft_substr(*data, sub_start + size, ft_strlen(*data));
	free(*data);
	*data = ft_strjoin(tmp, after);
	if (tmp)
		free(tmp);
	free(after);
	return (full);
}

int	single_q_check(char *tmp, int i)
{
	if (tmp[i] == '\'')
	{
		i++;
		while (tmp[i] && tmp[i] != '\'')
			i++;
		i++;
	}
	return (i);
}

int	exp_cond(char c)
{
	return (c == '$' && !ft_isalnum(c + 1) && c + 1 != '$');
}
