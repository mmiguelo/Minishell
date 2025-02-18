/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:38 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/18 19:02:28 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(void)
{
	char *input;
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN); //ignore on prompt but leave with leak when using cat
	signal(SIGTSTP, SIG_IGN);
	while (1)
	{
		input = readline("prompt> ");
		if (!input || ft_strncmp(input, "exit", 6) == 0) // Ctrl+D EOF
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		tokenizer(input);
		add_history(input); // Deletes history after closing (our own??????? maybe not)
		free(input);
	}
	return 0;
}

// Do different "whiles(1)" for main/cat/here_doc also signals are different (ctrl + /)
