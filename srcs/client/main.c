/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 11:56:21 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/14 20:04:53 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_p.h"
#include <sys/socket.h>
#include <netinet/in.h>

static int 	receive(int sock, char *str)
{
	int 	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (SUCCESS);
	ft_putendl_sock(str, sock);
	if (ft_strcmp(str, "quit") == SUCCESS)
	{
		ft_strdel(&str);
		return (FAILURE);
	}
	ft_strdel(&str);
	while (gnl_sock(sock, &str) > 0)
	{
		if (ft_strcmp(str, EOT) == SUCCESS)
		{
			ft_strdel(&str);
			return (SUCCESS);
		}
		ft_putendl(str);
		ft_strdel(&str);
	}
	return (FAILURE);
}

int		main(int ac, char **av)
{
	int					port;
	int					sock;
	char				*str;

	if (ac != 3)
		return (ft_error("Usage: ./client machine port"));
	port = ft_atoi(av[2]);
	if ((sock = create_client(av[1], port)) == FAILURE)
		return (FAILURE);
	while (ft_putstr("CeciEstUnPrompt> "), get_next_line(0, &str))
	{
		if (receive(sock, str) == FAILURE)
			break ;
	}
	close(sock);
	return (SUCCESS);
}
