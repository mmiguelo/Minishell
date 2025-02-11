/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:31 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/11 17:46:24 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/*=============================================================================#
#                               DEFINES                                        #
#=============================================================================*/


/*=============================================================================#
#                               STRUCTS                                        #
#=============================================================================*/

typedef struct s_token
{
	char			*token;
	char			*type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/

// token
// tokenizer.c
void	tokenizer(char *input);

// free.c
void	free_char_pp(t_token **token);
void	free_tokens(t_token **token);



#endif