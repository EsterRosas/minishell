/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2023/11/26 19:58:51 by erosas-c         ###   ########.fr       */
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
	char	**envp;
	pid_t	pid;
}		t_prompt;

typedef struct s_subpr
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}		t_subpr;

typedef	struct s_envv
{
	char	*nm;
	char	*val;
	int		size;
}		t_envv;

#endif
