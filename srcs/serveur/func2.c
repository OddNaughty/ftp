//
// Created by Camille WAGNER on 01/12/15.
//

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "ft_p.h"

int 		ftp_mkdir(t_data *data)
{
	char	**split;
	int 	ret;

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
