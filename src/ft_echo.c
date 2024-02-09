#include "../inc/minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (ft_strcmp(cmd->args[1], "-n") == 0)
		i++;
	while (cmd->args[++i])
	{
		printf("%s", cmd->args[i]);
		if (i < dbl_len(cmd->args) - 1)
			printf(" ");
		else if (/*i == dbl_len(cmd->args) - 1 &&*/ ft_strcmp(cmd->args[1], "-n") != 0)
			printf("\n");
	}
}

