/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/02 17:32:49 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// ./pipex file1 cmd1 cmd2 file2

void	child_process(char *argv, char **envp, int *input_fd, int is_last, int fileout)
{
	int		fd[2];
	int		output_fd;

	if (!is_last && pipe(fd) == -1)
		error();
	if (is_last)
		output_fd = fileout;
	else
		output_fd = fd[1];
	execute_cmd(argv, envp, *input_fd, output_fd);
	if (!is_last)
	{
		close(fd[1]);
		close(*input_fd);
		*input_fd = fd[0];
	}
	else
	{
		close(output_fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;
	int	input_fd;

	if (argc < 5)
		return (usage(), -1);
	i = 2;
	fileout = open_file(argv[argc - 1], 1);
	filein = open_file(argv[1], 2);
	input_fd = filein;
	while (i < argc - 2)
	{
		child_process(argv[i], envp, &input_fd, 0, fileout);
		i++;
	}
	child_process(argv[argc - 2], envp, &input_fd, 1, fileout);
	close(fileout);
}