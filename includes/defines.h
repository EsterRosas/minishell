/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2023/12/02 19:34:59 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "../lib/libft/libft.h"

# define SQUOTE	39
# define DQUOTE	34
# define KSPACE	32

typedef struct s_prompt
{
	t_list	*cmds;
	char 	**o_envp;
//	pid_t	pid;
}		t_prompt;

typedef struct s_cmd
{
	char	**args;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_cmd;

typedef	struct s_envv
{
	char			*nm;
	char			*val;
//	int		size;
	struct	s_envv	*next;
}		t_envv;

#endif
