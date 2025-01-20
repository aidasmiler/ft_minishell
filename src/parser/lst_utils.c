/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:30:11 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/10 16:29:20 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token	*new_token(char *word, int type)
{
	t_token	*newel;

	newel = malloc(sizeof(t_token));
	if (!newel)
		return (NULL);
	newel->word = ft_strdup(word);
	newel->type = type;
	newel->next = NULL;
	return (newel);
}

void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	add_command_back(t_command **lst, t_command *new)
{
	t_command	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
}

t_redir	*new_redir(int fd, int type, char **name)
{
	t_redir	*newel;

	newel = malloc(sizeof(t_token));
	if (!newel)
		return (NULL);
	newel->type = type;
	newel->fd = fd;
	newel->name = *name;
	newel->next = NULL;
	return (newel);
}

void	add_redir_back(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
