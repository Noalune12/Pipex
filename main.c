#include "pipex.h"

int	check_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening input file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	check_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error opening output file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}


//first cmd
//scd cmd
//find exec

void	pipex(char **argv, char **envp)
{
	int		infile;
	int		outfile;
	char	*cmd1;
	char	*cmd2;

	infile = check_infile(argv[1]);
	outfile = check_outfile(argv[4]);

	close(infile);
	close(outfile);
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
