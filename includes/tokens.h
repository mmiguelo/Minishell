/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:29:20 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/24 12:42:02 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef TOKEN_H
// # define TOKEN_H

// # include "minishell.h"

// /*=============================================================================#
// #                               DEFINES                                        #
// #=============================================================================*/



// /*=============================================================================#
// #                               STRUCTS                                        #
// #=============================================================================*/

// typedef struct s_token
// {
// 	char			*token;
// 	int				type;
// 	struct s_token	*prev;
// 	struct s_token	*next;
// } t_token;


// /*=============================================================================#
// #                               GENERAL                                        #
// #=============================================================================*/

// // token
// // tokenizer.c
// void	token_split(t_token **token,char *input);
// void	tokenizer(char *input);

// // token_tools.c
// t_token	*initialize_token(char *input);
// t_token	*find_last_token(t_token *token);
// t_token	*list_add_last_token(t_token **token, t_token *new);
// void	print_token_list(t_token *token);
// void	print_tokens(t_token *token);

// /* // quote_handler.c

// // split_minishell.c
// t_token	*minishell_split(t_token **token, char *input) !!!!!! PARSING = TOKEN*/ 

// #endif