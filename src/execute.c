/* ************************************************************************** */
/*			                                                                */
/*			                                            :::      ::::::::   */
/*   execute.c			                              :+:      :+:    :+:   */
/*			                                        +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.	+#+  +:+	   +#+	    */
/*			                                    +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:16:14 by fredchar		  #+#	#+#             */
/*   Updated: 2025/04/30 11:18:14 by fredchar		 ###   ########.fr	   */
/*			                                                                */
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
		// ft_printf("Path |%d|: %s\n", i, paths[i]);
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		// ft_printf("Full |%d|: %s\n", i, full_path);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_array(paths); // Free the split array
			// printf("about to return |%s|\n", full_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_array(paths);
	return (NULL);
}

char	*get_full_path(char *cmd, char **ev)
{
	char	*path_env;
	char	**paths;
	int		i;

	i = 0;
	path_env = NULL;
	paths = NULL;
	// fprintf(stderr, "ENVPDATA is |%s|\n", ev[0]);
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
		{
			path_env = ev[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
	{
		fprintf(stderr, "Error finding environment paths");
		return (NULL);
	}
	// Split the PATH variable into directories
	paths = ft_split(path_env, ':');
	if (!paths)
	{
		// fprintf(stderr, "WEEWEEEWEE\n");
		error();
	}
	// Search for the command in each directory
	// char *full_path = access_full_path(paths, cmd);
	// printf("returned full path is |%s|\n", full_path);
	return (access_full_path(paths, cmd));
}

// example of argv in this case would be "/bin/cat", "filename.txt", NULL

int execute_cmd(char *av, char **ev)
{
	char	*path;
	char	**argv;

	argv = ft_split(av, ' ');
	// 1. Get full command path (e.g., "/bin/cat")
	path = get_full_path(argv[0], ev);
	if (!path)
		return(ft_printf("Command not found: %s\n", av),  EXIT_FAILURE);
	// ft_printf("Path that was returned is |%s|\n", path);

	if (execve(path, argv, ev) == -1)
		return(perror("execve failed"), EXIT_FAILURE);
	return (1);
}