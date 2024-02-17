

#include "../inc/minishell.h"

int	ft_export_edit(char	**args, t_envv *env)
{
	t_env	*aux;
	t_envv	*input;
	int		i;

	aux = env;
	i = 1;
	input = malloc(sizeof(t_envv));
	if (!input)
		return (-1);
	i = ft_strchr(envp[0], '=') - envp[0];
	env_lst->nm = ft_substr(envp[0], 0, i);
	env_lst->val = ft_substr(envp[0], i + 1, ft_strlen(envp[0]) - 1);
	env_lst->next = NULL;

	while

		


	return (0);
}
