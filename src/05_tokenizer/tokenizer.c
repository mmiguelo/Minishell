/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/22 18:02:07 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	finish_tokenizer(t_shell *shell, t_token *token_list)
{
	t_token	*token;
	char	*last_arg;
	
	last_arg = "";
	token = token_list;
	while (token)
	{
		if (token->type == CMD || token->type == ARG)
			last_arg = token->token;
		token = token->next;
	}
	update_env(shell, "_", last_arg);
	shell->token_list = token_list;
}

//TODO DELETE printf and (*shell)->exit_status = 0;
void	tokenizer(t_shell **shell, char *s)
{
	t_token	*token_list;
	t_info	info;
	int		i;

	token_list = NULL;
	inizialize_info(&info);
	i = 0;
	while (s[i])
	{
		split_spaces(token_list, s, &i, &info);
		if (handle_expansions(*shell, &s, &i, &info) == TRUE)
			continue ;
		if (info.error_flag == TRUE)
			return (free_tokens(&token_list));
		handle_quotes(&s, &i, &info);
		add_new_token(&token_list, s, &info);
		info.type_flag = FALSE;
	}
	free(s);
	finish_tokenizer(*shell, token_list);
}

int	parse_tokenizer(t_shell *shell)
{
	char	*dup;

	dup = ft_strdup(shell->input);
	if (!dup)
		return (ERROR);
	tokenizer(&shell, dup);
	if (!shell->token_list)
	{
		free_ref(&shell->input);
		return (ERROR);
	}
	return (SUCCESS);
}
