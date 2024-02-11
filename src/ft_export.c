/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:25:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/02/11 21:38:18 by erosas-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	goes_after(char *s1, char *s2)
{
	size_t	n;
	size_t	i;

	i = -1;
	n = ft_strlen(s1);
	if (n > ft_strlen(s2))
		n = ft_strlen(s2);
	while (++i < n)
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (0);
	}
	if (!s1)
		return (0);
	return (1);
}

t_envv	*ft_sortlist(t_envv	*env)
{
	t_envv	*aux;
	int		len;
	t_envv	*temp;

	temp = malloc(sizeof(t_envv));
	if (!temp)
		return (NULL);
	aux = env;
	len = 0;
	while (aux)
	{
		aux = aux->next;
		len++;
	}
	aux = env;
	while (len >= 0)
	{
		while (aux->next)
		{
			if (goes_after(aux->nm, aux->next->nm))
			{
				temp->nm = ft_strdup(aux->nm);
				temp->val = ft_strdup(aux->val);
				free(aux->nm);
				free(aux->val);
				aux->nm = ft_strdup(aux->next->nm);
				aux->val = ft_strdup(aux->next->val);
				free(aux->next->nm);
				free(aux->next->val);
				aux->next->nm = ft_strdup(temp->nm);
				aux->next->val = ft_strdup(temp->val);
			}
			aux = aux->next;
		}
		len--;
		aux = env;
	}
	return (env);
}

void	only_export(t_envv *env)
{
	t_envv	*sorted;

	sorted = ft_sortlist(env);
	while (sorted)
	{
		printf("declare -x %s", sorted->nm);
		if (sorted->val[0] != '\0')
			printf("=\"%s\"", sorted->val);
		printf("\n");
		sorted = sorted->next;
	}
}

void	ft_export(char **args, t_envv *env)
{
	if (dbl_len(args) == 1)
		only_export(env);
}
