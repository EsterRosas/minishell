/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:38:52 by erosas-c          #+#    #+#             */
/*   Updated: 2024/01/23 10:51:55 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

# define SQUOTE	39
# define DQUOTE	34
# define KSPACE	32

typedef struct s_in
{
	char	*file;
	bool	hdoc;
}		t_in;

typedef struct s_envv
{
	char			*nm;
	char			*val;
	struct s_envv	*next;
}		t_envv;

/* Had to change the approach as to be able to pass fds from parser we need to
 * keep all possible in or out files open, and this could be a mess. FDs are to be
 * looked for in executor, as some of them may not be needed.
 * IMPORTANT NOTES:
 * 1) When several input or output files (whether "simple" or append/heredoc),
 * bash takes the last one.
 * 2) Anyway, bash tries to open all the files from the first one, but it skips
 * this command and gos to next one (after the next pipe as soon as he cannot open
 * a file.
 * 3) In any case, if among the infiles there is a heredoc, we need to ask
 * the user for the input to this heredoc, even if we will not feed any "file"
 * with it because we know we will not be using it, for example, because it's not
 * the last one in the infiles struc array.
 *
 * That is why each infile is an item in an array os structs (s_in), each one
 * including the name/path of the file and a boolean indicating if ti's heredoc
 * (<<) or not. IMPORTANT: if it's a heredoc, the vaule of char *file is the
 * DELIMITER!!! to be used to get the additional input of the user until they
 * write that delimiter again.
 */
typedef struct s_cmd
{
	char			**args;
	char			*full_path;
	struct s_in		*infiles;
	char			**outfiles;
	bool			append;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_prompt
{
	t_cmd	*cmd;
	char	**envp;
	pid_t	pid;
}		t_prompt;

#endif
