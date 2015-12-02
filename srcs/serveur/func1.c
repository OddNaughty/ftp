/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 17:46:52 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/14 19:20:12 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_p.h"
#include <dirent.h>
#include <errno.h>
#include <sys/socket.h>

static int	ftp_get2(int fd, t_data *data)
{
	int		size;
	char	*tosend;

	tosend = ft_strnew(1024);
	while ((size = read(fd, tosend, 1024)) > 0)
	{
		send(data->fd_sock, tosend, size, 0);
		ft_strdel(&tosend);
		tosend = ft_strnew(1024);
	}
	if (size != FAILURE)
	{
		send(data->fd_sock, tosend, size, 0);
		ft_strdel(&tosend);
	}
	close(fd);
	return (SUCCESS);
}

int			ftp_get(t_data *data)
{
	char	**split;
	char	*str;
	char	*tosend;
	int		fd;

	str = data->str;
	if ((split = ft_strsplitwhite(str)) == NULL)
		return (FAILURE);
	if (ft_strcmp(split[0], "get") != SUCCESS)
	{
		ft_freechartab(&split);
		return (CONTINUE);
	}
	tosend = ft_strnew(1024);
	if ((fd = open(ft_strjoin(data->pwd, split[1]), O_RDONLY)) == FAILURE)
	{
		tosend = ft_strcpy(tosend, EOT);
		tosend = ft_strjoin(tosend, "Can't open file...");
		send(data->fd_sock, tosend, 1024, 0);
		return (FAILURE);
	}
	ft_strdel(&tosend);
	return (ftp_get2(fd, data));
}

static int	ftp_put2(t_data *data, int size, int fd)
{
	char	*str;

	if (size < 1024)
	{
		close(fd);
		return (SUCCESS);
	}
	str = ft_strnew(1024);
	while ((size = recv(data->fd_sock, str, 1024, 0)) == 1024)
	{
		write(fd, str, size);
		ft_strdel(&str);
		str = ft_strnew(1024);
	}
	if (size == FAILURE)
		return (SUCCESS);
	write(fd, str, size);
	ft_strdel(&str);
	close(fd);
	return (SUCCESS);
}

int			ftp_put(t_data *data)
{
	char	**split;
	char	**split2;
	int		fd;
	char	*str;
	int		size;

	split = ft_strsplitwhite(data->str);
	if (ft_strcmp(split[0], "put") != SUCCESS)
		return (CONTINUE);
	str = ft_strnew(1024);
	if ((size = recv(data->fd_sock, str, 1024, 0)) == FAILURE)
		return (FAILURE);
	if (ft_strncmp(EOT, str, ft_strlen(EOT)) == SUCCESS)
		return (SUCCESS);
	split2 = ft_strsplit(split[1], '/');
	fd = open(ft_strjoin(data->pwd, split2[ft_chartablength(split2) - 1]),
		O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	write(fd, str, size);
	return (ftp_put2(data, size, fd));
}

int			ftp_pwd(t_data *data)
{
	char	**split;
	char	*str;

	str = data->str;
	if ((split = ft_strsplitwhite(str)) == NULL)
		return (FAILURE);
	if (ft_strcmp(split[0], "pwd") != SUCCESS)
	{
		ft_freechartab(&split);
		return (CONTINUE);
	}
	if (!split[1])
		ft_putendleot_sock(data->pwd, data->fd_sock);
	else
		ft_putendleot_sock("Usage: Just type pwd to know where you are",
			data->fd_sock);
	ft_freechartab(&split);
	return (SUCCESS);
}
