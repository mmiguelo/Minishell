/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:29:20 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/12 14:40:48 by frbranda         ###   ########.fr       */
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

typedef struct s_token
{
    char            *token;
    char            *type;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

// token
// tokenizer.c
t_token	*initialize_token(char *input);
t_token	*find_last_token(t_token *token);
t_token	*list_add_last_token(t_token **token, t_token *new);
void	token_split(t_token **token,char *input);
void	print_token_list(t_token *token);
void	tokenizer(char *input);

// free_tokens.c
void	free_char_pp(char **s); // generally usefull
void	free_tokens(t_token **token);

#endif