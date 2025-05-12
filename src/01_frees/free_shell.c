#include "minishell.h"

void	free_loop(t_shell *shell)
{
	free_char_pp_ref(&shell->args);
	free_tokens(&shell->token_list);
	free_ref(&shell->input);
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
		if ((*token)->heredoc)
			clean_heredoc(&(*token)->heredoc);
		free(*token);
		*token = temp;
	}
	(*token) = NULL;
}
