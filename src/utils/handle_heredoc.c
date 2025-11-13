/**
 * @file handle_heredoc.c
 * @brief Heredoc input redirection implementation
 * 
 * @author Lilith Estévez Boeta y Begoña Varea Kuhn
 * @date 2025-09-21
 */

#include "minishell.h"

/**
 * @brief Writes line to pipe and frees it
 * 
 * @details Helper function that writes a heredoc line to the pipe
 * write end, appends newline, and frees the line buffer.
 * 
 * @ingroup utils_module
 * 
 * @param[in] pipefd Pipe file descriptors
 * @param[in] line Line to write (will be freed)
 */
static void	write_and_free(int *pipefd, char *line)
{
	write(pipefd[1], line, str_len(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

/**
 * @brief Closes pipe write end and waits for child process
 * 
 * @details Helper function that closes the write end of the heredoc
 * pipe and waits for the child process to complete.
 * 
 * @ingroup utils_module
 * 
 * @param[in] pipefd Pipe file descriptors
 * @param[in] pid Child process ID
 * @param[out] status Pointer to store exit status
 */
static void	close_and_waitpid(int *pipefd, int pid, int *status)
{
	close(pipefd[1]);
	waitpid(pid, status, 0);
}

/**
 * @brief Reads heredoc input lines until delimiter
 * 
 * @details Reads lines from stdin using readline until the EOF
 * delimiter is encountered. Writes each line to the pipe. Handles
 * Ctrl-D (NULL input) by exiting with status 130.
 * 
 * @ingroup utils_module
 * 
 * @param[in] pipefd Pipe file descriptors
 * @param[in,out] cmd Command structure with heredoc delimiter
 */
static void	read_heredoc_lines(int *pipefd, t_command *cmd)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line)
		{
			free(cmd->heredoc_eof);
			close(pipefd[1]);
			exit(130);
		}
		if (str_compare_all(line, cmd->heredoc_eof))
		{
			free(cmd->heredoc_eof);
			free(line);
			break ;
		}
		write_and_free(pipefd, line);
	}
}

/**
 * @brief Executes heredoc reading in forked process
 * 
 * @details Forks a child process to read heredoc input. Child process
 * restores default SIGINT behavior, closes pipe read end, and reads
 * lines until delimiter.
 * 
 * @ingroup utils_module
 * 
 * @param[in] pid Process ID (0 in child)
 * @param[in] pipefd Pipe file descriptors
 * @param[in,out] cmd Command structure with heredoc delimiter
 */
static void	throw_heredoc(int pid, int *pipefd, t_command *cmd)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		read_heredoc_lines(pipefd, cmd);
		close(pipefd[1]);
		exit(0);
	}
}

/**
 * @brief Sets up heredoc input redirection
 * 
 * @details Creates a pipe and forks a child process to read heredoc
 * input lines until the EOF delimiter. The read end of the pipe becomes
 * the command's input file descriptor. Handles signal interruption and
 * process cleanup.
 * 
 * @ingroup utils_module
 * 
 * @param[in,out] cmd Command structure with heredoc delimiter, updated
 * with infile descriptor
 */
void	handle_heredoc(t_command *cmd)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (!cmd->heredoc_eof)
		return ;
	if (pipe(pipefd) == -1)
		return ;
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	throw_heredoc(pid, pipefd, cmd);
	close_and_waitpid(pipefd, pid, &status);
	cmd->infile = pipefd[0];
}
