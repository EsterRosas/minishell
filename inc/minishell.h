/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:45:32 by ecabanas          #+#    #+#             */
/*   Updated: 2024/02/29 19:58:28 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/param.h>
# include "../lib/libft/libft.h"
# include "defines.h"

int		g_exst;

/*      prompt.c        	*/
void	loop_prompt(t_envv *o_envp);
int		upd_shlvl(t_envv *env);

/*		trim functions		*/
char	**cmdtrim(char *s);
int		readl_test(void);
char	**del_consec_quotes(char **s);

/*		subsplit functions	*/
char	**cmdsubsplit(char **s);
int		need_split(char **s);
int		only_sep(char *s);
int		splitable(char *s);
int		next_quote(char *p, int i, char c);

/*		expander functions	*/
char	**cmdexpand(char **s);
int		need_var(char **s);
int		has_var(char *s);
char	**repl_var(char **s, t_envv *o_envp);
char	*var_name(char	*p, int aft_dl);
char	*get_oenv(char *s, t_envv *o_envp);

/*		lexer_utils			*/
int		check_syntax(char **lex);
int		is_sep(char c);
char	*first_spl(char *tr);
char	*last_spl(char *tr, int l);
int		count_new_ptrs(char **s);

/*      builtins            */
int		is_builtin(char	*s);
int		ft_exbuiltin(t_prompt *prompt, t_cmd *cmd);
int		ft_pwd(void);
int		ft_echo(t_cmd *cmd);
int		ft_env(t_envv *env);
int		ft_unset(t_cmd *cmd, t_envv *env);
int		ft_cd(t_cmd *cmd, t_envv *env);
int		ft_export(char **args, t_envv *env);
int		ft_edit_envlist(char **args, t_envv *env);
int		add_node(char *evar, t_envv *env_lst);
void	ft_exit(int st);
int		is_env(char *s);
int		is_cd(char *s);
int		is_echo(char *s);
int		is_pwd(char *s);
int		is_inenvlst(char *s, t_envv *env);
//int		is_subshell(char *s);

/*      errors.c            */
void	handle_error(char *cmd, char *message);
void	handle_error2(char *cmd, char *option, char *message);
void	ft_exporterror(char *cmd, char *s, char *msg);

/*		utils.c				*/
int		dbl_len(char **s);
void	free_env(t_envv *o_envp);
void	add_env_back(t_envv *env_lst, t_envv *nw);
int		expandable(char *s);
int		ft_strcmp(char *s1, char *s2);
t_envv	*cp_envp(char **envp);

/*		list2array.c		*/
char	**env_lst2arr(t_envv *env_lst);

/*		parser				*/
int		assign_infile(char **lex, int i, t_cmd *s);
int		assign_outfile(char **lex, int i, t_cmd *s);
void	free_cmdlist(t_cmd *head);
void	free_envlist(t_envv *head);
t_cmd	*get_cmdlst(char *line, t_envv *env_lst);
t_cmd	*fill_cmdlst(char **lex);
char	**get_ptharr(t_envv *env_lst);
void	del_quotes(char **s);
int		process_hdoc(char *delim, int last);
char	*path2cmd(char *arg);
void	cmdlst_addback(t_cmd *cmdlst, t_cmd *nw);
char	*fill_path(char *path, t_envv *env_lst, char *first_arg);

/*		signals					*/
void	handle_sigint(int sig);
void	disable_ctrl_chars(void);
void	restore_terminal_settings(void);
void	ft_signal(int i);

/*		executor				*/
void	ft_exec(t_prompt *prompt);
int		onecmd_nobuilt(t_prompt *prompt);

/*		exec_utils.c			*/
void	exec_cmd(t_prompt *prompt, t_cmd *cmd);
int		cmdlistsize(t_cmd *cmd);
int		wait_children(pid_t last_child, int n);
pid_t	make_fork(void);
int		check_cmd(t_cmd *cmd);

/*		pipe_utils.c			*/
void	make_pipe(int pipefd[2]);
void	handle_read_end(int *pipe_fd);
void	handle_write_end(int *pipe_fd);
void	update_pipes(t_pipe *p);

/*		pipe_utils.c			*/
void	make_pipe(int pipefd[2]);
void	handle_read_end(int *pipe_fd);
void	handle_write_end(int *pipe_fd);
void	update_pipes(t_pipe *p);
void	handle_stdio(t_pipe *p, char *str);

#endif
