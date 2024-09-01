/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:58:12 by ofilloux          #+#    #+#             */
/*   Updated: 2024/09/01 00:09:02 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"


void	run_main_process(void)
{
	printf("hola run_main\n");
}

void	redirect_to_cmd2(int *fd_arr2)
{
	char bin[] = "/bin/sort";
	char *arg_v[] = {"/bin/sort", NULL};
	close(fd_arr2[1]);
	execve(bin, arg_v, NULL);

}

// https://www.youtube.com/watch?v=Mqb2dVRe0uo
// void	run_execve(char *cmd, int *fd_arr)
// {
// 	char	**arg_v;
// 	char	*bin;
// 	int		fd_arr2[2];
// 	int		pid2;

// 	close(fd_arr[1]);
// 	// close write end of the child process
// 	dup2(fd_arr[0], STDIN_FILENO);
// 	close(fd_arr[0]);
// 	arg_v = ft_split(cmd, ' ');
// 	bin = ft_strjoin("/bin/", arg_v[0]);
// 	arg_v[0] = ft_strdup(bin);
// 	if (pipe(fd_arr2) == -1)
// 		perror("error in pipe for redirecting stdout to stdin for cmd2");
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		perror("error in 2nd forking");
// 	if (pid2 == 0)
// 	{ /////// PARTIE à revoir
// 		close(fd_arr2[0]);
// 		dup2(STDOUT_FILENO, STDIN_FILENO);
// 		execve(bin, arg_v, NULL);
// 		close(fd_arr2[1]); // useless parce qu'après exec rien n'est lu
// 	}
// 	else
// 		redirect_to_cmd2(fd_arr2);
// }

// void	redirect_content_to_stdin(t_file *file, char *cmd1)
// {
// 	int	fd_arr[2];
// 	int	pid;

// 	if (pipe(fd_arr) == -1)
// 		perror("error in pipe");// améliorer la gestion de l'erreur et la sortie du programme
// 	pid = fork(); // du coup 4 fd à close
// 	if (pid == -1)
// 		perror("error in forking"); // améliorer la gestion de l'erreur et la sortie du programme
// 	if (pid == 0)
// 		run_execve(cmd1, fd_arr);
// 	else
// 	{
// 		close(fd_arr[0]);
// 		if (write(fd_arr[1], file->content, ft_strlen(file->content)) == -1 )
// 			perror("in writng fo 1st command");
// 		close(fd_arr[1]);
// 		wait(NULL);
// 		printf("hola desde redirect.c\n");
// 		run_main_process();
// 	}
// }


// pipe(fd[1]) = write end  ; pipe(fd[0]) = Read end  ;

void	run_cmd1(int *fd, t_cmd *cmd, t_file *file1)
{
	int	pid3;
	int	fd_arr2[2];

	if (pipe(fd_arr2) == -1)
		error_mgmt("error in pipe : fonction_redirect <- redirect.c");
	pid3 = fork();
	if (pid3 == -1)
		error_mgmt("error in fork in run_cmd1 in redirects.c");
	if (pid3 == 0)
	{
		close(fd_arr2[0]);
		printf("desde write cmd (pid3)\n");
		//dup2(fd_arr2[1], STDIN_FILENO);
		if (write(fd_arr2[1], file1->content, ft_strlen(file1->content)) == -1)
			error_mgmt("error in write in run_cmd1 in redirects.c");
		close(fd_arr2[1]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid3, NULL, 0);

	printf("desde run cmd1\n");
	close(fd_arr2[1]);
	dup2(fd_arr2[0], STDIN_FILENO);
	close(fd_arr2[0]);

	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execve(cmd->bin1, cmd->argv1, NULL);
	exit(EXIT_FAILURE); // in case execve doesn't find the file or else;
}

void	run_cmd2(int *fd, t_cmd *cmd, t_file *file2)
{
	// int pid4;
	// int	fd_arr3[2];

	file2->fd = open(file2->name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if (file2->fd < 0)
		error_mgmt("error at opening file2");
	dup2(file2->fd, STDOUT_FILENO);
	// pid4 = fork();
	// if (pid4 == -1)
	// 	error_mgmt("error in fork in run_cmd1 in redirects.c");
	//// forker pour pouvoir fermer file2->fd (close() après execve.
	// if (pid4 == 0)
	// {
		printf("desde run cmd2\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(cmd->bin2, cmd->argv2, NULL);
		error_mgmt("execve failed in run_cmd2");
	// }
	// waitpid(pid4, NULL, 0);
	/// se démerder pour écrire dans le file2.
	// fermer file2
	exit(EXIT_SUCCESS);
}

// n'est il pas intéressant de faire un dup de stdin avant de la dup2, car dup2 ferme le second argument ?
// et il faut garder stdin ouvert pour la second pipe entre cmd1 et cmd2

void	fonction_redirect(t_cmd *cmd, t_file *file1, t_file *file2)
{
	int	fd_arr[2];
	int	pid1;
	int	pid2;

	if (pipe(fd_arr) == -1)
		error_mgmt("error in pipe : fonction_redirect <- redirect.c");
	pid1 = fork(); // du coup 4 fd à close
	if (pid1 == -1)
		error_mgmt("error in forking1: fonction_redirect <- redirect.c");
	if (pid1 == 0)
		run_cmd1(fd_arr, cmd, file1); // cmd 1;
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 == -1)
		error_mgmt("error in forking2: fonction_redirect <- redirect.c");

	if (pid2 == 0)
		run_cmd2(fd_arr, cmd, file2); // cmd 1;
	waitpid(pid2, NULL, 0);
	close(fd_arr[0]);
	close(fd_arr[0]);
	// normalement à partir d'ici, tout est ok et je peux clore tranquillou le programme
}


// void	redirect_content_to_stdin(t_file *file, char *cmd1)
// {
// 	int	fd_arr[2];
// 	int	pid;

// 	if (pipe(fd_arr) == -1)
// 		perror("error in pipe");// améliorer la gestion de l'erreur et la sortie du programme
// 	pid = fork(); // du coup 4 fd à close
// 	if (pid == -1)
// 		perror("error in forking"); // améliorer la gestion de l'erreur et la sortie du programme
// 	if (pid == 0)
// 		run_execve(cmd1, fd_arr);
// 	else
// 	{
// 		close(fd_arr[0]);
// 		if (write(fd_arr[1], file->content, ft_strlen(file->content)) == -1 )
// 			perror("in writng fo 1st command");
// 		close(fd_arr[1]);
// 		wait(NULL);
// 		printf("hola desde redirect.c\n");
// 		run_main_process();
// 	}
// }


////// incorrecte ///////
// void	redirect_content_to_stdin(t_file *file)
// {
// 	if (write(STDIN_FILENO, file->content, ft_strlen(file->content)) == -1)
// 	{
// 		perror("Error at writing in stdin");
// 		clean_exit(file, NULL);
// 	}
// }
