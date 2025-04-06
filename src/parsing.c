/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:39:04 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/06 16:23:52 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parse_input(t_data *data, int ac, char **av)
{
	if (ac != 5)
		return (-1);
	data->infile_path = av[1];
	data->cmd1 = av[2];
	data->cmd2 = av[3];
	data->outfile_path = av[4];
	return (0);
}