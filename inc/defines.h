/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damendez <damendez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/22 21:02:54 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

# define SQUOTE	39
# define DQUOTE	34
# define KSPACE	32

# define R_END 0
# define W_END 1

typedef struct s_pipe
{
	int	num_cmds;
	int	prev_fds[2];
	int	next_fds[2];
	int	i;
}	t_pipe;

typedef struct s_envv
{
	char			*nm;
	char			*val;
	struct s_envv	*next;
}		t_envv;

typedef struct s_cmd
{
	char			**args;
	char			*full_path;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_prompt
{
	t_cmd	*cmd;
	t_envv	*envp;
	pid_t	pid;
}		t_prompt;

#endif
