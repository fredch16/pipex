/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/05/02 15:52:39 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>


typedef struct s_data
{
	int		ac;
	char	**envp;
	char	**av;
	int		infile_fd;
	int		outfile_fd;
	int		*pipes;
	int		*pids;
	int		child_id;
	int		cmd_count;
	int		exit_code;
	char	*cmd;

	char	*infile_path;
	char	*outfile_path;
}	t_data;

// parsing.c

int	parse_input(t_data *data, int ac, char **av, char **ev);

// execute.c

int	execute_cmd(char *av, char **ev, int input_fd, int output_fd);

// utils.c

void	usage(void);
void	error(void);
int		open_file(char *av, int i);
int		print_err(char *msg1, char *msg2, int errstate);

void	free_up(t_data *data);
#endif