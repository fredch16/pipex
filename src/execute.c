/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:16:14 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/08 14:02:39 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*access_full_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		printf("Path |%d|: %s\n", i, paths[i]);
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		printf("Full |%d|: %s\n", i, full_path);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_array(paths); // Free the split array
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

char	*get_full_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	int		i;

	// Get the PATH environment variable
	i = 0;
	path_env = NULL;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	// Split the PATH variable into directories
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);

	// Search for the command in each directory
	return (access_full_path(paths, cmd));
}

// example of argv in this case would be "/bin/cat", "filename.txt", NULL
int	execute_cmd(t_data *data, t_cmd *cmd, char *file)
{
	char	*argv[3];
	char	*full_path;

	// Resolve the full path of the command
	full_path = get_full_path(cmd->cmd, data->envp);
	if (!full_path)
	{
		ft_printf("Command not found: %s\n", cmd);
		exit(EXIT_FAILURE);
	}
	// Prepare arguments for the command
	argv[0] = cmd->cmd;   // Command (e.g., "cat")
	argv[1] = file;  // File to pass as an argument
	argv[2] = NULL;  // Null-terminated array
	// Execute the command
	if (execve(full_path, argv, data->envp) == -1)
	{
		perror("Error executing command");
		free(full_path);
		exit(EXIT_FAILURE);
	}
	free(full_path);
	return (0); // This line will never be reached if execve succeeds
}