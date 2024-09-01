/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:56:28 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/31 23:48:19 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> //EXIT_SUCCESS , malloc, etc
# include <sys/types.h> // open
# include <sys/stat.h> // open
# include <fcntl.h> // open()
# include <unistd.h> //close(), execve(), fork()
# include <errno.h> // errno
# include <stdio.h> // printf
# include <stdbool.h> //bool
 # include <sys/types.h> // wait();
# include <sys/wait.h> // wait();

# define ERROR_FILE_NAME "File name error"
# define BUF_SIZE 4

typedef struct s_files
{
	char	*name;
	int		fd;
	char	*content;
}	t_file;

typedef struct s_cmd
{
	char	*bin1;
	char	**argv1;
	char	*result1;
	char	*bin2;
	char	**argv2;
	char	*result2;
}	t_cmd;


typedef void	(*t_run_command)(char *cmd1);

/// TEST
void	fonction_redirect(t_cmd *cmd, t_file *file1, t_file *file2);

void	clean_exit(t_file *file1, t_file *file2);
void	init_file(char *file_name, t_file *file);
void	init_file_2(char *file_name, t_file *file);
void	init_cmd(char *av2, char *av3, t_cmd *cmd);
bool	fill_content(t_file *file);
void	redirect_content_to_stdin(t_file *file, char *av);

/////// utils
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	error_mgmt(char *msg);

#endif




/*
FONCTIONS AUTORISÉES
• open, close, read, write,
malloc, free, exit,ft_printf et tout équivalent que VOUS avez codé

perror => void perror(const char *s) => message d'erreur sur stderr
	//ex perror("Erreur lors de l'ouverture du fichier")

strerror => char *strerror(int errnum)
	//Retourne une string décrivant le code d'erreur spécifié par errnum.
	//Similaire à perror, mais ne produit pas de sortie directe sur stderr.
	//ex printf("Erreur: %s\n", strerror(errnum));

access => int access(const char *pathname, int mode)
	//Vérifie l'existence d'un fichier ou la capacité d'accès à un fichier
	//(lecture, écriture, exécution)
	//selon le mode spécifié (R_OK, W_OK, X_OK, F_OK)
	//if (access("monfichier.txt", R_OK) == 0) {
		printf("Le fichier est accessible en lecture.\n");
	} else {
		perror("Erreur d'accès au fichier");
	}

dup => int dup(int oldfd)
	// Duplique le descripteur de fichier oldfd et retourne
	// un nouveau descripteur de fichier qui pointe vers le même fichier.
	// Utile pour rediriger les entrées/sorties
	// ex : int fd = open("output.txt", O_WRONLY);
	//	int newfd = dup(fd);  // newfd est maintenant une copie de fd

dup2 => int dup2(int oldfd, int newfd)
	//Duplique oldfd dans newfd. Si newfd est déjà ouvert, il est d'abord fermé.
	//Cela permet de rediriger un descripteur de fichier spécifique.
	//Utilisation : Principalement pour rediriger stdin, stdout, ou stderr.

execve => int execve(const char *pathname, char *const argv[], char *const envp[]);
	// Remplace le processus en cours par un nouveau processus
	// en exécutant le fichier spécifié par pathname.
	// Ne retourne jamais si l'appel réussit,
	// car le processus appelant est remplacé
	// Utilisation : Pour lancer un programme externe avec des arguments
	//				et un environnement spécifiques.
	// ex : char *args[] = {"/bin/ls", "-l", NULL};
			execve("/bin/ls", args, NULL);

fork => pid_t fork(void);
	//Crée un nouveau processus (fils) en dupliquant le processus appelant (parent).
	// Retourne 0 au processus fils et le PID du fils au parent.
	// En cas d'erreur, retourne -1.
	// Utilisation : Pour créer des processus fils, souvent utilisé avec exec
	// 				pour exécuter des commandes dans un nouveau processus.
	//exemple :  pid_t pid = fork();
	//			if (pid == 0) {
	// 			printf("Je suis le processus fils.\n");
	//			} else if (pid > 0) {
	//			printf("Je suis le processus parent.\n");
	//			}

pipe => int pipe(int pipefd[2])
	// Crée un canal unidirectionnel (pipe) utilisé pour
	// la communication inter-processus (IPC). (après les fork())
	// pipefd[0] est le descripteur de fichier de lecture et
	// pipefd[1] est le descripteur de fichier d'écriture.
	// int pipefd[2];
	//	pipe(pipefd);  // Crée un pipe
	// pipefd[0] pour lecture, pipefd[1] pour écriture

unlink => int unlink(const char *pathname)
	// Supprime un nom de fichier du système de fichiers.
	// Si c'est le dernier lien vers le fichier
	// et qu'aucun processus ne l'a ouvert, le fichier est supprimé.

wait => pid_t wait(int *status);
	//Bloque le processus parent jusqu'à ce qu'un processus fils se termine.
	//Retourne le PID du processus fils terminé et renseigne le statut de terminaison dans status.
	// Utilisation : Pour attendre la fin des processus fils.
	//exemple : int status;
	//			pid_t pid = wait(&status);
	// 			printf("Processus fils %d terminé avec le code de statut %d\n", pid, status);

waitpid => pid_t waitpid(pid_t pid, int *status, int options);
	// Similaire à wait, mais permet de spécifier le PID du processus fils à attendre
	// et d'utiliser des options pour contrôler le comportement d'attente.
	// Utilisation : Plus flexible que wait pour gérer la terminaison des processus fils.
	//		exemple : int status;
	//		pid_t pid = waitpid(-1, &status, 0);  // Attend n'importe quel processus fils

*/
