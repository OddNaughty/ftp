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
	static int	(*doit[NB_CMD])(t_data *data) =

	{
		ftp_ls,
		ftp_cd,
		ftp_get,
		ftp_put,
		ftp_pwd,
		ftp_mkdir
	};
	int 		i;

	i = 0;
	while (i < NB_CMD && (doit[i](data) == CONTINUE))
		i++;
	if (i == NB_CMD)
		ft_putendleot_sock("Unknown command", data->fd_sock);
	return (SUCCESS);
}
