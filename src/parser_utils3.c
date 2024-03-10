#include "../inc/minishell.h"

void	put_exex2path(t_cmd *cmd)
{
/*	int	l;

	l = dbl_len(cmd->args);*/
	cmd->full_path = ft_strdup(cmd->args[0]);
/*	free(cmd->args[0]);
	if (l > 1)
		cmd->args++;*/
}
