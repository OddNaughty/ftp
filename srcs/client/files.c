/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 21:17:16 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/15 21:17:17 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/socket.h>
#include "libft.h"
#include "ft_p.h"
#include <stdio.h>

static int	put_file(char *file, int sock)
{
	char	*tosend;
	int		fd;
	int		size;

	tosend = ft_strnew(1024);
	if ((fd = open(file, O_RDONLY)) == FAILURE)
	{
		tosend = ft_strcpy(tosend, EOT);
		tosend = ft_strjoin(tosend, "Can't open file...");
		send(sock, tosend, 1024, 0);
		return (ft_error("Can't open the file..."));
	}
	while ((size = read(fd, tosend, 1024)) > 0)
	{
		send(sock, tosend, size, 0);
		ft_strdel(&tosend);
		tosend = ft_strnew(1024);
	}
	if (size != FAILURE)
	{
		send(sock, tosend, size, 0);
		ft_strdel(&tosend);
	}
	close (fd);
	ft_putendl("Transmission done");
	return (SUCCESS);
}

static int	get_file(char *file, int sock)
{
	char	*str;
	int		fd;
	int		size;

	str = ft_strnew(1024);
	if ((size = recv(sock, str, 1024, 0)) == FAILURE)
		return (FAILURE);
	if (ft_strncmp(EOT, str, ft_strlen(EOT)) == SUCCESS)
	{
		ft_putendl(str + ft_strlen(EOT));
		return (SUCCESS);
	}
	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == FAILURE)
		return (ft_error("Open failed..."));
	write(fd, str, size);
	if (size < 1024)
	{
		close(fd);
		return (SUCCESS);
	}
	ft_strdel(&str);
	str = ft_strnew(1024);
	while ((size = recv(sock, str, 1024, 0)) == 1024)
	{
		write(fd, str, size);
		ft_strdel(&str);
		str = ft_strnew(1024);
	}
	if (size == FAILURE)
		return (ft_error("Got a problem while receiving"));
	write(fd, str, size);
	ft_strdel(&str);
	close (fd);
	ft_putendl("File successfully get");
	return (SUCCESS);
}

int	cmd_files(char *str, int sock)
{
	char	**split;
	char	**split2;
	int		file;

	split = ft_strsplitwhite(str);
	if ((ft_strcmp(split[0], "get") == SUCCESS) || (ft_strcmp(split[0], "put") == SUCCESS))
	{
		if (!split[1])
			return (ft_error("I need a file to get"));
		split2 = ft_strsplit(split[1], '/');
		file = ft_chartablength(split2) - 1;
		if (ft_strcmp(split[0], "get") == SUCCESS)
		{
			if (get_file(split2[file], sock) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
		else if (ft_strcmp(split[0], "put") == SUCCESS)
		{
			if (put_file(split[1], sock) == FAILURE)
				return (FAILURE);
			return (SUCCESS);
		}
	}
	return (CONTINUE);
}
