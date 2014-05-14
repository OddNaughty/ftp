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

int 	ftp_ls(t_data *data)
{
	(void)data;
	// int len;
	// struct dirent *pDirent;
	// DIR *pDir;

	// if (c < 2) 
	// {
	// 	printf ("Usage: testprog <dirname>\n");
	// 	return 1;
	// }
	// pDir = opendir (v[1]);
	// if (pDir == NULL)
	// {
	// 	printf ("Cannot open directory '%s'\n", v[1]);
	// 	return 1;
	// }
	// while ((pDirent = readdir(pDir)) != NULL)
	// 	printf ("[%s]\n", pDirent->d_name);
	// closedir (pDir);
	return (CONTINUE);
}

int 	ftp_cd(t_data *data)
{
	(void)data;
	return (CONTINUE);
}

int 	ftp_get(t_data *data)
{
	(void)data;
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
		ft_putendleot_sock(g_pwd, data->fd_sock);
	else
		ft_putendleot_sock("Usage: Just type pwd to know where you are", data->fd_sock);
	ft_freechartab(&split);
	return (SUCCESS);
}
