#include "minishell.h"

int	count_pid(t_shell *shell)
{
	int		i;
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
	if (shell->fd[0] != STDIN_FILENO)
		dup2(shell->fd[0], STDIN_FILENO);
	if (shell->fd[1] != STDOUT_FILENO)
		dup2(shell->fd[1], STDOUT_FILENO);
}

static char	**get_paths_from_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	for (i = 0; envp[i]; i++)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
	}
	return (NULL);
}

static char	*check_path_and_return(char **full_path, char *cmd)
{
	int		i;
	char	*temp;
	char	*partial_path;

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

char	*search_path(char *cmd, char **envp)
{
	char	**full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL); // to change
	}
	full_path = get_paths_from_env(envp);
	if (!full_path)
		return (NULL);
	return (check_path_and_return(full_path, cmd));
}
