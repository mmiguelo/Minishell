/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:29:20 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/19 18:28:31 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

//# include "minishell.h"  - only if minishell struct are needed!

/*=============================================================================#
#                               DEFINES                                        #
#=============================================================================*/



/*=============================================================================#
#                               STRUCTS                                        #
#=============================================================================*/

typedef enum e_token_type
{
	COMMAND,
	ARG,
	PIPE,
	REDIR_R,
	REDIR_L,
	APPEND,
	HEREDOC,
	
} t_token_type;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

// token
// tokenizer.c
void	token_split(t_token **token,char *input);
void	tokenizer(char *input);

// token_tools.c
t_token	*initialize_token(char *input);
t_token	*find_last_token(t_token *token);
t_token	*list_add_last_token(t_token **token, t_token *new);
void	print_token_list(t_token *token);
void	print_tokens(t_token *token);

/* // quote_handler.c

// split_minishell.c
t_token	*minishell_split(t_token **token, char *input) !!!!!! PARSING = TOKEN*/ 

#endif