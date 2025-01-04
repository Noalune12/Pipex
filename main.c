#include "pipex.h"

void	child_process(int index, char **av, char **envp, int pipefd[2])
{
	int pid;

	pid = fork();
	if (pid == -1) //close pipefd ??
		error_handler(errno, "fork failed", NULL);
	if (pid == 0)
	{
		// dup
		close(pipefd[0]);
		close(pipefd[1]);
		// get path
		execute_cmd(av[index + 2], envp);
	}
}

void	pipex(int ac, char **av, char **envp)
{
	int		pipefd[2]; // 0 - read, 1 - write
	int		i;

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
	while (ac - 3 > i)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		errno = EINVAL;
		perror("5 arguments needed (./pipex file1 cmd1 cmd2 file2)");
		exit(EXIT_FAILURE);
	}
	pipex(argc, argv, envp);
	exit(EXIT_SUCCESS);
}
