/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:22:46 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 12:22:47 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_sorted(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!*lst || ft_strcmp(new->name, (*lst)->name) < 0)
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		tmp = *lst;
		while (tmp)
		{
			if (ft_strcmp(new->name, tmp->name) > 0 && tmp->next
				&& ft_strcmp(new->name, tmp->next->name) < 0)
			{
				new->next = tmp->next;
				tmp->next = new;
				return ;
			}
			tmp = tmp->next;
		}
		add_var_back(lst, new);
	}
}

static t_env	*sort_for_export(t_env *env)
{
	t_env	*tmp;
	t_env	*sorted;
	t_env	*new;

	tmp = env;
	sorted = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "_"))
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (NULL);
			new->name = ft_strdup(tmp->name);
			new->content = NULL;
			if (tmp->content)
				new->content = ft_strdup(tmp->content);
			new->next = NULL;
			add_sorted(&sorted, new);
		}
		tmp = tmp->next;
	}
	return (sorted);
}

static void	print_export(t_env *env_lst)
{
	t_env	*tmp;
	t_env	*tmp_free;

	tmp_free = sort_for_export(env_lst);
	tmp = tmp_free;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->name, STDOUT_FILENO);
		if (tmp->content)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(tmp->content, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		tmp = tmp->next;
	}
	free_env(&tmp_free);
}

void	ft_export(char **cmd)
{
	int		i[2];
	char	*content;
	char	*name;
	t_env	*tmp;

	i[0] = 0;
	tmp = g_env_lst;
	if (!cmd[1])
		print_export(tmp);
	while (cmd[++i[0]])
	{
		i[1] = -1;
		name = ft_calloc(1, sizeof(char));
		content = NULL;
		while (cmd[i[0]][++i[1]] && cmd[i[0]][i[1]] != '=')
			name = strjoin_chr(name, cmd[i[0]][i[1]]);
		if (cmd[i[0]][i[1]] && cmd[i[0]][i[1]] == '=')
			content = ft_strdup(&cmd[i[0]][++i[1]]);
		if (!ft_strncmp(name, "_", 2))
			return (free(name));
		change_create_var(name, content);
	}
}
