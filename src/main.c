/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:38 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/21 20:32:53 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces(char	*input)
{
	int	i;

	i = 0;
	while(input[i])
	{
		if (!ft_strchr(WHITE_SPACES, input[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_minishell(t_shell *shell)
{
	t_bt	func;

	while (1)
	{
		shell->prev_exit_status = shell->exit_status; // for signal exit_status
		shell->exit_status = 0;
		set_signo(0); // reset signo
		errno = 0; // reset errno
		shell->input = readline("minishell> ");
		if (get_signo() == CTRL_C)
			shell->prev_exit_status = CTRL_C + 128;
		if (!shell->input)
		{
			ft_putstr_fd("exit\n", 2);
			free_exit (shell, shell->prev_exit_status);
		}
		if (only_spaces(shell->input) == FALSE)
			add_history(shell->input);
		tokenizer(&shell, ft_strdup(shell->input));
		shell->args = token_list_to_array(shell->token_list);
		if (shell->args && shell->args[0])
		{
			func = ft_isbuiltin(shell->args[0], shell);
			if (func)
			{
				if (func(shell->args, shell) != 0)
					printf("Error executing %s\n", shell->args[0]);
				// TODO if func export e mudou update env
				//TODO envp arg to env list (FREE OLD ENV)
			}
			else
				printf("Command not found\n");
		}
		free_char_pp_ref(&shell->args);
		free_tokens(&shell->token_list);
		free_ref(&shell->input);
	}
	ft_kill(&shell, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1)
		return (ft_printf_fd(STDERR_FILENO, ERROR_LAUCH), 0);
	(void)argv;
	ft_init(&shell, envp);
	set_signal_default();
	ft_minishell(&shell);
	return (0);
}

/*	line: 31 -> // ignore on prompt but leave with leak when using cat
	line: 37 -> // Ctrl+D EOF

// Do different "whiles(1)" for main/cat/here_doc also 
// signals are different(ctrl + /) ??? */

/* // Fuction that helps construct the binary tree based on tokenizer input
t_node	*return_node(tokenptr)
{
	t_node	*node = (t_node *)cmd(&tokenptr);
	if *tokenptr == pipe	
		return ((t_node *)pipe(node, return_node(tokenptr++)));
	return (node);
}

// exec commands after binary tree is created
exec(node)
{
	if node.type = pipe
	{
		t_pipe	*pipe = (t_pipe *)node;
		exec(pipe->left);
		exec(pipe->right);
		return;
	}
	else if (node->tyoe == cmd)
	{
		t_cmd	*cmd = (t_cmd*)node;
		executeCMD(cmd);
	}
} */
