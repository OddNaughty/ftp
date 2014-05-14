/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 12:25:19 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/14 18:33:44 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include "libft.h"
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
    struct sockaddr_in	addr;

	if ((proto = getprotobyname("tcp")) == NULL)
		return (ft_error("Can't get protocol"));
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == FAILURE)
		return (ft_error("Socket creating error"));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htons(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&addr, sizeof(addr)))
		return (ft_error("Unable to bind"));
	if (listen(sock, 42))
		return (ft_error("Can't listen it"));
	return (sock);
}
