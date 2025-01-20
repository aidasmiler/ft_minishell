/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 12:08:12 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 11:43:29 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_command(t_command **command, char *word)
{
	int		i;
	char	**tmp;

	i = 0;
	while ((*command)->cmd && (*command)->cmd[i])
		i++;
	tmp = (*command)->cmd;
	(*command)->cmd = ft_calloc(i + 2, sizeof(char *));
	if (!(*command)->cmd)
		exit(errno);
	i = 0;
	while (tmp && tmp[i])
	{
		(*command)->cmd[i] = ft_strdup(tmp[i]);
		i++;
	}
	(*command)->cmd[i] = ft_strdup(word);
	free_double_chr_ptr(tmp);
}

static void	manage_heredocs(char *eof, char **name, int *fd)
{
	int					pid;
	static unsigned int	i = 0;
	char				*tmp;

	tmp = ft_itoa(i++);
	*name = ft_strjoin(".tmp", tmp);
	free(tmp);
	pid = fork();
	if (!pid)
	{
		signals_heredoc();
		heredoc_maker(eof, name);
		exit(0);
	}
	else
		heredoc_parent(fd, name, pid);
}

static int	add_redirs(t_command **command, t_token *token)
{
	int		fd;
	char	*name;

	fd = 0;
	name = NULL;
	if (!token->next)
		return (print_error(T_SYNTAX,
				"syntax error near unexpected token 'newline'", 2));
	else if (token->next->type != C_WORD)
		return (print_redir_error(token->next->type));
	if (token->type == C_OUTPUT && ft_strlen(token->word) == 1)
		fd = open(token->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (token->type == C_OUTPUT && ft_strlen(token->word) == 2)
		fd = open(token->next->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (token->type == C_INPUT && ft_strlen(token->word) == 1)
		fd = open(token->next->word, O_RDONLY);
	else if (token->type == C_INPUT && ft_strlen(token->word) == 2)
		manage_heredocs(token->next->word, &name, &fd);
	if (fd == -1)
		return (print_error(T_NOFILE, token->next->word, ENOENT));
	add_redir_back(&(*command)->redirs, new_redir(fd, token->type, &name));
	return (1);
}

static int	create_commands(t_token **head, t_command **parse)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		exit(errno);
	command->redirs = NULL;
	while (*head && (*head)->type != C_PIPE)
	{
		if ((*head)->type == C_WORD)
			add_command(&command, (*head)->word);
		else if ((*head)->type == C_OUTPUT || (*head)->type == C_INPUT)
		{
			if (!add_redirs(&command, (*head)))
			{
				free_commands(&command);
				return (0);
			}
			*head = (*head)->next;
		}
		*head = (*head)->next;
	}
	add_command_back(parse, command);
	return (1);
}

int	restore_tokens(t_token *lst, t_command **parse)
{
	t_token		*head;

	head = lst;
	while (head)
	{
		if (!create_commands(&head, parse))
			return (0);
		if (head)
			head = head->next;
	}
	return (1);
}
