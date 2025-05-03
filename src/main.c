/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/03 14:03:28 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// ./pipex file1 cmd1 cmd2 file2

void	child_process(t_data *data, char *argv, int is_last)
{
	int		fd[2];

	if (!is_last && pipe(fd) == -1)
		error();
	if (is_last)
		data->output_fd = data->outfile_fd;
	else
		data->output_fd = fd[1];
	execute_cmd(data, argv);
	if (!is_last)
	{
		close(fd[1]);
		close(data->input_fd);
		data->input_fd = fd[0];
	}
	else
	{
		close(data->output_fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;

	if (argc < 5)
		return (usage(), -1);
	i = 2;
	data.envp = envp;
	data.outfile_fd = open_file(argv[argc - 1], 1);
	data.infile_fd = open_file(argv[1], 2);
	data.input_fd = data.infile_fd;
	while (i < argc - 2)
	{
		child_process(&data, argv[i], 0);
		i++;
	}
	child_process(&data, argv[argc - 2], 1);
	close(data.outfile_fd);
}
