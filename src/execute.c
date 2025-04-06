/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:16:14 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/06 18:01:53 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*get_full_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	// Get the PATH environment variable
	path_env = NULL;
	int j = 0;
	while (envp[j++])
		printf("%s\n", envp[j]);
	printf("============================= END OF ENVP ===========================\n\n");
	for (i = 0; envp[i]; i++)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
	}
	ft_printf("Full time path is %s\n", path_env);
	cmd += 0;
	full_path = NULL;
	paths = NULL;
	return (NULL);
	// if (!path_env)
	// 	return (NULL);

	// // Split the PATH variable into directories
	// paths = ft_split(path_env, ':');
	// if (!paths)
	// 	return (NULL);

	// // Search for the command in each directory
	// i = 0;
	// while (paths[i])
	// {
	// 	full_path = ft_strjoin(paths[i], "/");
	// 	full_path = ft_strjoin(full_path, cmd);
	// 	if (access(full_path, X_OK) == 0)
	// 	{
	// 		ft_free_split(paths); // Free the split array
	// 		return (full_path);
	// 	}
	// 	free(full_path);
	// 	i++;
	// }

	// ft_free_split(paths); // Free the split array
	// return (NULL);
}

int	execute_cmd(char *cmd, char *file, char **envp)
{
	char	*argv[3];
	char	*full_path;

	// Resolve the full path of the command
	full_path = get_full_path(cmd, envp);
	if (!full_path)
	{
		ft_printf("Command not found: %s\n", cmd);
		exit(EXIT_FAILURE);
	}

	// Prepare arguments for the command
	argv[0] = cmd;   // Command (e.g., "cat")
	argv[1] = file;  // File to pass as an argument
	argv[2] = NULL;  // Null-terminated array

	// Execute the command
	if (execve(full_path, argv, envp) == -1)
	{
		perror("Error executing command");
		free(full_path);
		exit(EXIT_FAILURE);
	}
	free(full_path);
	return (0); // This line will never be reached if execve succeeds
}