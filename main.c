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

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		errno = EINVAL;
		perror("5 arguments needed (./pipex file1 cmd1 cmd2 file2)");
		exit(EXIT_FAILURE);
	}
	pipex(argv, envp);
	exit(EXIT_SUCCESS);
}
