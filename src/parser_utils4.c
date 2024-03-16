#include "../inc/minishell.h"

char	*del_leaddol(char *s)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = -1;
	res = malloc(sizeof(char) * ft_strlen(s));
	if (!res)
		return (NULL);
	while (s[++i])
		res[++j] = s[i];
	res[j] = '\0';
	free(s);
	return (res);
}

t_cmd	*args_exst(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	i = 0;
	aux = cmd;
	while (aux)
	{
		if (aux->args && aux->args[0])
		{
			while (cmd->args[i])
			{
				if (ft_strcmp(cmd->args[i], "$?") == 0)
				{	
					free(cmd->args[i]);
					cmd->args[i] = ft_itoa(g_exst);
				}
				i++;
			}
		}
		aux = aux->next;
	}
	return (cmd);
}

t_cmd	*args_leaddol_quotes(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	i = 0;	
	aux = cmd;
	while (aux)
	{
		if (aux->args && aux->args[0])
		{
			while (cmd->args[i])
			{
		//		printf("before cmd->args[%i]: %s\n", i, cmd->args[i]);
				if (ft_strlen(cmd->args[i]) > 1 && cmd->args[i][0] == '$'
					&& (cmd->args[i][1] == SQUOTE || cmd->args[i][1] == DQUOTE))
					cmd->args[i] = del_leaddol(cmd->args[i]);
				i++;
			}
			del_quotes(aux->args, 1);
		//	printf("after del_quotes cmd->args[1]: %s\n", cmd->args[1]);
		}
		aux = aux->next;
	}
	return (cmd);
}
