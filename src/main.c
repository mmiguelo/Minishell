/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:38 by frbranda          #+#    #+#             */
/*   Updated: 2025/04/08 18:07:07 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_list_to_array(t_token *tokens)
{
	t_token	*temp;
	char	**array;
	int		count;
	int		i;

	temp = tokens;
	count = 0;
	i = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	array = ft_calloc((count + 1), sizeof(char*));
	if (!array)
		return (NULL);
	temp = tokens;
	while (temp)
	{
		array[i] = ft_strdup(temp->token);
		temp = temp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

// ctr + c handler (make new .c file)
void	sigint_handler(int sig)
{
	(void) sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_minishell(t_shell *shell, char **envp)
{
	t_builtin	func;
	char		**args;
	
	ft_init(shell, envp);
	while (1)
	{
		shell->input = readline("minishell> ");
		if (!shell->input || ft_strncmp(shell->input, "exit", 6) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		add_history(shell->input);
		tokenizer(&shell, ft_strdup(shell->input));
		args = token_list_to_array(shell->token_list);
		int i = -1;
		while (args[++i])
			printf("arg[%i]: %s\n", i, args[i]);
		if (args && args[0])
		{
			func = ft_isbuiltin(args[0], shell);
			if (func)
			{
				if (func(args, shell) != 0)
					printf("Error executing %s\n", args[0]);
			}
			else
				printf("Command not found\n");
		}
		free_char_pp(args);
		free_tokens(&shell->token_list);
		free(shell->input);
	}
	ft_kill(&shell, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_signals();
	ft_memset(&shell, 0, sizeof(t_shell));
	ft_minishell(&shell, envp);
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
