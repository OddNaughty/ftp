/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 17:31:27 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/14 18:33:47 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include "libft.h"
#include <sys/socket.h>

int 	interpret(t_data *data)
{
	static int	(*doit[5])(t_data *data) =

	{
		ftp_ls,
		ftp_cd,
		ftp_get,
		ftp_put,
		ftp_pwd
	};
	int 		i;

	i = 0;
	while (i < 5 && (doit[i](data) == CONTINUE))
		i++;
	if (i == 5)
		ft_putendleot_sock("Unknown command", data->fd_sock);
	return (SUCCESS);
}
