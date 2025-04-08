/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/08 14:02:11 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"

typedef	struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	*cmd;
}	t_cmd;

typedef struct s_data
{
	char	*infile_path;
	char	*outfile_path;
	char	**envp;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
}	t_data;

// Utility Functions

int	parse_input(t_data *data, int ac, char **av, char **ev);
// int	execute_cmd(char *cmd, char *file, char **ev);
int	execute_cmd(t_data *data, t_cmd *cmd, char *file);

#endif