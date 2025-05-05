/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:31 by frbranda          #+#    #+#             */
/*   Updated: 2025/05/05 16:06:36 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h> // error codes
# include <signal.h> // signals
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h> // wait for child process
# include <fcntl.h> // file manipulation
# include <dirent.h> // folder manipulation
# include "../libft/libft.h"

/*=============================================================================#
#                                   DEFINES                                    #
#=============================================================================*/

# define NO_NUMERIC "minishell: exit: %s: numeric argument required\n"

# define ERROR_LAUCH "Error: minishell must be lauched without arguments\n"
# define ERROR_SYNTAX "syntax error near unexpected token `%s'\n"
# define ERROR_SYNTAX_END "syntax error near unexpected token `newline'\n"
# define ERROR_UNCLOSED_QUO "Error: Quotes must be closed\n"
# define ERROR_UNCLOSED_PIPE "Error: Open pipes not allowed\n"
# define CORE_DUMP_MSG "Quit (core dumped)\n"

// all special cases
# define SPECIAL " \t\r\n\v\f\"\'<>|"
# define WHITE_SPACES " \t\r\n\v\f"
# define OPERATOR "<>|"
# define T_REDIR "<>"
# define T_PIPE "|"
# define QUOTES "\"\'"

// signal helper
# define CTRL_C 2
# define SET 0
# define GET 1

// signal changer
# define SIGMODE_DEFAULT 0 // main/default
# define SIGMODE_PIPELINE 1 // pipeline
# define SIGMODE_CHILD 2 // pipe child
# define SIGMODE_HEREDOC 3 // heredoc

// error handler
# define INVALID -1
# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 2
# define UNKNOWN_COMMAND 127

// token type
# define CMD 0
# define ARG 1
# define PIPE 2
# define REDIR_IN 4// < redir onto a file and chage its contente
# define REDIR_OUT 5// >
# define APPEND 6// >> redir onto a file and add content
# define HEREDOC 7// <<
# define REDIR 8 // tree contruct

# define FALSE 0
# define TRUE 1

// Quote handle
# define GENERAL 0	
# define SINGLE_QUO 1
# define DOUBLE_QUO 2

/*=============================================================================#
#                                   STRUCTS                                    #
#=============================================================================*/

typedef struct s_token
{
	char			*token;
	int				type;	//EXEC/CMD/PIPE/REDIR
	struct s_token	*next;
}	t_token;

/*typedef enum Redir {
	INPUT,
	OUTPUT
}	Redir_e;*/

typedef struct s_node
{
	int	type;
}	t_node;

typedef struct s_pipe
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe;

typedef struct s_redir
{
	int				type;
	char			*redir_file;
	int				type_of_redirection;
	struct s_redir	*next;
}	t_redir;

typedef struct s_exec
{
	int		type;
	t_list	*argv;
	t_redir	*redirs;
}	t_exec;

// struct helper
typedef struct s_info
{
	int	start;
	int	end;
	int	len;
	int	env_start;
	int	env_end;
	int	type;
	int	type_flag;
	int	mode;
	int	error_flag;
}	t_info;

typedef struct s_shell
{
	char	*input;
	char	**args;
	t_token	*token_list;
	t_token	*head;
	t_info	info;
	t_node	*tree;
	int		pid;
	char	**envp;
	char	**cmd;
	char	pwd[1024];
	char	*old_pwd;
	int		exit_status;
	int		prev_exit_status;
}	t_shell;

//function pointer type for builtins
typedef int	(*t_bt)(char **, t_shell *);

/*=============================================================================#
#                                     MAIN                                     #
#=============================================================================*/

void	ft_minishell(t_shell *shell);

// TODO temp... change when tree is done
int		execute_command(char *arg);
void	execute_external_cmd(t_shell *shell);
void	builtin_and_cmd(t_shell *shell);

/*=============================================================================#
#                                   PARSING                                    #
#=============================================================================*/

int		ft_parsing(t_shell *shell, char *s);
void	handle_syntax_error(char *s, int i);
int		check_syntax_first_pipe(t_shell *shell, char *s, int *i);
int		check_syntax_pipes(t_shell *shell, char *s, int *i);
int		check_syntax_quotes(t_shell *shell, char *s, int *i);
int		check_syntax_redir(t_shell *shell, char *s, int *i);

/*=============================================================================#
#                                  TOKENIZER                                   #
#=============================================================================*/

// tokenizer.c
void	tokenizer(t_shell **shell, char *s);

// 00_handle_spaces
//  token_split_space.c
void	token_word_handler(char *s, int *i, t_info *info);
void	token_redir_handler(char *s, int *i, t_info *info);
void	split_spaces(t_token *token_list, char *s, int *i, t_info *info);

//  type_helper.c
void	get_token_redir_type(char *s, int i, t_info *info);
void	get_token_type(t_token *token_list, t_info *info);

// 01_handle_expansions
//  handle_expansions.c
char	*expand_variable(t_shell *shell, char **s_ptr, int *i, t_info *info);
int		expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info);
int		handle_expansions(t_shell *shell, char **s_ptr, int *i, t_info *info);

//  handle_dollar_cases.c
char	*remove_dollar(char **s_ptr, int *i, t_info *info);
char	*handle_double_dollar(t_shell *shell, char *s, int *i, t_info *info);
char	*handle_question_mark(t_shell *shell, char *s, int *i, t_info *info);

