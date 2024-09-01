/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:25:52 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/31 23:45:50 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"


void	init_cmd(char *av2, char *av3, t_cmd *cmd)
{
	/// problème du split est quand il y a des arguments avec des guillemets  et des espaces entre
	cmd->argv1 = ft_split(av2, ' ');
	cmd->bin1 = ft_strjoin("/bin/", cmd->argv1[0]);
	cmd->argv1[0] = ft_strdup(cmd->bin1);
	cmd->result1 = NULL;
	cmd->argv2 = ft_split(av3, ' ');
	cmd->bin2 = ft_strjoin("/bin/", cmd->argv2[0]);
	cmd->argv2[0] = ft_strdup(cmd->bin2);
	cmd->result2 = NULL;
	return ;
}


void	get_file_info(char *file_name, t_file *file)
{
	file->name = ft_strdup(file_name);
	if (file->name == NULL)
		clean_exit(file, NULL);
	file->fd = open(file->name, O_RDONLY);
	if (file->fd == -1)
	{
		perror("Error at opening file 1");
		clean_exit(file, NULL);
	}
	file->content = NULL;
	if (fill_content(file) == false)
	{
		perror("Error at buffering content of file 1");
		clean_exit(file, NULL);
	}
	if (close(file->fd) == -1)
	{
		perror("Error initfile at closing file 1");
		clean_exit(file, NULL);
	}
	file->fd = -2;
}

void	init_file(char *file_name, t_file *file)
{
	if (access(file_name, R_OK) == 0)
		get_file_info(file_name, file);
	else
	{
		perror("Enable to access file 1");
		exit(EXIT_FAILURE);
	}
}

void	init_file_2(char *file_name, t_file *file)
{
	file->name = ft_strdup(file_name);
	if (file->name == NULL)
		clean_exit(file, NULL);
	file->content = NULL;
}
