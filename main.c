/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:37:09 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/06 14:07:08 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_outfile(char **av, int pipefd[2])
{
	int	outfile;

	close(pipefd[1]);
	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

void	open_dup(int index, char **av, int pipefd[2])
{
	int	infile;

	if (index == 0)
	{
		close(pipefd[0]);
		infile = open(av[1], O_RDONLY);
		if (infile < 0)
		{
			close(pipefd[1]);
			error_handler(errno, "Error opening input file", NULL);
		}
		dup2(infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(infile);
	}
	else
		dup_outfile(av, pipefd);
}

void	child_process(int index, char **av, char **envp, int pipefd[2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_handler(errno, "fork failed", NULL);
	if (pid == 0)
	{
		open_dup(index, av, pipefd);
		execute_cmd(av[index + 2], envp);
	}
}

void	pipex(int ac, char **av, char **envp)
{
	int		pipefd[2];
	int		i;
	int		status;
	int		exit_status;

	if (pipe(pipefd) == -1)
		error_handler(errno, "pipe failed", NULL);
	i = -1;
	while (ac - 3 > ++i)
		child_process(i, av, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	i = -1;
	while (ac - 3 > ++i)
	{
		wait(&status);
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

	if (argc != 5)
	{
		errno = EINVAL;
		perror("5 arguments needed (./pipex file1 cmd1 cmd2 file2)");
		exit(EXIT_FAILURE);
	}
	pipex(argc, argv, envp);
	outfile = open(argv[4], O_WRONLY);
	if (outfile < 0)
		exit(EXIT_FAILURE);
	close(outfile);
	exit(EXIT_SUCCESS);
}
