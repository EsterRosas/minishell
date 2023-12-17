/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecabanas <ecabanas@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:45:32 by ecabanas          #+#    #+#             */
/*   Updated: 2023/12/12 19:54:27 by erosas-c         ###   ########.fr       */
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
# include "../lib/libft/libft.h"
# include "defines.h"

/*      prompt.c        	*/
char	*rl_gets(char *line);
void	loop_prompt(char *line, t_envv *o_envp);
int		ft_strcmp(char *s1, char *s2);

/*		trim functions		*/
char	**cmdtrim(char *s);
int		readl_test(void);

/*		subsplit functions	*/
char	**cmdsubsplit(char **s);
int		need_split(char **s);
int		only_sep(char *s);
int		is_sep(char c);
int		splitable(char *s);
int		count_new_ptrs(char **s);
char	*first_spl(char *tr);
char	*last_spl(char *tr, int l);
int		next_quote(char *p, int i, char c);

/*		expander functions	*/
char	**cmdexpand(char **s);
int		need_var(char **s);
int		has_var(char *s);
char	**repl_var(char **s, t_envv *o_envp);
char	*var_name(char	*p, int aft_dl);
char	*get_oenv(char *s, t_envv *o_envp);

/*      testfunctions.c        */
void	test(char *line, t_envv *o_envp);

/*      builtins.c            */
void	ft_echo(const char *message);
void	ft_pwd(void);
int		is_builtin(char	*s);
void	ft_exit(void);

/*      errors.c            */
void	handle_error(const char *message);

/*		utils.c				*/
int		dbl_len(char **s);
void	free_env(t_envv *o_envp);
void	add_env_back(t_envv *env_lst, t_envv *new);
char	**env_lst2arr(t_envv *env_lst);
int		expandable(char *s);

/*		parser.c				*/
t_cmd	*get_cmd(char **lexi, t_envv *env_lst);
int		assign_infile(char	*file);
int		assign_outfile(char	*file);
void	free_cmds(char **lexed, t_cmd *cmd);
void	del_all_quotes(char **args);
t_cmd	*get_cmdlst(char **lex, t_envv *env_lst);
void	fill_cmdlst(char **lex, t_envv *env_lst, t_cmd *cmdlst, int cmd_n);

#endif