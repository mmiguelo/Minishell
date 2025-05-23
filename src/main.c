#include "minishell.h"

void	read_input(t_shell *shell)
{
	shell->prev_exit_status = shell->exit_status; // for signal exit_status
	shell->exit_status = 0;
	set_signo(0); // reset signo
	reset_heredoc_id(); // reset heredoc_id
	reset_dups(shell); // safe reset dups
	errno = 0; // reset errno
	if (!isatty(STDOUT_FILENO))
		rl_outstream = stderr;
	shell->input = readline("minishell> ");
	if (get_signo() == CTRL_C)
		shell->prev_exit_status = CTRL_C + 128;
	if (!shell->input)
	{
		ft_putstr_fd("exit\n", 2);
		ft_kill(&shell, shell->prev_exit_status);
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
			continue ;
		if (parse_tokenizer(shell) != SUCCESS)
			continue ;
		if (build_process(shell) != SUCCESS)
			continue ;
		execute_process(shell);
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

/* void	ft_execute_line(t_shell *shell, char *line)
{
	shell->prev_exit_status = shell->exit_status;
	shell->exit_status = 0;
	set_signo(0);
	reset_heredoc_id();
	reset_dups(shell);
	errno = 0;

	shell->input = ft_strdup(line);
	if (!shell->input || only_spaces(shell->input) == TRUE)
		return ;

	if (ft_parsing(shell, shell->input) != SUCCESS)
		return ;
	if (parse_tokenizer(shell) != SUCCESS)
		return ;
	if (build_process(shell) != SUCCESS)
		return ;

	execute_process(shell);
	free_loop(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc == 3 && strcmp(argv[1], "-c") == 0)
	{
		ft_init(&shell, envp);
		set_signal_mode(SIGMODE_DEFAULT);
		ft_execute_line(&shell, argv[2]);
		return (0);
	}
	else if (argc == 1)
	{
		ft_init(&shell, envp);
		set_signal_mode(SIGMODE_DEFAULT);
		ft_minishell(&shell);
		return (0);
	}
	else
	{
		return (ft_printf_fd(STDERR_FILENO, ERROR_LAUCH), 0);
	}
} */
