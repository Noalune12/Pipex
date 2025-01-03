#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	*exec1;
	char	*exec2;
	char	**args;
	// char	*full_path;
	char	*path_env;
}	t_pipex;

void	check_files(char *infile, char *outfile, t_pipex *pipex);
char	*find_exec_cmd(char *cmd, char **envp, t_pipex *pipex);
char	*error_handler(int errnum, char *message, t_pipex *pipex);
void	ft_free_double(char **strs);

#endif
