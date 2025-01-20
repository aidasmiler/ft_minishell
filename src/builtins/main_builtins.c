/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:57:43 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 12:35:41 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_builtins(char **cmd)
{
	if (!ft_strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
	else if (!ft_strncmp(cmd[0], "env", 4))
		ft_env();
	else if (!ft_strncmp(cmd[0], "cd", 3))
		ft_cd(cmd);
	else if (!ft_strncmp(cmd[0], "export", 7))
		ft_export(cmd);
	else if (!ft_strncmp(cmd[0], "unset", 6))
		ft_unset(cmd);
	return ;
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	return (0);
}
