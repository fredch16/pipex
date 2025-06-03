/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/06/03 16:17:20 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_data *data, char *argv, int is_last)
{
	int		fd[2];
	pid_t	pid;

	if (!is_last && pipe(fd) == -1)
		error();
	if (is_last)
		data->output_fd = data->outfile_fd;
	else
		data->output_fd = fd[1];
	pid = execute_cmd(data, argv);
	if (pid > 0)
		data->pids[data->cmd_idx - data->first_cmd] = pid;
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

void	handle_heredoc(t_data *data, char *li)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error();
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
		{
			close(fd[1]);
			close(fd[0]);
			error();
		}
		if (!ft_strncmp(line, li, ft_strlen(li)) && line[ft_strlen(li)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	data->input_fd = fd[0];
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	if (argc < 5)
		return (usage(), -1);
	data.envp = envp;
	data.cmd_count = argc - 3;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		data.outfile_fd = open_file(argv[argc - 1], 0);
		handle_heredoc(&data, argv[2]);
		data.cmd_idx = 3;
		data.first_cmd = 3;
	}
	else
	{
		data.cmd_idx = 2;
		data.first_cmd = 2;
		data.outfile_fd = open_file(argv[argc - 1], 1);
		data.infile_fd = open_file(argv[1], 2);
		data.input_fd = data.infile_fd;
	}
	data.pids = (pid_t *)malloc(sizeof(pid_t) * (data.cmd_count));
	if (!data.pids)
		error();
	while (data.cmd_idx < argc - 2)
	{
		child_process(&data, argv[data.cmd_idx], 0);
		data.cmd_idx++;
	}
	child_process(&data, argv[argc - 2], 1);
	i = 0;
	while (i < data.cmd_count)
	{
		if(data.pids[i] > 0)
			waitpid(data.pids[i], NULL, 0);
		i++;
	}
	free(data.pids);
	close(data.input_fd);
}
