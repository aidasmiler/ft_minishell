/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:23:41 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/25 15:58:53 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_var(char **name, char **content)
{
	t_env	*newel;

	newel = malloc(sizeof(t_env));
	if (!newel)
		return (NULL);
	newel->name = ft_strdup(*name);
	free(*name);
	if (*content)
	{
		if (!ft_strcmp(newel->name, "SHLVL"))
			newel->content = ft_itoa(ft_atoi(*content) + 1);
		else
			newel->content = ft_strdup(*content);
		free(*content);
	}
	else
		newel->content = NULL;
	newel->next = NULL;
	return (newel);
}

void	add_var_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	make_env(char	**env, t_env **env_lst)
{
	int		i;
	int		j;
	char	*name;
	char	*content;

	i = -1;
	while (env && env[++i])
	{
		j = -1;
		name = ft_calloc(1, sizeof(char));
		while (env[i] && env[i][++j] && env[i][j] != '=')
			name = strjoin_chr(name, env[i][j]);
		if (env[i][j] && env[i][j] == '=')
			j++;
		content = ft_strdup(&env[i][j]);
		add_var_back(env_lst, new_var(&name, &content));
	}
}

char	*ft_getenv(char	*name)
{
	t_env	*tmp;

	tmp = g_env_lst;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(name) + 1))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

char	**turn_lst_to_array(void)
{
	int		i;
	t_env	*tmp;
	char	**env_array;
	char	*name_eq;

	i = -1;
	tmp = g_env_lst;
	env_array = malloc((env_lstsize(tmp) + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	while (tmp)
	{
		name_eq = ft_strdup(tmp->name);
		name_eq = strjoin_chr(name_eq, '=');
		env_array[++i] = ft_strjoin(name_eq, tmp->content);
		free (name_eq);
		tmp = tmp->next;
	}
	env_array[++i] = NULL;
	return (env_array);
}
