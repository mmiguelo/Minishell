# Minishell

This project is a custom implementation of a command-line interpreter, similar to `bash`. As part of the 42 curriculum, Minishell is designed to parse user input, handle command execution, and manage system resources like processes and file descriptors.

## Features

*   **Command Execution:** Supports executing both built-in commands and external system commands found in the `PATH`.
*   **Piping:** Chains multiple commands using pipes (`|`), redirecting the standard output of one command to the standard input of the next.
*   **Redirections:** Manages I/O redirection with:
    *   `<` (Input redirection)
    *   `>` (Output redirection, truncating the file)
    *   `>>` (Append output redirection)
    *   `<<` (Heredoc)
*   **Environment Variables:** Expands environment variables (e.g., `$USER`, `$PWD`) and the special exit status variable (`$?`).
*   **Re-tokenization:** After the first expansion, the shell scans the resulting tokens again to detect and expand any newly introduced variables or special symbols (e.g., a variable that expands into another variable or command). This ensures full recursive expansion and correct token structure before execution. - 
*   **Quoting:** Correctly handles single (`'`) and double (`"`) quotes to manage string literals and expansions.
*   **Signal Handling:** Intercepts and manages `Ctrl-C` (SIGINT) and `Ctrl-\` (SIGQUIT) to mimic `bash` behavior, providing a stable user experience.
*   **Built-in Commands:**
    *   `echo` with the `-n` option.
    *   `cd` to change the current directory.
    *   `pwd` to display the current working directory.
    *   `export` to set or display environment variables.
    *   `unset` to remove environment variables.
    *   `env` to display the current environment.
    *   `exit` to terminate the shell.

## Implementation Overview

The shell operates in a continuous loop: reading user input, parsing it, and then executing the commands.

### 1. Parsing & Tokenization
The core of the shell's logic begins with parsing the raw input from the user.
1.  **Syntax Validation:** The input string is first scanned for fundamental syntax errors, such as unclosed quotes, misplaced pipes, or invalid redirection syntax.
2.  **Tokenization:** The validated string is broken down into a linked list of tokens (`t_token`). Each token is categorized by type (e.g., `CMD`, `ARG`, `PIPE`, `REDIR_IN`).
3.  **Expansion & Quote Removal:** Environment variables are expanded. Subsequently, quotes are processed and removed, and backslash-escaped characters are handled.

### 2. Process Building
Once tokenized, the stream of tokens is converted into a more structured format for execution.
1.  **Process Nodes:** The token list is transformed into a linked list of process nodes (`t_node`), where each node represents a simple command and its arguments. Pipes in the token list delineate these nodes.
2.  **Redirection Handling:** I/O redirections are parsed and stored within a separate linked list (`t_redir`) attached to each process node.
3.  **Heredoc Management:** For `<<` redirections, temporary files are created to store the heredoc content, which is read during the execution phase.

### 3. Execution
The execution engine forks processes to run commands.
*   **Single Commands:** If a command is a built-in like `cd`, `export`, or `exit`, it is executed directly in the main shell process. Other commands are executed in a child process.
*   **Pipelines:** For commands chained with pipes, a child process is created for each command in the pipeline. File descriptors are managed to ensure that the output of one process is correctly piped to the input of the next.
*   **Error Handling:** The executor handles errors such as "command not found" (127) or permission denied (126) and sets the appropriate exit status.

## How to Build and Run

### Prerequisites
*   A C compiler (e.g., `cc`, `gcc`)
*   `make`
*   The `readline` library (for command history and interactive editing)

### Compilation
Clone the repository and run `make`:
```bash
git clone https://github.com/mmiguelo/minishell.git
cd minishell
make
```

### Running the Shell
Execute the compiled binary:
```bash
./minishell
```

### Makefile Rules
The `Makefile` provides several rules for convenience:
*   `make all`: (Default) Compiles the entire project.
*   `make clean`: Removes all object files.
*   `make fclean`: Removes object files and the `minishell` executable.
*   `make re`: Cleans the project and recompiles everything.
