/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erosas-c <erosas-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:25:13 by erosas-c          #+#    #+#             */
/*   Updated: 2024/03/28 17:40:07 by erosas-c         ###   ########.fr       */
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
	if ((!s1 && s2[i] < '=') || (!s2 && s1[i] > '='))
		return (1);
	return (0);
}

void	ft_swapnodes(t_envv *aux)
{
	t_envv	*temp;

	temp = ft_calloc(sizeof(t_envv), 1);
	if (!temp)
		return ;
	temp->nm = ft_strdup(aux->nm);
	if (aux->val)
		temp->val = ft_strdup(aux->val);
	else
		temp->val = NULL;
	free(aux->nm);
	free(aux->val);
	aux->nm = ft_strdup(aux->next->nm);
	if (aux->next-> val)
		aux->val = ft_strdup(aux->next->val);
	else
		aux->val = NULL;
	free(aux->next->nm);
	free(aux->next->val);
	aux->next->nm = ft_strdup(temp->nm);
	if (temp->val)
		aux->next->val = ft_strdup(temp->val);
	else
		aux->next->val = NULL;
	free_env(temp);
}

t_envv	*ft_sortlist(t_envv	*env)
{
	t_envv	*aux;
	int		len;

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
				ft_swapnodes(aux);
			aux = aux->next;
		}
		len--;
		aux = env;
	}
	return (aux);
}

void	only_export(t_envv *env)
{
	t_envv	*sorted;
	t_envv	*aux;

	sorted = ft_sortlist(env);
	aux = sorted->next;
	while (aux)
	{
		printf("declare -x %s", aux->nm);
		if (aux->val)
			printf("=\"%s\"", aux->val);
		printf("\n");
		aux = aux->next;
	}
}

int	ft_export(char **args, t_envv *env)
{
	int	i;

	i = 1;
	if (dbl_len(args) == 1)
	{
		only_export(env);
		g_exst = 0;
	}
	else
	{
		while (args[i])
		{
			if (id_notvalid(args[i]) == 1)
				g_exst = 1;
			else
				g_exst = ft_edit_envlist(args[i], env);
			i++;
		}
	}
	return (g_exst);
}
