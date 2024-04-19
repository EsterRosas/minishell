/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:45:32 by ecabanas          #+#    #+#             */
/*   Updated: 2024/04/01 15:45:22 by erosas-c         ###   ########.fr       */
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
# include <sys/stat.h>
# include "../lib/libft/inc/libft.h"
# include "defines.h"

int		g_exst;

/*      prompt.c        	*/
void	loop_prompt(t_envv *o_envp);

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
char	*get_oenv(char *s, t_envv *o_envp);
char	**get_nms_arr(char *s, int ct);
int		count_vars(char	*s);
char	**get_vals_arr(char **nms, int ct, t_envv *env);

/*		lexer_utils			*/
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
int		ft_edit_envlist(char *arg, t_envv *env);
int		add_node(char *evar, t_envv *env_lst);
void	only_name(t_envv *node, char *evar);
int		add_new_node(char *evar, t_envv *env);
int		ft_exit(t_cmd *cmd);
int		is_env(char *s);
int		is_cd(char *s);
int		is_echo(char *s);
int		is_pwd(char *s);
int		is_inenvlst(char *s, t_envv *env);
int		id_notvalid(char *s);
int		path_unset(t_envv *env, char *s);
char	*upd_auxval(void);
int		do_cdonly(t_envv *env, char *oldpwd_current);
int		cd_only(t_envv *env);
void	upd_pwds(t_envv *env, char *oldpwd_current);

/*		syntax				*/
int		path_unset_nobuilt(t_cmd *cmd, t_envv *env);
int		check_syntax(char **lex);

/*      errors.c            */
void	handle_error(char *cmd, char *message);
void	handle_error_opt(char *cmd, char *option, char *message);
void	ft_exporterror(char *cmd, char *s, char *msg);
void	only_msg_err(char *message);
void	handle_error_syn(char *message, char *str);

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
t_cmd	*get_cmdlst(char **lex, t_envv *env_lst);
t_cmd	*fill_cmdlst(char **lex);
char	**get_ptharr(t_envv *env_lst);
void	del_quotes(char **s, int i);
int		process_hdoc(char *delim, int last);
char	*path2cmd(char *arg);
void	cmdlst_addback(t_cmd *cmdlst, t_cmd *nw);
char	*fill_path(char *path, t_envv *env_lst, char *first_arg);
char	**add_arg(char **args, char **lex, t_iptrs *iptrs);
char	**fill_args(char **args, char **lex, int lex_pos);
int		is_inpath(char *s, t_envv *env);
void	put_exex2path(t_cmd *cmd);
int		upd_node(t_cmd *s, char **lex, t_iptrs *ip);
char	*dots2path(char *ar);
char	*dot2path(char *ar);
char	*rm_quotes(char *s, int n);
int		ct_quotes(char *p);
t_cmd	*args_leaddol_quotes(t_cmd *cmd);
t_cmd	*args_exst(t_cmd *cmd);
void	sum_ij(int *i, int *j);
int		dollars2del(char *p);
int		count_sp(char *s, char **nms, char **vals);
char	*do_collage(char *res, char *s, char **nms, char **vals);
int		count_sp(char *s, char **nms, char **vals);
char	*just_del_names(char *s, char **nms, char **vals);
char	*ft_assign_mem(char *res, int ct);
void	redo_path(t_cmd *cmd, t_envv *env);
void	cp_val(char *res, int j, char *val);
void	ft_globalfree(t_prompt *prompt);
int		in_savedpath(char *s, char **path);

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

/*		exec_utils2.c			*/
int		ft_chdir(char *s);
void	check_cmd(t_cmd *cmd, t_envv *env);
int		has_nonum(char *s);

/*		pipe_utils.c			*/
void	make_pipe(int pipefd[2]);
void	handle_read_end(int *pipe_fd);
void	handle_write_end(int *pipe_fd);
void	update_pipes(t_pipe *p);
void	handle_stdio(t_pipe *p, char *str);

#endif
