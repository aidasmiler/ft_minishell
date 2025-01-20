/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:48:25 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 12:46:00 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_create_var(char *name, char	*new_content)
{
	t_env	*tmp;

	tmp = g_env_lst;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, ft_strlen(name) + 1))
		{
			free(tmp->content);
			free(name);
			tmp->content = new_content;
			return ;
		}
		tmp = tmp->next;
	}
	add_var_back(&g_env_lst, new_var(&name, &new_content));
}

int	ft_cd(char **cmd)
{
	char	*pwd;
	char	*oldpwd;

	if (!cmd[1])
		return (0);
	else if (chdir(cmd[1]) == -1)
		return (print_error(T_NOFILE, cmd[1], 1));
	oldpwd = ft_getenv("OLDPWD");
	pwd = ft_getenv("PWD");
	if (oldpwd)
	{
		change_create_var(ft_strdup("OLDPWD"), ft_getenv("PWD"));
		free(oldpwd);
	}
	if (pwd)
	{
		change_create_var(ft_strdup("PWD"), getcwd(NULL, 0));
		free(pwd);
	}
	return (1);
}

void	ft_unset(char **cmd)
{
	int		i;
	t_env	*tmp;
	t_env	*aux;

	i = 0;
	if (!cmd[1])
		return ;
	while (cmd[++i])
	{
		if (!ft_strcmp(cmd[i], "_"))
			continue ;
		tmp = g_env_lst;
		while (tmp)
		{
			if (tmp->next && !ft_strcmp(cmd[i], tmp->next->name))
			{
				aux = tmp->next;
				tmp->next = tmp->next->next;
				free(aux->content);
				free(aux->name);
				free(aux);
			}
			tmp = tmp->next;
		}
	}
}
