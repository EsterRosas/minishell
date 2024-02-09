/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:56:29 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/08 18:47:41 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 *	Minishell executer steps
 *	0. What does executer take as input?
 *	Lexer:
 *		minishell~ echo "hello		there" how are 'you 'doing? $USER |wc -l >outfile
 *		-> {echo, "hello		there", how, are, 'you 'doing?, $USER, |wc, -l, >outfile, NULL}
 *	Exapander:
 *		$USER -> to value given
 *	Seperate <, |, or > when outside of quotes:
 *		-> {echo, "hello		there", how, are, 'you 'doing?, value, |, wc, -l, >, outfile, NULL}
 *	Parser:
 *		-> cmd:
				cmd 1:
					prompt->cmd->in: 0, prompt->cmd->out: 1, prompt->cmd->fl_p: (null)
					prompt->cmd->args[0]: echo
					prompt->cmd->args[1]: hellothere
					prompt->cmd->args[2]: how
					prompt->cmd->args[3]: are
					prompt->cmd->args[4]: you doing?
					prompt->cmd->args[5]: damendez
				cmd 2:
					prompt->cmd->in: 0, prompt->cmd->out: -1, prompt->cmd->fl_p: /usr/bin/wc
					prompt->cmd->args[0]: wc
					prompt->cmd->args[1]: -l
 *	Executer
 *		1. Handle builtin commands found in 'cmd' nodes. If not a builtin, call func for executing non-builtins
 *			1.1. If a prompt->cmd->args[n] is a subject required builtin (correct syntax) execute it
 *		2. Execute non-builtin func
 *			2.1. Search for command in PATH, retrieve full path
 *			2.2. Check if a fork() needs to be done (builtins dont require child processes)
 *			2.3. 
 *
*/

void	handle_cmds(t_prompt *prompt)
{
	//printf("hello from handle_cmds\n");
	//printf("Heres prompt->cmd->args[%i]: %s\n", i, prompt->cmd->args[i]);
	while (prompt->cmd)
	{
		printf("Ready to execute external command");
		exec_ext_cmd(prompt);
		prompt->cmd = prompt->cmd->next;
	}
}

int	is_builtin(char	*s)
{
	if (ft_strlen(s) == ft_strlen("echo")
		&& ft_strncmp(s, "echo", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("cd")
		&& ft_strncmp(s, "cd", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("pwd")
		&& ft_strncmp(s, "pwd", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("export")
		&& ft_strncmp(s, "export", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("unset")
		&& ft_strncmp(s, "unset", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("env")
		&& ft_strncmp(s, "env", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strlen(s) == ft_strlen("exit")
		&& ft_strncmp(s, "exit", ft_strlen(s)) == 0)
		return (1);
	return (0);
}

void	ft_env(t_envv *env)
{
	char	**s;
	int		i;

	s = env_lst2arr(env);
	i = -1;
	while (s[++i])
		printf("%s\n", s[i]);
}

void	ft_pwd(t_envv *env)
{
	t_envv	*aux;

	aux = env;
	while (ft_strcmp(aux->nm, "PWD") != 0)
		aux = aux->next;
	if (ft_strcmp(aux->nm, "PWD") == 0)
		printf("%s\n", aux->val);
}

void	ft_exit()
{
	printf("exit\n");
	exit (1); 
}
