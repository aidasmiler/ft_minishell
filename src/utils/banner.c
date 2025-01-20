/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airodrig <airodrig@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:54:04 by mcordoba          #+#    #+#             */
/*   Updated: 2022/05/12 18:57:11 by airodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_banner_second_part(void)
{
	printf(ORG"     88    88  \
  Y8,_,88,_,d8b,_  ²YbadP¹ ,d8b, ,d8I ^888,,____,dP,d8   \
  I8, ²YbadP¹ ,d8b,_ ,d8b,_  \n");
	printf(YEL"     88    88  \
  ²Y88P^^Y88P¹^Y88888P^Y888P^^Y88P^888a8P^Y88888P^ 88P   \
  ²Y8888^Y8888P¹^Y888P¹^Y88  \n");
	printf(GRN"                                          \
      ,d8I¹                                                \n");
	printf(BLU"                                          \
    ,dP¹8I                                                 \n");
	printf(CYN"                                          \
   ,8^  8I           airodrig  &  mcordoba                 \n");
	printf(PUR"                                          \
   I8   8I                                                 \n");
	printf(RED"                                          \
   ²8, ,8I                                                 \n");
	printf(ORG"                                          \
    ²Y8P^                                                  \n");
	printf(NOCOL"                                          \
                                                           \n");
}

void	print_banner(void)
{
	printf("\n");
	printf(RED" ,ggg, ,ggg,_,ggg,                                    \
     ,gg,                                      \n");
	printf(ORG"dP^^Y8dP^^Y88P^^Y8b        ,dPYb,                     \
    i8^^8i   ,dPYb,              ,dPYb, ,dPYb, \n");
	printf(YEL"Yb, ²88¹  ²88¹  ²88        IP¹²Yb                     \
    ²8,,8¹   IP¹²Yb              IP¹²Yb IP¹²Yb \n");
	printf(GRN" ²^  88    88    88   gg   I8  8I                     \
     ²88¹    I8  8I              I8  8I I8  8I \n");
	printf(BLU"     88    88    88   ^^   I8  8¹                     \
     dP¨8,   I8  8¹              I8  8¹ I8  8¹ \n");
	printf(CYN"     88    88    88   gg   I8 dP   ,ggg,   gg     gg  \
    dP¹ ²8a  I8 dPgg,    ,ggg,   I8 dP  I8 dP  \n");
	printf(PUR"     88    88    88   88   I8dP   i8^ ^8i  I8     8I  \
   dP¹   ²Yb I8dP^ ^8I  i8^ ^8i  I8dP   I8dP   \n");
	printf(RED"     88    88    88   88   I8P    I8, ,8I  I8,  \
 ,8I _ ,dP¹     I8 I8P    I8  I8, ,8I  I8P    I8P    \n");
	print_banner_second_part();
}
