/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 11:56:21 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/14 16:43:09 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_p.h"
#include <sys/socket.h>
#include <netinet/in.h>

static int		treatment(int sock, int cs)
{
	t_data				data;

	close(sock);
	data.fd_sock = cs;
	data.pwd = ft_strdup("./");
	ft_putstr("A l'écoute : ");
	while (gnl_sock(cs, &(data.str)))
	{
		if (ft_strcmp(data.str, "quit") == SUCCESS)
			break ;
		if (data.str || *(data.str))
		{
			ft_putendl(data.str);
			interpret(&data);
			ft_strdel(&(data.str));
		}
		ft_putstr("A l'écoute : ");
	}
	close(cs);
	exit(SUCCESS);
}

static int		acpt(int sock)
{
	int					cs;
	unsigned int		addr_len;
	struct sockaddr_in	addr;

	ft_putendl("Waiting for a connection");
	while (1)
	{
		addr_len = sizeof(addr);
		cs = accept(sock, (struct sockaddr *)&addr, &addr_len);
		if (!fork())
			treatment(sock, cs);
		else
			close(cs);
	}
	return (SUCCESS);
}

int				main(int ac, char **av)
{
	int					port;
	int					sock;

	if (ac != 2)
		return (ft_error("Usage: ./serveur port"));
	port = ft_atoi(av[1]);
	if ((sock = create_server(port)) == FAILURE)
		return (FAILURE);
	if (acpt(sock) == FAILURE)
		return (FAILURE);
	close(sock);
	return (SUCCESS);
}
