/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:12:01 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 11:44:38 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_tokens(t_token *token)
{
	t_token	*head;

	head = token;
	while (head)
	{
		if (head->type == C_PIPE && (ft_strlen(head->word) > 1 || !head->next))
			return (print_error(T_SYNTAX,
					"syntax error near unexpected token '|'", 2));
		else if (head->type == C_INPUT && ft_strlen(head->word) > 2)
			return (print_error(T_SYNTAX,
					"syntax error near unexpected token '<'", 2));
		else if (head->type == C_OUTPUT && ft_strlen(head->word) > 2)
			return (print_error(T_SYNTAX,
					"syntax error near unexpected token '>'", 2));
		else if (head->next && head->type == head->next->type
			&& head->type != C_WORD)
			return (print_redir_error(head->next->type));
		head = head->next;
	}
	return (1);
}

static int	is_normal(char **line, int *i, t_token **token, char **word)
{
	if ((*line)[*i] == C_DOLLAR)
		expand_this_one(line, *i);
	if (gettype((*line)[*i]) == C_SQUOTE)
		return (S_SQUOTE);
	else if (gettype((*line)[*i]) == C_DQUOTE)
		return (S_DQUOTE);
	else if (gettype((*line)[*i]) == C_SPACE)
		return (S_NORMAL);
	*word = strjoin_chr(*word, (*line)[*i]);
	if (!(*line)[*i])
	{
		if ((*i)-- && *word)
			add_token_back(token, new_token(*word, gettype(*word[0])));
		return (S_NORMAL);
	}
	if (!(*line)[*i + 1] || (gettype((*line)[*i]) != gettype((*line)[*i + 1])
		&& (!is_word(gettype((*line)[*i + 1]))
		|| !is_word(gettype((*line)[*i])))))
	{
		add_token_back(token, new_token(*word, gettype((*line)[*i])));
		ft_bzero(*word, ft_strlen(*word));
	}
	return (S_NORMAL);
}

static int	is_squote(char *line, int *i, t_token **token, char **word)
{
	if (!line[*i + 1] || (line[*i] == C_SQUOTE
			&& !is_word(gettype(line[*i + 1]))))
	{
		add_token_back(token, new_token(*word, C_WORD));
		ft_bzero(*word, ft_strlen(*word));
	}
	if (gettype(line[*i]) == C_SQUOTE)
		return (S_NORMAL);
	*word = strjoin_chr(*word, line[*i]);
	return (S_SQUOTE);
}

static int	is_dquote(char **line, int *i, t_token **token, char **word)
{
	if (!(*line)[*i + 1] || ((*line)[*i] == C_DQUOTE
			&& !is_word(gettype((*line)[*i + 1]))))
	{
		add_token_back(token, new_token(*word, C_WORD));
		ft_bzero(*word, ft_strlen(*word));
	}
	if (gettype((*line)[*i]) == C_DQUOTE)
		return (S_NORMAL);
	if ((*line)[*i] == C_DOLLAR)
		expand_this_one(line, *i);
	if (!(*line)[*i] || gettype((*line)[*i]) == C_DQUOTE)
	{
		(*i)--;
		return (S_DQUOTE);
	}
	*word = strjoin_chr(*word, (*line)[*i]);
	return (S_DQUOTE);
}

int	tokenize_line(char *line, t_token **token)
{
	int		i;
	int		state;
	char	*word;

	i = -1;
	state = S_NORMAL;
	word = ft_calloc(sizeof(char), 1);
	while (line && line[++i])
	{
		if (state == S_NORMAL)
			state = is_normal(&line, &i, token, &word);
		else if (state == S_SQUOTE)
			state = is_squote(line, &i, token, &word);
		else if (state == S_DQUOTE)
			state = is_dquote(&line, &i, token, &word);
	}
	if (word)
		free(word);
	free(line);
	if (state != S_NORMAL)
		return (print_error(T_SYNTAX, "Expected closing quotation", 2));
	if (!check_tokens(*token))
		return (0);
	return (1);
}
