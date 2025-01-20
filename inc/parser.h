/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 00:45:36 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 11:32:18 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <stdlib.h> // malloc, free, exit, getenv
# include <sys/errno.h> //errno
# include <stdio.h> // strerror, perror, readline
# include <readline/readline.h> // readline
# include <readline/history.h> // readline
# include <stdbool.h> // boolean

# define NOCOL		"\033[0m"
# define RED		"\033[1;31m"
# define ORG		"\033[0;33m"
# define YEL		"\033[1;33m"
# define GRN		"\033[1;32m"
# define BLU		"\033[0;34m"
# define CYN		"\033[0;36m"
# define PUR		"\033[0;35m"

# define PROMPT "\033[0;33m \U0001F981 〽iley$hell > \U0001F445 \033[0m "
# define PROMPT_HEREDOC "\033[48:5:234m \U0001F525 \033[0m\033[38:5:202m ⫸ \033[0m"

enum e_chart{
	C_SQUOTE = '\'',
	C_DQUOTE = '"',
	C_DOLLAR = '$',
	C_INPUT = '<',
	C_OUTPUT = '>',
	C_PIPE = '|',
	C_SPACE = ' ',
	C_QUESTION = '?',
	C_WORD = '0'
};

enum e_states{
	S_NORMAL,
	S_SQUOTE,
	S_DQUOTE
};

enum e_error{
	T_SYNTAX,
	T_NOFILE,
	T_TOOMANYARGS,
	T_NOCMD
};

typedef struct s_token
{
	int				type;
	char			*word;
	struct s_token	*next;
}t_token;

typedef struct s_redir
{
	int				type;
	int				fd;
	char			*name;
	struct s_redir	*next;
}t_redir;

typedef struct s_command
{
	char				**cmd;
	t_redir				*redirs;
	struct s_command	*next;
	struct s_command	*previous;
}t_command;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}t_env;

///////////////////////////////////////////////////////////////
// parser
///////////////////////////////////////////////////////////////

// tokenizer.c
int		tokenize_line(char *line, t_token **token);
// parser.c
int		restore_tokens(t_token *lst, t_command **parse);
// lexer_parser_utils.c
int		gettype(char c);
bool	is_word(int type);
int		get_name_expand(char *line, int *i, char **expand);
void	expand_this_one(char **line, int i);
// heredoc_utils.c
void	expand_heredoc(char **line);
int		close_open(int fd, char *name);
int		heredoc_maker(char *eof, char **name);
void	heredoc_parent(int *fd, char **name, int pid);
// signals_utils.c
void	signals_heredoc(void);
void	ignore_signals(void);

// lst_utils.c
t_token	*new_token(char *word, int type);
void	add_token_back(t_token **lst, t_token *new);
void	add_command_back(t_command **lst, t_command *new);
t_redir	*new_redir(int fd, int type, char **name);
void	add_redir_back(t_redir **lst, t_redir *new);
void	free_commands(t_command **command);

///////////////////////////////////////////////////////////////
// print
///////////////////////////////////////////////////////////////
// print_utils.c
void	print_tokens(t_token *token);
void	print_commands(t_command *command);
void	print_env(t_env *env_lst);
// print_error.c
int		print_error(int type, char *str, int erno);
int		print_redir_error(int type);
int		print_type_of_args(char *cmd, char *arg);

#endif
