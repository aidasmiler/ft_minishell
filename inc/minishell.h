/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:50:13 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/13 14:01:19 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"

# include <unistd.h> // write, access, close, fork, getcwd, chdir, unlink,
// execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <fcntl.h> // open
# include <sys/types.h> // read
# include <sys/wait.h> // wait, waitpid, wait3, wait4
# include <signal.h> // signal, sigaction, kill
# include <sys/stat.h> // stat, lstat, fstat
# include <dirent.h> // opendir, readdir, closedir
# include <sys/ioctl.h> // ioctl
# include <termios.h> // tcsetattr, tcgetattr
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# define READ 0
# define WRITE 1

extern t_env	*g_env_lst;

// banner & prompt
void	print_banner(void);
char	*prompt(void);

///////////////////////////////////////////////////////////////
// env_to_lst.c
///////////////////////////////////////////////////////////////
t_env	*new_var(char **name, char **content);
void	add_var_back(t_env **lst, t_env *new);
void	make_env(char	**env, t_env **env_lst);
char	*ft_getenv(char	*name);
char	**turn_lst_to_array(void);

///////////////////////////////////////////////////////////////
// executor
///////////////////////////////////////////////////////////////
void	executor(t_command	*lst, int stdin_fd, int stdout_fd);
void	manage_redirs(t_redir *redirs);
int		change_cmd(char **cmd);
void	restore_org_fds(int stdin_fd, int stdout_fd);

///////////////////////////////////////////////////////////////
// builtins
///////////////////////////////////////////////////////////////
// echo_pwd_exit_env.c
void	ft_echo(char **cmd);
void	ft_pwd(void);
int		ft_exit(char **cmd);
void	ft_env(void);
// cd_env_unset.c
void	change_create_var(char *name, char	*new_content);
int		ft_cd(char **cmd);
void	ft_unset(char **cmd);
// export.c
void	ft_export(char **cmd);
// main_builtins.c
void	manage_builtins(char **cmd);
int		is_builtin(char *cmd);

///////////////////////////////////////////////////////////////
// other_utils
///////////////////////////////////////////////////////////////
int		env_lstsize(t_env *lst);
// signals_utils.c
void	manage_signals(int signal);
void	my_signal(void);
void	child_signals(int signal);

///////////////////////////////////////////////////////////////
// free_utils.c
///////////////////////////////////////////////////////////////
void	free_tokens(t_token **lst);
void	free_env(t_env **lst);

#endif
