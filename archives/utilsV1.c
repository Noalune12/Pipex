#include "pipex.h"

void	check_files(char *infile, char *outfile, t_pipex *pipex)
{
	pipex->infile = open(infile, O_RDONLY);
	if (pipex->infile < 0)
	{
		free(pipex);
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile < 0)
	{
		close(pipex->infile);
		free(pipex);
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
}

char	*error_handler(int errnum, char *message, t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->exec1)
		free(pipex->exec1);
	if (pipex->exec2)
		free(pipex->exec2);
	// if (pipex->full_path)
	// 	free(pipex->full_path);
	// if (pipex->path_env)
	// 	free(pipex->path_env);
	free(pipex);
	errno = errnum;
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_free_double(char **strs)
{
	size_t	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
		free (strs);
		strs = NULL;
	}
}
