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

static int	get_file(char *str)
{

}

int	cmd_files(char *str)
{
	char	**split;

	split = ft_strsplitwhite(str);
	if ((ft_strcmp(split[0], "get") == SUCCESS) && split[1])
	{
		if (get_file(split[1]) == FAILURE)
			return (FAILURE);
	}
	else if (ft_strcmp(split[0], "put") == SUCCESS)
	{

	}
	return (CONTINUE);
}
