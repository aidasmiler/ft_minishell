/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:24:00 by airodrig          #+#    #+#             */
/*   Updated: 2022/05/14 11:35:05 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	print_error(int type, char *str, int erno)
{
	errno = erno;
	ft_putstr_fd("Miley$hell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	if (type == T_SYNTAX)
		ft_putchar_fd('\n', STDERR_FILENO);
	else if (type == T_NOFILE)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (type == T_TOOMANYARGS)
		ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	else if (type == T_NOCMD)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (0);
}

int	print_redir_error(int type)
{
	errno = 258;
	ft_putstr_fd("Miley$hell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	if (type == C_INPUT)
		ft_putstr_fd("'<'\n", STDERR_FILENO);
	else if (type == C_OUTPUT)
		ft_putstr_fd("'>'\n", STDERR_FILENO);
	else if (type == C_PIPE)
		ft_putstr_fd("'|'\n", STDERR_FILENO);
	return (0);
}

int	print_type_of_args(char *cmd, char *arg)
{
	ft_putstr_fd("Miley$hell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	errno = 1;
	return (0);
}
