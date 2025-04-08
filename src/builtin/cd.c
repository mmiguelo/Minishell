/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:19:37 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/04/07 18:47:28 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Updates or adds an environment variable in the shell's environment.
 * 
 * This function searches for the specified environment variable (`var`) in
 * the shell's
 * environment (`shell->envp`). If the variable exists, it updates its value
 * to `path`.
 * If it does not exist, it adds a new entry to the environment.
 * 
 * @param shell A pointer to the shell structure containing the environment
 * variables.
 * @param var The name of the environment variable to update or add.
 * @param path The new value to assign to the environment variable.
 */
void	update_env(t_shell *shell, const char *var, char *path)
{
	int		i;
	char	*new_line;
	char	**env;
	char	*temp;

	i = get_env_line(var, shell);
	if (i == -1)
	{
		env = shell->envp;
		while (*env)
			env++;
		new_line = ft_strjoin(var, "=");
		temp = new_line;
		new_line = ft_strjoin(new_line, path);
		free(temp);
		*env = new_line;
	}
	else
	{
		free(shell->envp[i]);
		shell->envp[i] = ft_strjoin(var, "=");
		temp = shell->envp[i];
		shell->envp[i] = ft_strjoin(shell->envp[i], path);
		free(temp);
	}
}

int	save_cwd(char *cwd, size_t size)
{
	if (getcwd(cwd, size) == NULL)
		return (errno);
	return (0);
}

int	verify_dir(const char *dir)
{
	if (!dir || !dir[0] || access(dir, F_OK) != 0)
		return (perror(dir), 1);
	if (chdir(dir) != 0)
		return (perror("cd"), 1);
	return (0);
}

int	folder_back(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", shell);
	if (oldpwd == NULL)
	{
		ft_printf("minishell: cd: OLDPWD not set\n");
		return (1);
	}
	ft_printf("%s\n", oldpwd);
	if (verify_dir(oldpwd) != 0)
		return (1);
	return (0);
}

/**
 * @brief Changes the current working directory.
 * 
 * This function implements the `cd` built-in command, handling different cases:
 * - No arguments: changes to the `HOME` directory.
 * - `cd -`: switches to the previous directory (`OLDPWD`) and prints it.
 * - Too many arguments: prints an error message.
 * - Invalid option (`-x`): prints an error message.
 * 
 * If the directory change is successful, it updates the `PWD` and `OLDPWD`
 * environment variables.
 * 
 * @param args Array of command arguments (`args[0]` is "cd", `args[1]` is the
 * target path).
 * @param shell Pointer to the shell structure containing environment variables.
 * @return int 0 on success, 1 on failure, 2 if an invalid option is provided.
 */
int	ft_cd(char **args, t_shell *shell)
{
	char	*new_cwd;

	if (save_cwd(shell->pwd, sizeof(shell->pwd)) != 0)
		return (perror("minishell: cd"), 1);
	if (args[1] && args[1][0] == '-' && args[1][1])
		return (ft_printf("minishell: cd: %s: invalid option\n", args[1]), 2);
	if (args[1] && args[2])
		return (ft_printf("minishell: cd: too many arguments\n"), 1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		new_cwd = get_env_value("HOME", shell);
	else if (ft_strcmp(args[1], "-") == 0)
		return (folder_back(shell));
	else
		new_cwd = args[1];
	if (verify_dir(new_cwd) != 0)
		return (1);
	update_env(shell, "OLDPWD", shell->pwd);
	if (save_cwd(shell->pwd, sizeof(shell->pwd)) == 0)
		update_env(shell, "PWD", shell->pwd);
	return (0);
}
