#include "pipex.h"

void	execute_cmd1(t_pipex *pipex, char *cmd, char **envp)
{
	pipex->args = ft_split(cmd, " ");
	if (!pipex->args)
		error_handler(ENOMEM, "Split failed", pipex);
	if (execve(pipex->exec1, pipex->args, envp) == -1)
	{
		ft_free_double(pipex->args);
		error_handler(errno, "exec cmd1 failed", pipex);
	}
	ft_free_double(pipex->args);
}

void	execute_cmd2(t_pipex *pipex, char *cmd, char **envp)
{
	pipex->args = ft_split(cmd, " ");
	if (!pipex->args)
		error_handler(ENOMEM, "Split failed", pipex);
	if (execve(pipex->exec2, pipex->args, envp) == -1)
	{
		ft_free_double(pipex->args);
		error_handler(errno, "exec cmd2 failed", pipex);
	}
	ft_free_double(pipex->args);
}

void	create_pipes(t_pipex *pipex, char **argv, char **envp)
{
	int		pipefd[2]; // 0 - read, 1 - write
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		error_handler(EFAULT, "pipe failed", pipex); //errno ??
	pid1 = fork();
	if (pid1 == -1)
		error_handler(errno, "fork failed", pipex);
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipex->infile, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_cmd1(pipex, argv[2], envp);
		close(pipefd[1]);
	}
	pid2 = fork();
	if (pid2 == -1)
		error_handler(errno, "fork failed", pipex);
	if (pid2 == 0)
	{
		close(pipefd[1]);
		dup2(pipex->outfile, STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		execute_cmd2(pipex, argv[3], envp);
		close(pipefd[0]);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	// if (pid1 == 0) //we are in child process
	// 	printf("Hello from the chil process %d\n\n", pid1);
	// else
	// {
	// 	printf("Hello from the main process\n");
	// }
	// int n;
	// if (pid1 == 0)
	// 	n = 1;
	// else
	// 	n = 6;
	// if (pid1 != 0)
	// 	wait(NULL);
	// int i = n;
	// while (i < n + 5)
	// {
	// 	printf("%d ", i);
	// 	i++;
	// }
}
