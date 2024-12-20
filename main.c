#include "pipex.h"

int	check_arg(int ac, char **av)
{
	(void)ac;
	(void)av;
	int	fd;

	fd = open(av[1], O_RDONLY);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// access(av[2], X_OK) != 0
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 5)
	{
		errno = EINVAL;
		perror("5 arguments needed (./pipex file1 cmd1 cmd2 file2)");
		exit(EXIT_FAILURE);
	}
	if (check_arg(argc, argv) == 1)
		exit(EXIT_FAILURE);
}
