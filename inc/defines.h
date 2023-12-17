/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/11 21:59:01 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

# define SQUOTE	39
# define DQUOTE	34
# define KSPACE	32

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
	t_envv	*o_envp;
//	pid_t	pid;
	t_cmd	*next;
}		t_prompt;

#endif
