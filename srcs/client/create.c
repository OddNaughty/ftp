/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 12:25:19 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/13 17:01:42 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"
#include "libft.h"
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int		create_client(char *where, int port)
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
	if (!ft_strcmp("localhost", where))
		where = ft_strdup("127.0.0.1");
	addr.sin_addr.s_addr = inet_addr(where);
	if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)))
		return (ft_error("Unable to connect"));
	return (sock);
}
