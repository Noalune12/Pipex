/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:10:23 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/07 10:10:24 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	dup_outfile(t_args *args, int pipefd[2])
{
	int	outfile;

	close(pipefd[1]);
	outfile = open(args->av[args->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		close(pipefd[0]);
		error_handler(errno, "Error opening output file", NULL);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[0]);
	close(outfile);
}

void	dup_infile(t_args *args, int pipefd[2][2])
{
	int	infile;

	close(pipefd[1][1]);
	close(pipefd[1][0]);
	close(pipefd[0][0]);
	infile = open(args->av[1], O_RDONLY);
	if (infile < 0)
	{
		close(pipefd[0][1]);
		error_handler(errno, "Error opening input file", NULL);
	}
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[0][1], STDOUT_FILENO);
	close(pipefd[0][1]);
	close(infile);
}

void	dup_pipe_cmd(int index, int pipefd[2][2])
{
	if (index % 2 == 1)
	{
		close(pipefd[1][0]);
		close(pipefd[0][1]);
		dup2(pipefd[0][0], STDIN_FILENO);
		dup2(pipefd[1][1], STDOUT_FILENO);
		close(pipefd[0][0]);
		close(pipefd[1][1]);
	}
	else
	{
		close(pipefd[1][1]);
		close(pipefd[0][0]);
		dup2(pipefd[1][0], STDIN_FILENO);
		dup2(pipefd[0][1], STDOUT_FILENO);
		close(pipefd[0][1]);
		close(pipefd[1][0]);
	}
}
