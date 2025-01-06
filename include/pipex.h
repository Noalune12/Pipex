/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:40:52 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/06 14:15:29 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

void	execute_cmd(char *cmd, char **envp);
char	*find_exec_cmd(char **cmds, char **envp, int check);
void	ft_free_double(char **strs);
int		error_handler(int errnum, char *message, char **strs);
void	check_cmd(char *cmd, char **envp, int check);

#endif
