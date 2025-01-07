/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:37:09 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/07 08:47:26 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdio.h>

void	dup_outfile(char **av, int pipefd[2], int ac)
{
	int	outfile;

	close(pipefd[1]);
	outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	open_dup(int ac, int index, char **av, int pipefd[2][2])
{
	int	infile;

	if (index == 0)
	{
		close(pipefd[1][1]);
		close(pipefd[1][0]);
		close(pipefd[0][0]);
		infile = open(av[1], O_RDONLY);
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
	else if (index == ac - 4)
	{
		if (index % 2 == 0)
		{
			close(pipefd[0][0]);
			close(pipefd[0][1]);
			dup_outfile(av, pipefd[1], ac);
		}
		else
		{
			close(pipefd[1][0]);
			close(pipefd[1][1]);
			dup_outfile(av, pipefd[0], ac);
		}
	}
	else if (index != 0 && index != ac - 4)
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
}

void	child_process(int index, int ac, char **av, char **envp, int pipefd[2][2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_handler(errno, "fork failed", NULL);
	if (pid == 0)
	{
		open_dup(ac, index, av, pipefd);
		execute_cmd(av[index + 2], envp);
		// exit(0);
	}
}

void	pipex(int ac, char **av, char **envp)
{
	int		pipefd[2][2];
	int		i;
	int		status;
	int		exit_status;

	if (pipe(pipefd[0]) == -1 || pipe(pipefd[1]) == -1)
		error_handler(errno, "pipe failed", NULL);
	i = -1;
	while (ac - 3 > ++i)
		child_process(i, ac, av, envp, pipefd);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][0]);
	close(pipefd[1][1]);
	i = -1;
	while (ac - 3 > ++i)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	check_cmd(av[ac - 2], envp, 1);
	if (exit_status != 0)
		exit(exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int	outfile;

	if (argc < 5)
	{
		errno = EINVAL;
		perror("5 arguments or more needed (./pipex file1 cmd1 cmd2 ... file2)");
		exit(EXIT_FAILURE);
	}
	pipex(argc, argv, envp);
	outfile = open(argv[argc - 1], O_WRONLY);
	if (outfile < 0)
		exit(EXIT_FAILURE);
	close(outfile);
	exit(EXIT_SUCCESS);
}
