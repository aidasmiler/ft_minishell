/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_ptrs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 18:57:23 by airodrig          #+#    #+#             */
/*   Updated: 2022/04/11 14:40:30 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_double_chr_ptr(char **dbl_ptr)
{
	int	i;

	i = -1;
	while (dbl_ptr && dbl_ptr[++i])
		free(dbl_ptr[i]);
	if (dbl_ptr)
		free(dbl_ptr);
}
