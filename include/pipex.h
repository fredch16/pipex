/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:06:46 by fredchar          #+#    #+#             */
/*   Updated: 2025/04/06 17:28:43 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include "libft/libft.h"

#endif

typedef struct	s_data
{
	char	*infile_path;
	char	*outfile_path;
	char	*cmd1;
	char	*cmd2;
}	t_data;

// Utility Functions

int	parse_input(t_data *data, int ac, char **av);
int	execute_cmd(char *cmd, char *file, char **ev);