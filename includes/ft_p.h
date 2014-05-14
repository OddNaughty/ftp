/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 11:38:48 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/14 18:31:57 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P
# define FT_P

typedef struct s_data
{
	int 		fd_sock;
	char		*str;
}				t_data;

int		create_server(int port);
int		create_client(char *addr, int port);

int 	interpret(t_data *data);

int 	ftp_ls(t_data *data);
int 	ftp_cd(t_data *data);
int 	ftp_pwd(t_data *data);
int 	ftp_get(t_data *data);
int 	ftp_put(t_data *data);

char	*g_pwd;
#endif
