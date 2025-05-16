#include "minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->filename)
			free(redir->filename);
		free(redir);
		redir = temp;
	}
}

void	free_process(t_node *process)
{
	t_node	*temp;

	if (process)
	{
		while (process)
		{
			temp = process->next;
			if (process->args)
				ft_matrix_free((void ***)(&process->args));
			if (process->redir)
				free_redir(process->redir);
			free(process);
			process = temp;
		}
	}
}

void	free_mid_process(t_shell *shell)
{
	if (shell->process)
	{
		free_process(shell->process);
		shell->process = NULL;
	}
	if (shell->pid_nbr)
	{
		free(shell->pid_nbr);
		shell->pid_nbr = NULL;
	}
}

