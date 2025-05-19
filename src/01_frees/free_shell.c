#include "minishell.h"

void	free_loop(t_shell *shell)
{
	free_tokens(&shell->token_list);
	free_process(&shell->process);
	free_ref(&shell->input);
}

// free tokens
void	free_tokens(t_token **token)
{
	t_token	*temp;

	if (!token || !(*token))
		return ;
	while (*token != NULL)
	{
		temp = (*token)->next;
		free((*token)->token);
		free(*token);
		*token = temp;
	}
	(*token) = NULL;
}

void	clean_heredoc(t_hd **hd)
{
	if (!hd || !(*hd))
		return ;
	unlink((*hd)->hd_path);
	free_ref(&(*hd)->hd_path);
	free_ref(&(*hd)->delimiter);
	free((*hd));
	(*hd) = NULL;
}

void	free_redir(t_redir **redir)
{
	t_redir	*temp;

	if (!redir || !(*redir))
		return ;
	while (*redir)
	{
		temp = (*redir)->next;
		if ((*redir)->filename)
			free((*redir)->filename);
		if ((*redir)->heredoc)
			clean_heredoc(&(*redir)->heredoc);
		free(*redir);
		*redir = temp;
	}
	(*redir) = NULL;
}

void	free_process(t_node **process)
{
	t_node	*temp;

	if (!process || !(*process))
		return ;
	while (*process)
	{
		temp = (*process)->next;
		if ((*process)->args)
			ft_matrix_free((void ***)(&(*process)->args));
		if ((*process)->redir)
			free_redir(&(*process)->redir);
		free_ref(&(*process)->cmd);
		free(*process);
		*process = temp;
	}
	(*process) = NULL;
}
