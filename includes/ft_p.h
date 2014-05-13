/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 11:38:48 by cwagner           #+#    #+#             */
/*   Updated: 2014/05/13 17:50:37 by cwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P
# define FT_P

int		create_server(int port);
int		create_client(char *addr, int port);

int 	ftp_ls(char *str);
int 	ftp_cd(char *str);
int 	ftp_pwd(char *str);
int 	ftp_get(char *str);
int 	ftp_put(char *str);

#endif
