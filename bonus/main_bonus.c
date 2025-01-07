/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:37:09 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/07 10:09:56 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	open_dup(t_args *args, int index, int pipefd[2][2])
{
	if (index == 0)
		dup_infile(args, pipefd);
	else if (index == args->ac - 4)
	{
		if (index % 2 == 0)
		{
			close(pipefd[0][0]);
			close(pipefd[0][1]);
			dup_outfile(args, pipefd[1]);
		}
		else
		{
			close(pipefd[1][0]);
			close(pipefd[1][1]);
			dup_outfile(args, pipefd[0]);
		}
	}
	else if (index != 0 && index != args->ac - 4)
		dup_pipe_cmd(index, pipefd);
}

void	child_process(int index, t_args *args, int pipefd[2][2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_handler(errno, "fork failed", NULL);
	if (pid == 0)
	{
		open_dup(args, index, pipefd);
		execute_cmd(args->av[index + 2], args->envp);
	}
}

void	pipex(t_args *args)
{
	int		pipefd[2][2];
	int		i;
	int		status;
	int		exit_status;

	if (pipe(pipefd[0]) == -1 || pipe(pipefd[1]) == -1)
		error_handler(errno, "pipe failed", NULL);
	i = -1;
	while (args->ac - 3 > ++i)
		child_process(i, args, pipefd);
	close_pipefd(pipefd);
	i = -1;
	while (args->ac - 3 > ++i)
	{
		waitpid(-1, &status, 0); //protect ??
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	check_cmd(args->av[args->ac - 2], args->envp, 1);
	if (exit_status != 0)
		exit(exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int		outfile;
	t_args	args;

	if (argc < 5)
	{
		errno = EINVAL;
		perror("5 arguments min needed (./pipex file1 cmd1 cmd2 ... file2)");
		exit(EXIT_FAILURE);
	}
	init_args(&args, argv, envp, argc);
	pipex(&args);
	outfile = open(argv[argc - 1], O_WRONLY);
	if (outfile < 0)
		exit(EXIT_FAILURE);
	close(outfile);
	exit(EXIT_SUCCESS);
}
