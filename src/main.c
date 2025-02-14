/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:38 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/12 14:20:05 by frbranda         ###   ########.fr       */
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
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
	while (1)
	{
		input = readline("prompt> ");
		if (!input || ft_strncmp(input, "exit", 10) == 0) // Ctrl+D EOF
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		tokenizer(input);
		add_history(input); // Deletes history after closing (our own)
		free(input);
	}
	return 0;
}
