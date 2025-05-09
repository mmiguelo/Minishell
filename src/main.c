/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:38 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/09 15:29:14 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_shell *shell)
{
	shell->prev_exit_status = shell->exit_status; // for signal exit_status
	shell->exit_status = 0;
	set_signo(0); // reset signo
	reset_heredoc_id(); // reset heredoc_id
	errno = 0; // reset errno
	shell->input = readline("minishell> ");
	if (get_signo() == CTRL_C)
		shell->prev_exit_status = CTRL_C + 128;
	if (!shell->input)
	{
		ft_putstr_fd("exit\n", 2);
		ft_kill (&shell, shell->prev_exit_status);
	}
	if (only_spaces(shell->input) == FALSE)
		add_history(shell->input);
}

void	ft_minishell(t_shell *shell)
{
	while (1)
	{
		read_input(shell);
		if (ft_parsing(shell, shell->input) != SUCCESS)
		{
			free_ref(&shell->input);
			continue ;
		}
		tokenizer(&shell, ft_strdup(shell->input));
		if (heredoc_handler(shell) != SUCCESS)
		{
			free_loop(shell);
			continue ;
		}
		shell->args = token_list_to_array(shell->token_list);
		builtin_and_cmd(shell);
		free_loop(shell);
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
	set_signal_mode(SIGMODE_DEFAULT);
	ft_minishell(&shell);
	return (0);
}

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
