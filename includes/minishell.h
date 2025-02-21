/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:31 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/21 20:03:40 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# include "free.h" 
# include "tokens.h"

/*=============================================================================#
#                               DEFINES                                        #
#=============================================================================*/

# define SIZE 85

# define SUCCESS 0
# define UNKNOWN_COMMAND 127

/*=============================================================================#
#                               STRUCTS                                        #
#=============================================================================*/

/* typedef struct s_token
{
	char			*token;
	t_token_type	type;
	struct t_token	*left;
	struct t_token	*right;
} t_token;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct t_env	*left;
	struct t_env	*right;
} t_env;

typedef struct s_shell
{
	t_token	*token_tree;
	t_env	*env_var;
	int		exit_status;
} t_shell; */


/*=============================================================================#
#                               GENERAL                                        #
#=============================================================================*/



#endif