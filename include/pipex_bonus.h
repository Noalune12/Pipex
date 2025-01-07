/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:45:52 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/07 13:00:05 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	int		ac;
	char	**av;
	char	**envp;
}	t_args;

void	init_args(t_args *args, char **av, char **envp, int ac);
char	**split_cmd(char const *s, char *charset);
void	execute_cmd(char *cmd, char **envp);
char	*find_exec_cmd(char **cmds, char **envp, int check);
void	ft_free_double(char **strs);
int		error_handler(int errnum, char *message, char **strs);
void	check_cmd(char *cmd, char **envp, int check);
void	dup_outfile(t_args *args, int pipefd[2]);
void	dup_infile(t_args *args, int pipefd[2][2]);
void	dup_pipe_cmd(int index, int pipefd[2][2]);
void	close_pipefd(int pipefd[2][2]);

#endif
