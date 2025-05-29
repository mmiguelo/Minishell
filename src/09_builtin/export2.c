/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:14:55 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/29 16:57:12 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes and validates environment variable assignments from the
 * export command.
 * 
 * This function processes each argument passed to the `export` command,
 * separating the variable names and their values. It validates the variables,
 * and if valid, it calls a handler function to perform the export action. If a
 * variable is invalid, it prints an error message. The function also prints the
 * variable and its value for debugging purposes.
 * 
 * @param args Array of strings representing the arguments passed to the `export`
 * command. Each argument can be a variable assignment of the form `VAR=VALUE`.
 * @param shell Pointer to the shell structure, which contains the environment
 * variables and other data.
 * @return int Returns `0` upon successful completion. If an error occurs (such
 * as an invalid variable), it prints an error message and returns `0`.
 */
int	check_export_var(char **args, t_shell *shell)
{
	int		i;
	char	*var;
	char	*value;
	int		error;

	i = 0;
	error = 0;
	while (args[++i])
	{
		var = get_export_var(args[i]);
		value = get_export_value(args[i]);
		if (validate_var(var))
			handle_export_var(&args[i], shell, var, value);
		else
			error = print_invalid_var(args[i]);
		if (var)
			free(var);
		if (value)
			free(value);
	}
	return (error);
}

char	*add_double_quotes(char *str, int j)
{
	char	*new_str;
	int		i;
	int		k;

	new_str = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (i == j)
			new_str[k++] = '\"';
		new_str[k++] = str[i++];
	}
	new_str[k++] = '\"';
	if (new_str[k - 1] == '\"' && new_str[k - 2] == '=')
		new_str[k++] = '\"';
	new_str[k] = '\0';
	free(str);
	return (new_str);
}

/**
 * @brief Sorts an array of strings in lexicographical order.
 * 
 * This function sorts an array of strings (environment variables in this case)
 * in ascending lexicographical order using a simple bubble sort algorithm. It is
 * used to sort the environment variables before printing them in the
 * `ft_print_export` function, ensuring they are listed in alphabetical order.
 * 
 * @param new_export Array of strings (environment variables) to be sorted. Each
 * string represents an environment variable in the format `VAR=VALUE`.
 */
void	sort_export(char **new_export)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (new_export[++i] != NULL)
	{
		j = i;
		while (new_export[++j] != NULL)
		{
			if (ft_strcmp(new_export[i], new_export[j]) > 0)
			{
				temp = new_export[i];
				new_export[i] = new_export[j];
				new_export[j] = temp;
			}
		}
	}
}

void	give_value(char **var, char *new_var, t_shell *shell, int index)
{
	char	*returned;
	char	*new_value;

	returned = ft_strdup(ft_strnstr(*var, "+=", ft_strlen(*var)) + 1);
	if (!returned)
		return ;
	new_value = ft_strdup_free(new_var, returned);
	if (!new_value)
		return ;
	free(shell->envp[index]);
	shell->envp[index] = ft_strdup(new_value);
	if (!shell->envp[index])
		return ;
	free(new_value);
}

int	add_var_to_envp(char *var, t_shell *shell)
{
	int		i;
	char	*new_var;
	char	**new_envp;

	new_var = ft_strdup(var);
	if (!new_var)
		return (-1);
	i = get_env_line(new_var, shell);
	if (update_existing_var(new_var, shell, i) == 0)
		return (0);
	new_envp = realloc_env(shell->envp);
	if (!new_envp)
	{
		free(new_var);
		return (-1);
	}
	shell->envp = new_envp;
	shell->envp[ft_arrlen(shell->envp)] = new_var;
	return (0);
}
