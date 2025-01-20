/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:58:36 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/05 18:11:43 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_tokens(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Token: %s de tipo %c\n", tmp->word, tmp->type);
		tmp = tmp->next;
	}
}

static void	print_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		printf("Redir con fd: %d de tipo %c\n", tmp->fd, tmp->type);
		tmp = tmp->next;
	}
}

void	print_commands(t_command *command)
{
	t_command	*tmp;
	int			i;

	tmp = command;
	while (tmp)
	{
		i = -1;
		printf("Round ------------------>");
		while (tmp && tmp->cmd[++i])
			printf("Command: %s\n", tmp->cmd[i]);
		if (tmp->redirs)
			print_redirs(tmp->redirs);
		tmp = tmp->next;
	}
}

void	print_env(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}
