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

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
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
		return (ft_putstr_fd("error in splitting search_path\n", 2), NULL);
	return (check_path_and_return(full_path, cmd));
}
