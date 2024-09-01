/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:42:22 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/31 21:23:54 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	clean_exit(t_file *file1, t_file *file2)
{
	if (file1 && file1->name)
		free(file1->name);
	if (file2 && file2->name)
		free(file2->name);
	if (file1 && file1->content)
		free(file1->content);
	if (file2 && file2->content)
		free(file2->content);
	if (file1 && file1->fd > 0)
		if (close(file1->fd) == -1)
			perror("Error at closing file 1");
	if (file2 && file2->fd > 0)
		if (close(file2->fd) == -1)
			perror("Error at closing file 2");
	exit(EXIT_FAILURE);
}


void	error_mgmt(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
