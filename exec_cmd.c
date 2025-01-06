/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:34:53 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/06 13:37:00 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_env_path(char **envp, char **cmds)
{
	char	*path_env;
	int		i;

	path_env = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = ft_strdup(envp[i] + 5);
			if (!path_env)
				error_handler(errno, "strdup failed", cmds);
			break ;
		}
		i++;
	}
	if (!path_env)
		error_handler(errno, "PATH not defined in the envp", cmds);
	return (path_env);
}

char	*join_full_path(char *path, char **cmds, char **paths)
{
	char	*dir;
	char	*full_path;

	dir = ft_strjoin(path, "/");
	if (!dir)
	{
		ft_free_double(paths);
		error_handler(ENOMEM, "Strjoin failed", cmds);
	}
	full_path = ft_strjoin(dir, cmds[0]);
	if (!full_path)
	{
		free(dir);
		ft_free_double(paths);
		error_handler(ENOMEM, "Strjoin failed", cmds);
	}
	free(dir);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_full_path(char **cmds, char *path_env)
{
	char	*full_path;
	char	**paths;
	size_t	i;

	paths = ft_split(path_env, ":");
	if (!paths)
		error_handler(errno, "Split failed", cmds);
	i = 0;
	while (paths[i])
	{
		full_path = join_full_path(paths[i], cmds, paths);
		if (full_path)
		{
			ft_free_double(paths);
			return (full_path);
		}
		i++;
	}
	ft_free_double(paths);
	free(full_path);
	return (NULL);
}

char	*find_exec_cmd(char **cmds, char **envp, int check)
{
	char	*full_path;
	char	*path_env;

	path_env = find_env_path(envp, cmds);
	full_path = find_full_path(cmds, path_env);
	free(path_env);
	if (!full_path)
	{
		if (check == 0)
			error_handler(errno, "cmd not found", cmds);
		ft_free_double(cmds);
		exit(127);
	}
	return (full_path);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**cmds;
	char	*exec;

	cmds = ft_split(cmd, " ");
	if (!cmds)
		error_handler(errno, "Split failed", NULL);
	if (!cmds[0])
		error_handler(errno, "Invalid cmd", cmds);
	exec = find_exec_cmd(cmds, envp, 0);
	if (execve(exec, cmds, envp) == -1)
	{
		free(exec);
		error_handler(errno, "exec cmd1 failed", cmds);
	}
	free(exec);
	ft_free_double(cmds);
}
