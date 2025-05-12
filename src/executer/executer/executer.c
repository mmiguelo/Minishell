/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:41:08 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/12 11:21:12 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_process(t_shell *shell)
{
	t_node	*node;

	node = shell->process;
	int		fd[2];
	int		in_fd = 0;
	pid_t	pid;

	while (node)
	{
		if (node->next && pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0) // child process
		{
			if (in_fd != 0)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (node->next)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (!apply_redirections(node))
				exit(1); // erro ao aplicar redirecionamento
			execve(node->cmd, node->args, shell->envp);
			perror("execve");
			exit(1);
		}
		if (in_fd != 0)
			close(in_fd);
		if (node->next)
		{
			close(fd[1]);
			in_fd = fd[0];
		}
		node = node->next;
	}
	while (wait(&(shell->exit_status)) > 0)
		;
	shell->exit_status = WEXITSTATUS(shell->exit_status);
}

int	apply_redirections(t_node *node)
{
	t_redir	*r = node->redir;
	int		fd;

	while (r)
	{
		if (r->type == REDIR_OUT) // >
			fd = open(r->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == APPEND) // >>
			fd = open(r->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (r->type == REDIR_IN) // <
			fd = open(r->filename, O_RDONLY);
		else
		{
			r = r->next; // AQUI FICA O HEREDOC DO FRANCISCO
			continue ;
		}
		if (fd < 0)
			return (perror(r->filename), 0);
		if (r->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		r = r->next;
	}
	return (1);
}