//  expansion_helper.c
char	*take_var_name(char *s, int *i);
char	*get_env_value_expansion(char *var_name, char **envp);
int		check_if_var_is_alone(char *s, int i, t_info *info);
char	*expand_var_in_str(char *s, char *var_value, int i, t_info *info);

// 02_handle_quotes
//	handle_quote.c
void	remove_quotes(char *s, int i, t_info *info);
void	handle_quotes(char **s_ptr, int *i, t_info *info);

//  quote_helper.c
void	quote_changer(char *s, int *i, t_info *info);

// 03_add_new_token
//  add_new_token.c
t_token	*add_new_token(t_token **token_list, char *temp, t_info *info);

// token_tools.c
t_token	*find_last_token(t_token *token);
t_token	*add_last_token(t_token **token, t_token *new);

// initialize_structs.c
// TODO DELETE initialize_env (or change it when exists)
void	inizialize_info(t_info	*info);
t_token	*initialize_token(char *s, int type);
//t_env	*initialize_env(void);
t_shell	*initialize_shell(void);

/*=============================================================================#
#                                   BUILTIN                                    #
#=============================================================================*/

//builtin functions
t_bt	ft_isbuiltin(char *cmd, t_shell *shell);

//cd
int		ft_cd(char **args, t_shell *shell);
int		folder_back(t_shell *shell);
int		verify_dir(const char *dir);
int		save_cwd(char *cwd, size_t size);
void	update_env(t_shell *shell, const char *var, char *path);
int		get_env_line(const char *var, t_shell *shell);
char	*get_env_value(const char *var, t_shell *shell);

//echo
int		ft_echo(char **args, t_shell *shell);

//env
int		ft_env(char **args, t_shell *shell);
void	when_no_env(t_shell *shell);

//exit
int		ft_exit(char **args, t_shell *shell);

//export
int		ft_export(char **args, t_shell *shell);
int		ft_print_export(t_shell *shell);
void	sort_export(char **new_export);
int		check_export_var(char **args, t_shell *shell);
void	handle_export_var(char **arg, t_shell *shell, char *var, char *value);
int		check_if_var_is_in_env(char *arg, t_shell *shell);
int		validate_var(const char *var);
int		check_for_value(char *arg);
char	*get_export_var(char *arg);
char	*get_export_value(char *arg);
int		export_error(char *arg);
void	append_var_to_envp(char **var, t_shell *shell);
char	*add_double_quotes(char *str, int j);
void	give_value(char **var, char *new_var, t_shell *shell, int index);
int		add_var_to_envp(char *var, t_shell *shell);
int		update_existing_var(char *new_var, t_shell *shell, int i);
char	**realloc_env(char **envp);
char	*get_value(char *var);
void	print_exported_vars(char **new_export);
void	concatenate_value(char **var, char *new_var, t_shell *shell, int i);

//pwd
int		ft_pwd(char **args, t_shell *shell);

//unset
int		ft_unset(char **args, t_shell *shell);
void	ft_erase_var(char *var, t_shell *shell);

/*=============================================================================#
#                                    UTILS                                     #
#=============================================================================*/

void	ft_init(t_shell	*shell, char **envp);
char	**init_env(char **envp);
char	**token_list_to_array(t_token *tokens);
int		only_spaces(char *input);

/*=============================================================================#
#                                   SIGNALS                                    #
#=============================================================================*/

// signal.c
void	set_signal_mode(int mode);

// signal_handler.c
void	signal_default_handler(int signo);
void	signal_pipe_handler(int signo);

// setget_signo.c
void	set_signo(int new_value);
int		get_signo(void);

/*=============================================================================#
#                      	              FREE                                     #
#=============================================================================*/

// free_exit.c
void	free_exit(t_shell *shell, int exit_status);
void	exit_init(t_shell *shell, char *reason);

// free_shell.c
void	free_tokens(t_token **token);
void	free_shell(t_shell	**shell);

// free.c
void	free_ref(char **s);
void	free_char_pp(char **s);
void	free_char_pp_ref(char ***s);
int		free_matriz(char **shell, int i);
void	ft_kill(t_shell **shell, int status);

/*=============================================================================#
#                      	             PRINT                                     #
#=============================================================================*/

// print_shell.c?

// print_error.c
int		print_msg_error(char *error);
int		print_invalid_var(char *var);

// print_token.c
void	print_type(t_info *info);
void	print_tokens(t_token *token);
void	print_tokens_simple(t_token *token);

/*=============================================================================#
#                      	           TREE                                        #
#=============================================================================*/

// node.c
t_pipe	*create_pipe_node(t_node *left, t_node *right);
t_redir	*create_redir_node(char *filename, int type);
t_exec	*create_cmd_node(void);

// tree.c
int		make_tree(t_shell *root);
t_node	*parse_pipe(t_token **current);
t_node	*parse_exec(t_token **current);

// tree_helper.c
int		redirection_type(t_token *token);
int		insert_argv_node(t_exec *node, char *content);
int		insert_redir_node(t_exec *node, char *filename, int type);

// exec_tree.c
void	parse_exec_or_pipe(t_shell *shell, t_node *node);

#endif