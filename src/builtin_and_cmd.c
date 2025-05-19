/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_and_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:35:41 by yes               #+#    #+#             */
/*   Updated: 2025/05/19 16:27:23 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	execute_command(char *arg)
{
	//TODO change when tree execute is done
	if (arg[0] == '.' && arg[1] == '/')
	{
		if (access(arg, F_OK) == 0)
			return (0);
	}
	return (-1);
}

void	execute_external_cmd(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(shell->args[0], shell->args, shell->envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		shell->exit_status = WEXITSTATUS(status);
	}
	else
	{
		perror("fork failed");
		shell->exit_status = 1;
	}
}

void	builtin_and_cmd(t_shell *shell)
{
	t_bt	func;

	//TODO change when tree execute is done
	if (shell->args && shell->args[0])
	{
		func = ft_isbuiltin(shell->args[0], shell);
		if (func)
		{
			if (func(shell->args, shell) != 0)
				printf("Error executing %s\n", shell->args[0]);
		}
		else if (execute_command(shell->args[0]) == 0)
			execute_external_cmd(shell);
		else
		{
			shell->exit_status = 127;
			ft_printf_fd(2, "Command not found\n");
		}
	}
} */
