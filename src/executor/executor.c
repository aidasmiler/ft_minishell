/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:46:04 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 12:31:15 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_command *command, int old_fds[2], int fds[2])
{
	if (command->previous)
	{
		close(old_fds[WRITE]);
		dup2(old_fds[READ], STDIN_FILENO);
		close(old_fds[READ]);
	}
	if (command->next)
	{
		close(fds[READ]);
		dup2(fds[WRITE], STDOUT_FILENO);
		close(fds[WRITE]);
	}
	manage_redirs(command->redirs);
	if (is_builtin(command->cmd[0]))
	{
		manage_builtins(command->cmd);
		exit(0);
	}
	signal(SIGQUIT, child_signals);
	signal(SIGINT, child_signals);
	errno = 0;
	execve(command->cmd[0], command->cmd, turn_lst_to_array());
	exit(127);
}

static void	execute_cmd(t_command *command, int old_fds[2])
{
	int		fds[2];
	pid_t	pid;

	pipe(fds);
	pid = fork();
	if (!pid)
		child(command, old_fds, fds);
	else if (pid)
	{
		signal(SIGQUIT, child_signals);
		signal(SIGINT, child_signals);
		if (command->previous)
			close(old_fds[READ]);
		old_fds[READ] = fds[READ];
		old_fds[WRITE] = fds[WRITE];
		close(fds[WRITE]);
		if (!command->next)
			close(fds[READ]);
	}
}

void	wait_childs(t_command *lst)
{
	int			status;
	t_command	*tmp;

	tmp = lst;
	if (tmp->cmd && is_builtin(tmp->cmd[0]) && !tmp->next && !tmp->previous)
		return ;
	while (tmp)
	{
		wait(&status);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		tmp = tmp->next;
	}
}

void	executor(t_command *lst, int stdin_fd, int stdout_fd)
{
	int			old_fds[2];
	t_command	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->cmd)
		{
			if (is_builtin(tmp->cmd[0]) && !tmp->next && !tmp->previous)
			{
				manage_redirs(tmp->redirs);
				manage_builtins(tmp->cmd);
			}
			else
			{
				change_cmd(tmp->cmd);
				execute_cmd(tmp, old_fds);
			}
			restore_org_fds(stdin_fd, stdout_fd);
		}
		tmp = tmp->next;
	}
	wait_childs(lst);
}
