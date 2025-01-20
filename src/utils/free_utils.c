/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:16:14 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/08 17:35:03 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **lst)
{
	t_token	*head;

	while (*lst)
	{
		head = (*lst)->next;
		free((*lst)->word);
		free(*lst);
		*lst = head;
	}
}

static void	free_redirs(t_redir **lst)
{
	t_redir	*head;

	while (*lst)
	{
		head = (*lst)->next;
		if ((*lst)->name)
		{
			if (unlink((*lst)->name) == -1)
				exit (errno);
			free((*lst)->name);
		}
		close((*lst)->fd);
		free(*lst);
		*lst = head;
	}
}

void	free_commands(t_command **command)
{
	t_command	*head;

	while (*command)
	{
		head = (*command)->next;
		free_double_chr_ptr((*command)->cmd);
		if ((*command)->redirs)
			free_redirs(&(*command)->redirs);
		free(*command);
		*command = head;
	}
}

void	free_env(t_env **lst)
{
	t_env	*head;

	while (*lst)
	{
		head = (*lst)->next;
		free((*lst)->name);
		free((*lst)->content);
		free(*lst);
		*lst = head;
	}
}
