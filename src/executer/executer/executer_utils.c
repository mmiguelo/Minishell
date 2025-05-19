#include "minishell.h"

int	count_pid(t_shell *shell)
{
	int i;
	t_node	*process;

	process = shell->process;
	i = 0;

	while (process)
	{
		i++;
		process = process->next;
	}
	return (i);
}

void	reset_dups(t_shell *shell)
{
	dup2(shell->fd[0], STDIN_FILENO);
	dup2(shell->fd[1], STDOUT_FILENO);
}

char	*search_path(char *cmd, char **envp, int i)
{
	char	**full_path;
	char	*partial_path;
	char	*temp;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL); // to change
	}
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	full_path = ft_split(envp[i] + 5, ':' );
	if (!full_path)
		return (ft_putstr_fd("error in splitting search_path\n", 2), NULL);
	i = 0;
	while (full_path[i])
	{
		temp = ft_strjoin(full_path[i], "/");
		partial_path = ft_strjoin(temp, cmd);
		free_ref(&temp);
		if (access(partial_path, F_OK | X_OK) == 0)
			return (free_char_pp_ref(&full_path), partial_path);
		free_ref(&partial_path);
		i++;
	}
	free_char_pp_ref(&full_path);
	return (NULL);
}
