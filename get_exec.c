#include "pipex.h"

char	*find_path(char *cmd, char **envp, t_pipex *pipex)
{
	char	**env;

	env = envp;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			pipex->path_env = ft_strdup(*env + 5);
			if (!pipex->path_env)
				return (error_handler(ENOMEM, "strdup failed", pipex));
			break ;
		}
		env++;
	}
	if (!pipex->path_env)
		return (error_handler(EINVAL, "PATH not defined in the envp", pipex));
	return (pipex->path_env);
}

int	is_exec(char *path)
{
	return (access(path, X_OK) == 0);
}

// char	*concat_full_path(char *start, char *end, char *cmd, t_pipex *pipex)
// {
// 	int		len;
// 	char	*full_path;
// 	char	*dir;
// 	char	*tmp;

// 	len = end - start;
// 	dir = ft_substr(start, 0, len);
// 	if (!dir)
// 		return (error_handler(ENOMEM, "Substr failed", pipex));
// 	tmp = ft_strjoin(dir, "/");
// 	if (!tmp)
// 	{
// 		free(dir);
// 		return (error_handler(ENOMEM, "Strjoin failed", pipex));
// 	}
// 	full_path = ft_strjoin(tmp, cmd);
// 	if (!full_path)
// 	{
// 		free(dir);
// 		free(tmp);
// 		return (error_handler(ENOMEM, "Strjoin failed", pipex));
// 	}
// 	free(tmp);
// 	free(dir);
// 	if (is_exec(full_path))
// 		return (full_path);
// 	free(full_path);
// 	return (NULL);
// }

char	*join_full_path(char *path, char *cmd, t_pipex *pipex, char **paths)
{
	char	*dir;
	char	*full_path;

	dir = ft_strjoin(path, "/");
	if (!dir)
	{
		ft_free_double(paths);
		ft_free_double(pipex->args);
		error_handler(ENOMEM, "Strjoin failed", pipex);
	}
	full_path = ft_strjoin(dir, cmd);
	if (!full_path)
	{
		free(dir);
		ft_free_double(paths);
		ft_free_double(pipex->args);
		return (error_handler(ENOMEM, "Strjoin failed", pipex));
	}
	free(dir);
	if (is_exec(full_path))
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_full_path(char *path_env, t_pipex *pipex)
{
	char	*full_path;
	char	**paths;
	size_t	i;

	paths = ft_split(path_env, ":");
	if (!paths)
		error_handler(ENOMEM, "Split failed", pipex);
	i = 0;
	while (paths[i])
	{
		full_path = join_full_path(paths[i], pipex->args[0], pipex, paths);
			if (full_path)
			{
				ft_free_double(paths);
				return (full_path);
			}
		i++;
	}
	ft_free_double(paths);
	return (NULL);
	// char	*start;
	// char	*end;

	// start = path_env;
	// end = ft_strchr(start, ':');
	// while (end)
	// {
	// 	full_path = concat_full_path(start, end, cmd, pipex);
	// 	if (full_path)
	// 		return (full_path);
	// 	start = end + 1;
	// 	end = ft_strchr(start, ':');
	// }
	// full_path = concat_full_path(start, end, cmd, pipex);
	// if (full_path)
	// 	return (full_path);
	// return (NULL);
}

char	*find_exec_cmd(char *cmd, char **envp, t_pipex *pipex)
{
	char	*full_path;

	find_path(cmd, envp, pipex);
	if (!pipex->path_env)
		return (NULL);
	printf("Path env = %s\n\n", pipex->path_env);
	pipex->args = ft_split(cmd, " ");
	if (!pipex->args)
		error_handler(ENOMEM, "Split failed", pipex);
	full_path = find_full_path(pipex->path_env, pipex);
	free(pipex->path_env);
	ft_free_double(pipex->args);
	return (full_path);
}
