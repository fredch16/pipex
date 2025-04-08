/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:22 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/08 14:01:52 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// ./pipex file1 cmd1 cmd2 file2

int main(int ac, char **av, char **ev)
{
	t_data	data;
	if (parse_input(&data, ac, av, ev) == -1)
	// 	ft_printf("Bye bye\n");
	if (ac != 3)
	{
		ft_printf("Usage: %s <command> <file>\n", av[0]);
		return (-1);
	}

	// Execute the command with the file as an argument
	execute_cmd(&data, data.cmd1, av[1]);

	return (EXIT_SUCCESS);
}