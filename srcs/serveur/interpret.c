/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 17:31:27 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/13 17:46:28 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int 	interpret(char *str)
{
	static int	(*doit[5])(char *str) =

	{
		ftp_ls,
		ftp_cd,
		ftp_get,
		ftp_put,
		ftp_pwd
	};
	int 		i;

	i = 0;
	while (i < 5 && (doit[i] == CONTINUE))
		i++;
	if (i == 5)
		return (ft_error("Unknown command"));
	return (SUCCESS);
}