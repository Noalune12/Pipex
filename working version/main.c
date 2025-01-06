#include "pipex.h"

void	open_dup(int index, char **av, int pipefd[2])
{
	int	infile;
	int	outfile;

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
	{
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
}

void	child_process(int index, char **av, char **envp, int pipefd[2])
{
	int pid;

	pid = fork();
	if (pid == -1) //close pipefd ??
		error_handler(errno, "fork failed", NULL);
	if (pid == 0)
	{
		// dup
		open_dup(index, av, pipefd);
		// get path
		execute_cmd(av[index + 2], envp);
	}
	// waitpid(pid, NULL, 0);
}

void	pipex(int ac, char **av, char **envp)
{
	int		pipefd[2]; // 0 - read, 1 - write
	int		i;
	int		status;
	int exit_status;

	if (pipe(pipefd) == -1)
		error_handler(errno, "pipe failed", NULL);
	i = 0;
	while (ac - 3 > i)
	{
		child_process(i, av, envp, pipefd);
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	i = 0;
	// while (ac - 3 > i)
	// {
	// 	// waitpid(-1, &status, 0);
	// 	// if ()
	// 	wait(&status);
	// 	printf("status = %d\n\n", status);
	// 	if (WIFEXITED(status))
	// 		exit_status = WEXITSTATUS(status);
	// 	// if (wait(&status) == -1)
	// 	// 	error_handler(errno, "wait failed", NULL);
	// 	// if (waitpid(-1, &status, 0) < 0)
	// 	// {
	// 	// 	if (WIFEXITED(status))
	// 	// 		exit_status = WEXITSTATUS(status);
	// 	// }
	// 	if (exit_status != 0)
	// 		exit(exit_status);
	// 	i++;
	// }
	// printf("exit status = %d\n\n", exit_status);
		// error_handler(0, "", NULL); //errno ??
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
	outfile = open(argv[4], O_WRONLY); //why not working with sleep inside pipex
	if (outfile < 0)
		exit(EXIT_FAILURE);
	close(outfile);
	exit(EXIT_SUCCESS);
}
