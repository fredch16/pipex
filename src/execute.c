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
		half_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_array(paths);
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
	paths = ft_split(path_env, ':');
	if (!paths)
		error();
	return (access_full_path(paths, cmd));
}

int	execute_cmd(char *av, char **ev, int input_fd, int output_fd)
{
	char	*path;
	char	**argv;
	pid_t	pid;

	argv = ft_split(av, ' ');
	if (!argv)
		error();
	path = get_full_path(argv[0], ev);
	if (!path)
		return (ft_free_array(argv), print_err("Command not found, ", av, -1));
	pid = fork();
	if (pid == -1)
		return (ft_free_array(argv), free(path), error(), -1);
	if (pid == 0)
	{
		if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
			error();
		close(input_fd);
		close(output_fd);
		if (execve(path, argv, ev) == -1)
			return (perror("execve failed"), exit(EXIT_FAILURE), -1);
	}
	ft_free_array(argv);
	free(path);
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}
