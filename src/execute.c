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
	char	*half_path;
	int		i;

	full_path = NULL;
	i = 0;
	while (paths[i])
	{
		// ft_printf("Path |%d|: %s\n", i, paths[i]);
		half_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(half_path, cmd);
		free(half_path);
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

int	execute_cmd(char *av, char **ev, int input_fd, int output_fd)
{
	char	*path;
	char	**argv;
	pid_t	pid;

	// Debugging: Print file descriptors
	fprintf(stderr, "execute_cmd: input_fd=%d, output_fd=%d\n", input_fd, output_fd);

	argv = ft_split(av, ' ');
	if (!argv)
		error();
	path = get_full_path(argv[0], ev);
	if (!path)
	{
		ft_free_array(argv);
		print_err("Command not found", av, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_free_array(argv);
		free(path);
		error();
	}
	if (pid == 0)
	{
		// In child process: redirect input/output
		if (dup2(input_fd, STDIN_FILENO) == -1 || dup2(output_fd, STDOUT_FILENO) == -1)
			error();
		// Close unused file descriptors
		close(input_fd);
		close(output_fd);
		// Execute the command
		if (execve(path, argv, ev) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	// In parent process: clean up
	ft_free_array(argv);
	free(path);
	// Parent does not close input_fd/output_fd here; caller handles it
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}