/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 13:22:26 by cwagner           #+#    #+#             */
/*   Updated: 2015/12/02 13:22:29 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "ft_p.h"

int		ftp_mkdir(t_data *data)
{
	char	**split;
	int		ret;

	if ((split = ft_strsplitwhite(data->str)) == NULL)
		return (FAILURE);
	if (ft_strcmp(split[0], "mkdir") != SUCCESS)
		return (CONTINUE);
	if (!split[1] || split[2])
	{
		ft_putendleot_sock("I just want an only argument.", data->fd_sock);
		return (FAILURE);
	}
	ret = mkdir(ft_strjoin(data->pwd, split[1]), S_IRWXU);
	if (!ret)
		ft_putendleot_sock("Directory created", data->fd_sock);
	else
		ft_putendleot_sock("Directory created", data->fd_sock);
	return (ret);
}

int		ftp_ls(t_data *data)
{
	char	**split;
	pid_t	statu;
	pid_t	ret;

	if ((split = ft_strsplitwhite(data->str)) == NULL)
		return (FAILURE);
	if (ft_strcmp(split[0], "ls") != SUCCESS)
		return (CONTINUE);
	if ((ret = fork()) == FAILURE)
		return (FAILURE);
	else if (!ret)
	{
		chdir(data->pwd);
		if (dup2(data->fd_sock, 1) < 0)
			ft_putendl("KAKAKAKA");
		if ((execve("/bin/ls", split, NULL)) == FAILURE)
			exit(FAILURE);
	}
	else
	{
		waitpid(ret, &statu, 0);
		ft_putendleot_sock("", data->fd_sock);
	}
	return (WIFEXITED(statu));
}

int		ftp_cd(t_data *data)
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
