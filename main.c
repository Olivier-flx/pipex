/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:56:08 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/31 23:50:08 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Votre programme sera exécuté comme suit :
./pipex file1 cmd1 cmd2 file2
Il doit prendre 4 arguments :
• file1 et file2 sont des noms de fichier.
• cmd1 et cmd2 sont des commandes shell avec leurs paramètres.
Votre programme doit se comporter exactement comme la commande shell suivante :
$> < file1 cmd1 | cmd2 > file2
*/

//	< file1   == envoyer contenu de file 1 sur stdin
//	cmd1 produit une sortie standard (stdout), qui sera ensuite utilisée
//		par le prochain processus dans la pipeline.
//	| prend stdout de cmd1 et la redirige vers sdtin qui sera utilisé par cmd2
//	> file2 == redirige et écrit la sortie standard (stdout) de cmd2 dans file2.
//		Si file2 n'existe pas, il sera créé. S'il existe déjà,
//		son contenu sera écrasé.

// commande de test < test_input grep "erreur" | sort >  test_output
// echo "couillon erreur zaza" | sed 's/erreur //'


// echo "couillon erreur zaza" | wc -w' >test.txt
	// remplie test.txt
// fhg | wc -w' >test.txt
	// se mets en attente de la suite de la commande avec >
// echo "couillon erreur zaza" | kuhggf > test.txt
	// stdout --> jhgf: command not found
	// créer le ficher test.txt mais le laisse vide


#include "./inc/pipex.h"

// int	main(int ac, char **av)
// {
// 	t_file	files1;
// 	t_file	files2;

// 	if (ac == 5 && *av[1] && *av[2] && *av[3] && *av[4])
// 	{
// 		init_file(*av[1], &files1);

// 		// open file 1
// 		// read file1
// 		// mettre le contenus dans un buffer
// 		// fermer file1
// 		// rediriger le contenu du fichier vers stdin (utiliser pipe() ? ou dup2()?)
// 		// execve(const char *pathname, char *const argv[], char *const envp[]); // pour lire les commandes
			// avant d'utiliser execve, il faut utiliser fork() car execve remplace l'execution en cours
			// donc l'execution du programme
			// fork returns an int. int id = fork(); -1 if error , 0 for the new process copy
			// pour eviter que le code 'sexecute deux fois, utiliser if(id ==0) {code 1} else {code 2}
			// if (id != 0) -> signifie qu c'est le main process
// 		// attendre que la commande s'execute avec execve
// 		// lire le premier output sur stdout (utilisation de pipe) et reutiliser execve,
// 		// attendre le résultat de execve
// 		// mettre le résultat de la seconde commande dans un buffer
/////////
// 		v1 // Utilliser Access() pour vérifier l'existence de file 2
// 			// existe pas -> créer le fichier avec execve(/bin/touch file2, NULL)
// 		v2// ouvrir le fichier file2
// 			// utiliser open(file, O_WRONLY | O_CREAT, S_IRWXU) // O_WRONLY | O_CREAT ==> bitwise or
//			//cela le créer s'il n'existe pas
/////////
// 		// ecrire le fichier file2
			// faire pointer stdout vers file2
				// int new_fd = dup2(fd_file2, STDOUT_FILENO)
					// va  dans un premier temps fermer stdout,
					// puis le reouvrir en le faisant pointer vers le fichier décrit par "fd file2"
					// il faut alos fermer le fd inutile avec close(fd_file2)
				// ft_printf("") vas alors écrire dans le file 2
			//write (fd file2 , buffer, buffer size);
// 		// fermer le fichier file2

// 	}
// 	return (EXIT_SUCCESS);
// }


////// Comment structurer le code

/// TODO => revoir le spit pour ignorer les espaces entre les guillemets

/* /////// PIPES STRUCTURE /////////////

	main -> read content  ===== stdin ===== cmd1  std out ===== stdin + cmd2 ====== output to file

	main process
		read content
				||
				||
				||
			child process cmd1
				||
				||
				||
			child process cmd2
		create file and write in it


*/

// TESTS /
int	main(int ac, char **av)
{
	t_file	file1;
	t_file	file2;
	t_cmd	cmd;

	if (ac == 5 && av[1] && av[1][0] && av[2] \
		&& av[2][0] && av[3] && av[3][0] && av[4] && av[4][0]) // ne pas oublier de changer ac ^^'
	{
		init_file(av[1], &file1);
		init_cmd(av[2], av[3], &cmd);
		init_file_2(av[4], &file2);
		fonction_redirect(&cmd, &file1, &file2);
		//redirect_content_to_stdin(&file1, av[2]);
		clean_exit(&file1, NULL); // return 1 so not good if everything's going well
	}
	else
		error_mgmt("Wrong arguments");

	return (EXIT_SUCCESS);
}
