/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:50:11 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 12:49:11 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*g_env_lst;

char	*get_line(void)
{
	int		status;
	char	*line;
	char	*tmp;

	status = errno;
	tmp = prompt();
	line = readline(tmp);
	free(tmp);
	errno = status;
	if (!line)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(errno);
	}
	tmp = ft_strtrim(line, " ");
	free(line);
	return (tmp);
}

void	loop_my_shell(int stdin_fd, int stdout_fd)
{
	char		*line;
	t_token		*token_line;
	t_command	*command;

	while (true)
	{
		my_signal();
		token_line = NULL;
		command = NULL;
		line = get_line();
		if (!*line)
			continue ;
		add_history(line);
		if (tokenize_line(line, &token_line)
			&& restore_tokens(token_line, &command))
			executor(command, stdin_fd, stdout_fd);
		free_tokens(&token_line);
		free_commands(&command);
	}
}

int	main(int argc, char const *argv[], char **env)
{
	const int	stdin_fd = dup(STDIN_FILENO);
	const int	stdout_fd = dup(STDOUT_FILENO);

	g_env_lst = NULL;
	print_banner();
	make_env(env, &g_env_lst);
	loop_my_shell(stdin_fd, stdout_fd);
	free_env(&g_env_lst);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
