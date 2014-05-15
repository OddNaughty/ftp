/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/15 12:49:40 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/15 12:49:40 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_p.h"

static int	la_norme_c_bien_mais_pas_trop2(int pos, char *ptr, char **path)
{
	char	*newpath;
	int		i;

	newpath = ft_strnew(pos + 2);
	i = 0;
	while (i < pos)
	{
		newpath[i] = ptr[i];
		i++;
	}
	newpath[i] = '/';
	ft_strdel(path);
	*path = newpath;
	return (SUCCESS);
}

static int	goback(char **path)
{
	char	*ptr;
	int		i;
	int		pos;

	i = 0;
	ptr = *path;
	pos = 0;
	ptr[ft_strlen(ptr) - 1] = '\0';
	while (ptr[i])
	{
		if (ptr[i] == '/')
			pos = i;
		i++;
	}
	if (!pos)
	{
		ptr[ft_strlen(ptr)] = '/';
		return (FAILURE);
	}
	if (la_norme_c_bien_mais_pas_trop2(pos, ptr, path) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int	la_norme_c_bien_mais_pas_trop(char *str, t_data *data)
{
	char	*new;

	if (ft_strcmp(str, "..") == SUCCESS)
	{
		if (goback(&(data->pwd)) == FAILURE)
		{
			ft_putendleot_sock(
			"You can't go there... So start again from beginning"
			, data->fd_sock);
			return (FAILURE);
		}
	}
	else
	{
		new = ft_strjoin(data->pwd, str);
		ft_strdel(&(data->pwd));
		data->pwd = ft_strjoin(new, "/");
		ft_strdel(&new);
	}
	return (SUCCESS);
}

int			handle_path(t_data *data, char *path)
{
	char	**split;
	int		i;

	split = ft_strsplit(path, '/');
	i = 0;
	if (ft_strcmp(split[0], ".") == SUCCESS)
		i++;
	while (split[i])
	{
		if (la_norme_c_bien_mais_pas_trop(split[i], data) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
