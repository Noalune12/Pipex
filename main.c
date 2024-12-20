#include "pipex.h"

int	check_arg(char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("file in is not valid");
		exit(EXIT_FAILURE);
	}
	close(fd);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("file out is not valid");
		exit(EXIT_FAILURE);
	}
	close(fd);
	// if (access(av[2], X_OK) != 0)
	// {
	// 	perror("cmd1 is not valid");
	// 	exit(EXIT_FAILURE);
	// }
	// if (access(av[3], X_OK) != 0)
	// {
	// 	perror("cmd2 is not valid");
	// 	exit(EXIT_FAILURE);
	// }
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
	check_arg(argv);

}

// which wc = /usr/bin/wc
// Comment puis-je exécuter une commande dans le terminal à partir de mon programme C ?
