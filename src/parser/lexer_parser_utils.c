/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:22:27 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/11 15:24:29 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gettype(char c)
{
	int					i;
	const char			special[6] = {'\'', '"', '<', '>', '|', ' '};
	const enum e_chart	charas[6] = {C_SQUOTE, C_DQUOTE, C_INPUT, C_OUTPUT,
		C_PIPE, C_SPACE};

	i = -1;
	while (++i < 6)
		if (c == special[i])
			return (charas[i]);
	return (C_WORD);
}

bool	is_word(int type)
{
	if (type == C_SQUOTE || type == C_DQUOTE || type == C_WORD)
		return (true);
	else
		return (false);
}

int	get_name_expand(char *line, int *i, char **expand)
{
	char	*name;

	name = ft_calloc(1, sizeof(char));
	while (line[++(*i)] && gettype(line[*i]) == C_WORD
		&& line[*i] != C_DOLLAR)
	name = strjoin_chr(name, line[*i]);
	if (!name[0])
		return (0);
	*expand = ft_getenv(name);
	free(name);
	if (!(*expand))
		*expand = ft_calloc(1, sizeof(char));
	return (1);
}

void	expand_this_one(char **line, int i)
{
	char	*expand;
	char	*final_line;
	char	*cut_line;

	cut_line = ft_substr(*line, 0, i);
	if ((*line)[i + 1] && (*line)[i + 1] == C_QUESTION)
	{
		i += 2;
		expand = ft_itoa(errno);
	}
	else
		if (!get_name_expand(*line, &i, &expand))
			return ;
	final_line = ft_strjoin(expand, &(*line)[i]);
	free(*line);
	*line = ft_strjoin(cut_line, final_line);
	free(final_line);
	free(cut_line);
	free(expand);
}
