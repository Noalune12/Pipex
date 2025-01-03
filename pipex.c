#include "pipex.h"

void	create_pipes(t_pipex *pipex, char **argv)
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
		printf("%d\n\n", pipex->outfile);
		int fd2 = dup2(pipex->outfile, STDOUT_FILENO); //everything that are written in stdout will be redirected to the file infile
		printf("%d\n\n", fd2);
		close(pipefd[0]);
		close(pipefd[1]);
	}
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
