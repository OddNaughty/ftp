/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 11:56:21 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/13 17:04:35 by cwagner          ###   ########.fr       */
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
	char				*str;

	if (ac != 3)
		return (ft_error("Usage: ./client machine port"));
	port = ft_atoi(av[2]);
	if ((sock = create_client(av[1], port)) == FAILURE)
		return (FAILURE);
	while (ft_putstr("CeciEstUnPrompt> "), get_next_line(0, &str))
	{
		if (ft_strcmp(str, "quit") == SUCCESS)
			break ;
		ft_putendl_fd(str, sock);
		free(str);
	}
	close(sock);
	return (SUCCESS);
}
