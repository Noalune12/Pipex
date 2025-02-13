/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:39:34 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/07 10:10:17 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	init_args(t_args *args, char **av, char **envp, int ac)
{
	args->av = av;
	args->envp = envp;
	args->ac = ac;
}

void	close_pipefd(int pipefd[2][2])
{
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][0]);
	close(pipefd[1][1]);
}

void	ft_free_double(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free (strs);
		strs = NULL;
	}
}

int	error_handler(int errnum, char *message, char **strs)
{
	if (strs)
		ft_free_double(strs);
	if (errnum)
	{
		errno = errnum;
		perror(message);
	}
	if (errnum == 127)
		exit(errnum);
	exit(EXIT_FAILURE);
}

void	check_cmd(char *cmd, char **envp, int check)
{
	char	**cmds;
	char	*exec;

	cmds = ft_split(cmd, " ");
	if (!cmds)
		error_handler(errno, "Split failed", NULL);
	exec = find_exec_cmd(cmds, envp, check);
	free(exec);
	ft_free_double(cmds);
}
