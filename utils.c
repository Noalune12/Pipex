#include "pipex.h"

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

int	error_handler(int errnum, char *message, char **strs)
{
	if (strs)
		ft_free_double(strs);
	errno = errnum;
	perror(message);
	exit(EXIT_FAILURE);
}

// char	*error_handler_NULL(int errnum, char *message)
// {
// 	errno = errnum;
// 	perror(message);
// 	return (NULL);
// }
