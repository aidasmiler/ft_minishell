/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:28:24 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/13 14:18:21 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(char **path_split, char **cmd, char *path)
{
	if (!access(path, F_OK | X_OK))
	{
		free_double_chr_ptr(path_split);
		free(*cmd);
		*cmd = path;
		return (1);
	}
	return (0);
}

int	change_cmd(char **cmd)
{
	int		i;
	char	*path;
	char	**path_split;

	if (!access(*cmd, F_OK | X_OK) || is_builtin(*cmd))
		return (1);
	i = -1;
	path = ft_getenv("PATH");
	if (path)
	{
		path_split = ft_split(path, ':');
		free(path);
		while (path_split[++i])
		{
			path_split[i] = strjoin_chr(path_split[i], '/');
			path = ft_strjoin(path_split[i], *cmd);
			if (check_access(path_split, cmd, path))
				return (1);
			free(path);
		}
		free_double_chr_ptr(path_split);
	}
	return (print_error(T_NOCMD, *cmd, 127));
}

void	manage_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		if (tmp->type == C_INPUT && tmp->name)
			tmp->fd = open(tmp->name, O_RDONLY);
		if (tmp->type == C_INPUT)
			dup2(tmp->fd, STDIN_FILENO);
		else if (tmp->type == C_OUTPUT)
			dup2(tmp->fd, STDOUT_FILENO);
		tmp = tmp->next;
	}
}

void	restore_org_fds(int stdin_fd, int stdout_fd)
{
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
}
