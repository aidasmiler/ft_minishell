/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:23:11 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/13 14:43:29 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	close_open(int fd, char *name)
{
	int	new_fd;

	close(fd);
	new_fd = open(name, O_RDONLY);
	return (new_fd);
}

void	expand_heredoc(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i] && (*line)[i] != C_DOLLAR)
		i++;
	expand_this_one(line, i);
}

int	heredoc_maker(char *eof, char **name)
{
	int					fd;
	char				*line;

	fd = open(*name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (fd);
	while (true)
	{
		signals_heredoc();
		line = readline(PROMPT_HEREDOC);
		if (!line)
			return (close(fd));
		if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
			break ;
		else if (ft_strchr(line, '$'))
			expand_heredoc(&line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
	}
	free(line);
	return (close(fd));
}

void	heredoc_parent(int *fd, char **name, int pid)
{
	int					status;
	int					new_fd;

	*fd = -2;
	ignore_signals();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) + 128 == 130)
	{
		write(STDOUT_FILENO, "\n", 1);
		unlink(*name);
		new_fd = open(*name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(new_fd);
	}
}
