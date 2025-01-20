/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 01:02:55 by marvin            #+#    #+#             */
/*   Updated: 2022/05/16 17:57:36 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_new_prompt(char **str1, char *str2)
{
	char	*new_prompt;

	new_prompt = ft_strjoin(*str1, str2);
	free(*str1);
	return (new_prompt);
}

char	*prompt(void)
{
	char	*user;
	char	*dir;
	char	*prompt;
	char	*tmp;

	user = ft_getenv("USER");
	if (!user)
		user = ft_strdup("user");
	tmp = ft_getenv("PWD");
	if (tmp && tmp[0])
	{
		dir = ft_strtrim(ft_strrchr(tmp, '/'), "/");
		free(tmp);
	}
	else
		dir = ft_strdup("dir");
	prompt = ft_strdup("\033[38:5:237m\033[48:5:234m \U0001F525 \033[48:5:254m ");
	prompt = get_new_prompt(&prompt, user);
	prompt = get_new_prompt(&prompt,
			" \033[48:5:63m\033[38:5:253m \U0001F4C1 ");
	prompt = get_new_prompt(&prompt, dir);
	prompt = get_new_prompt(&prompt, " \033[0m\033[38:5:63m ⫸  \033[0m");
	free(user);
	free(dir);
	return (prompt);
}
