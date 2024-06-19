/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhorvath <rhorvath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:53:38 by rhorvath          #+#    #+#             */
/*   Updated: 2024/06/13 11:42:37 by rhorvath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_command
{
	char	*line;
	char	*cmd;
	char	**c_table;
	char	**f_table;	
	int		in_fd;
	int		out_fd;
}	t_command;

typedef struct s_tokens
{
	char				*cmd;
	struct s_tokens		*next;
	struct s_command	*command;
}	t_tokens;

typedef struct s_terminal
{
	t_tokens	*head;
	char		*prompt;
	char		**env;
	int			n_cmd;
	int			exit_status;
	int			exit_flag;
	void		*ptr;
}		t_terminal;

//main
int			ft_looper(t_terminal *terminal, t_tokens **tokens);
int			main(int argc, char **argv, char **envp);
void		init(t_terminal *terminal, char **envp, char **argv, int argc);
char		**dup_envp(char **envp);

//input check
void		prompt(t_terminal *term);
int			checker(char	*inp);
int			numof_cmds(char *line);
int			pipe_check(char *line, int ind);

//tokens
int			ft_tokenizer(t_terminal *terminal, t_tokens **tokens, char *line);
void		ft_token_fixer(t_tokens **tokens, t_terminal *terminal);
t_tokens	*ft_tokens(char *line, int n_cmd);
int			ft_set_tokens(t_tokens **head, char *line);
char		*ft_parse(t_tokens *tokens);
void		ft_token_fix_helper(t_tokens **tokens);
void		ft_redir_call(t_tokens **tokens);

//expander
char		*ft_expand(char *cmd, char **data, t_terminal *terminal);
char		*ft_get(char *name, t_terminal *terminal);
char		*ft_rem_str(char *str, int sub_start, int size, char **data);
char		*ft_rep_str(char *str, int sub_start, char *var, char **data);
int			exp_cond(char c);
void		fix_cmd_cont(t_command *cmd);
int			single_q_check(char *tmp, int i);
void		ft_rell(int line, int ind, t_command *cmd);
void		rell_help(char	*tmp, char *tmp2, int j);
void		rell_help_2(t_command *cmd, int line, char *tmp, char *tmp2);

//redir
void		ft_redir(t_tokens *tokens);
void		redir_check(char *fname, int flag, t_tokens *tokens);
int			handle_redir(char *fname, int flag, t_tokens *tokens);
int			skip_leading_spaces(char *line, char *flags, int pos);
int			get_name_len(int start, char *line, char *flags);
t_command	*ft_clean_redir(t_tokens *tokens);

//utils
int			symbol_check(char c);
int			ft_len(char *str);
int			ft_n_var(char *str);
int			ft_len2(char *str);
void		ft_error(const char *str);
int			check_equal(char *str);

//freedom
void		free_fix_cmd(char *t_a, char *t_b, char *before, char *after);
void		free_cmd(t_tokens *lst);
void		free_init(t_terminal *term);
void		free_cmd_2(t_tokens *current);

//heredoc
int			ft_heredoc(t_tokens *tokens);
int			ft_end_check(char *eof, char *line);
char		*eof_fixer(char *eof);

//pwd
size_t		ft_strlen(const char *s);
int			exec_pwd(char *command);

//unset
void		ft_realloc(int ind, t_terminal *terminal);
void		free_mat(char **mat);
int			ft_unset(char **a, t_terminal *terminal, int flag);

//input
int			ft_strcmp(const char *s1, const char *s2);
int			check_builtins(char **command, t_terminal *terminal, int flag);

//exit
int			ft_exit(char **command, t_terminal *terminal);

//env
int			exec_env(t_terminal *terminal, int flag);
int			ft_pwd(t_terminal *terminal, int flag);

//echo
int			echo_helper(int flag);
int			exec_echo(char **command, int flag);

//cd
void		change_env_variable(t_terminal *terminal,
				const char *variable_name, const char *new_value);
char		*new_strjoin(const char *s1, const char *s2, const char *sep);
int			change_directory(char *new_dir, t_terminal *terminal, int flag);
int			change_directory_parent(char *oldpwd, char **final_dir);
int			main_directory(char **env, char **final_dir);
int			change_directory_path(char *base_path,
				char *new_value, char **final_dir);
int			helper_new_dir(char **env, char *new_dir, char **final_dir);
int			helper_minus_dir(char **env, char **final_dir);
char		*cd_path_helper(char *new_dir,
				char *oldpwd, char **final_dir, char **env);
int			change_directory(char *new_dir, t_terminal *terminal, int flag);

//export
void		ft_print_export(t_terminal *terminal);
void		ft_add_export_env(t_terminal *terminal, char *new_var);
int			ft_export(char **command, t_terminal *terminal, int flag);

//exec
int			execute(t_command *cmd, t_terminal *terminal, int stdin);
void		actual_exec(t_tokens *tokens, t_terminal *terminal);
void		lo(t_tokens *tokens, t_terminal *term, int stdin, int *status);
int			tf(int stdin, t_tokens *tokens, t_terminal *term);
char		*pp_strjoin(char *s1, char *s2, int free_flag);
char		*pp_arrcmp(void **arr, void *keyword);
int			check_fork(char **command);
char		*pp_path_helper(char *tmp);

//split
void		ft_change_q(char **c, char **f, t_command *cmd);
char		**splt_space(t_command *cmd, char *s, char *s_t);
int			skip_spaces(char *str, int i);
int			is_space(char c);
int			skip_tok(char *line, char *data, int i, char tok);

//signals
void		clear_sigargs(void);
void		block_signal(void);
void		ctrl_bs(void);
void		ctrl_c(void);
void		sig_type(int sig);
void		signals_main(void);

#endif
