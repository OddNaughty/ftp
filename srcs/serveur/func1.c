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

int 	ftp_ls(t_data *data)
{
	struct dirent *pDirent;
	DIR *pDir;
	char	**split;

	if ((split = ft_strsplitwhite(data->str)) == NULL)
		return (FAILURE);
	if (ft_strcmp(split[0], "ls") != SUCCESS)
		return (CONTINUE);
	if (split[1])
	{
		ft_putendleot_sock("I don't want any arguments.", data->fd_sock);
		return (FAILURE);
	}
	if ((pDir = opendir(data->pwd)) == NULL)
	{
		ft_putendleot_sock("FATAL CRASH NOOB !", data->fd_sock);
		return (FAILURE);
	}
	while ((pDirent = readdir(pDir)) != NULL)
		ft_putendl_sock(pDirent->d_name, data->fd_sock);
	ft_putendl_sock(EOT, data->fd_sock);
	closedir (pDir);
	return (SUCCESS);
}

int 	ftp_cd(t_data *data)
{
	char	**split;
	DIR		*dir;

	if ((split = ft_strsplitwhite(data->str)) == NULL)
		return (FAILURE);
	if (ft_strcmp(split[0], "cd") != SUCCESS)
		return (CONTINUE);
	if (!split[1] || split[2])
	{
		ft_putendleot_sock("I just want an only argument.", data->fd_sock);
		return (FAILURE);
	}
	if ((dir = opendir(ft_strjoin(data->pwd, split[1]))))
		closedir(dir);
	else
	{
		ft_putendleot_sock("It's not a folder", data->fd_sock);
		return (FAILURE);
	}
	if (handle_path(data, split[1]) == FAILURE)
		return (FAILURE);
	ft_putendleot_sock(data->pwd, data->fd_sock);
	return (SUCCESS);
}

int 	ftp_get(t_data *data)
{
	char	**split;
	char 	*str;

	str = data->str;
	if ((split = ft_strsplitwhite(str)) == NULL)
		return (FAILURE);
	if (ft_strcmp(split[0], "get") != SUCCESS)
	{
		ft_freechartab(&split);
		return (CONTINUE);
	}
	if (!split[1])
	{
	}
	return (CONTINUE);
}

int 	ftp_put(t_data *data)
{
	(void)data;
	return (CONTINUE);
}

int 	ftp_pwd(t_data *data)
{
	char	**split;
	char 	*str;

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
		ft_putendleot_sock("Usage: Just type pwd to know where you are", data->fd_sock);
	ft_freechartab(&split);
	return (SUCCESS);
}
