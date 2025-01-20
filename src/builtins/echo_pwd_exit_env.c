/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_exit_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:10:50 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 12:42:26 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int		i;

	i = 1;
	errno = EXIT_SUCCESS;
	if (!cmd[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
		i++;
	while (cmd && cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (cmd[1] && ft_strncmp(cmd[1], "-n", 2))
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_pwd(void)
{
	char	*cwd;

	errno = EXIT_SUCCESS;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(cwd);
}

int	ft_exit(char **cmd)
{
	int	i;
	int	status;

	i = -1;
	while (cmd[1] && cmd[1][++i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			print_type_of_args("exit", cmd[1]);
			exit(255);
		}
	}
	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
		return (print_error(T_TOOMANYARGS, "exit", 1));
	if (cmd[1])
		status = ft_atoi(cmd[1]) % 256;
	else
		status = errno;
	exit (status);
}

void	ft_env(void)
{
	t_env	*tmp;

	tmp = g_env_lst;
	while (tmp)
	{
		if (tmp->content && tmp->content[0])
		{
			ft_putstr_fd(tmp->name, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(tmp->content, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
}
