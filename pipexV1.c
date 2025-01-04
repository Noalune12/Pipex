#include "pipex.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->exec1 = NULL;
	pipex->exec2 = NULL;
	// pipex->full_path = NULL;
	pipex->path_env = NULL;
}

void	free_pipex(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->exec1);
	free(pipex->exec2);
	free(pipex);
}

void	pipex(char **argv, char **envp)
{
	t_pipex	*pipex;
	char	*exec;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error_handler(ENOMEM, "alloc pipex failed", pipex);
	check_files(argv[1], argv[4], pipex);
	init_pipex(pipex);
	exec = find_exec_cmd(argv[2], envp, pipex);
	if (!exec)
		error_handler(EINVAL, "cmd1 not found", pipex);
	pipex->exec1 = ft_strdup(exec);
	// printf("exec1 = %s\n", pipex->exec1);
	free(exec);
	exec = find_exec_cmd(argv[3], envp, pipex);
	if (!exec)
		error_handler(EINVAL, "cmd2 not found", pipex);
	pipex->exec2 = ft_strdup(exec);
	free(exec);
	create_pipes(pipex, argv, envp);
	// printf("exec2 = %s\n", pipex->exec2);
	free_pipex(pipex);
}

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
