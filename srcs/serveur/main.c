/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 11:56:21 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/13 17:48:28 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_p.h"
#include <sys/socket.h>
#include <netinet/in.h>


int		main(int ac, char **av)
{
	int					port;
	int					sock;
	int					cs;
	unsigned int		addr_len;
	struct sockaddr_in	addr;
	char				*str;

	if (ac != 2)
		return (ft_error("Usage: ./serveur port"));
	port = ft_atoi(av[1]);
	if ((sock = create_server(port)) == FAILURE)
		return (FAILURE);
	addr_len = sizeof(addr);
	cs = accept(sock, (struct sockaddr *)&addr, &addr_len);
	while (ft_putstr("A l'écoute: "), get_next_line(cs, &str))
	{
		if (ft_strcmp(str, "quit") == SUCCESS)
			break ;
		if (str || *str)
		{
			interpret(str);
			free(str);
		}
	}
	close(cs);
	close(sock);
	return (SUCCESS);
}