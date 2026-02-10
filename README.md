<a id="readme-top"></a>

<div align="center">

# 🐚 Minishell

**A custom Unix shell built from scratch — as beautiful as a shell | 42 School Project**

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norm-OK-brightgreen?style=for-the-badge)](https://github.com/42School/norminette)

---

*A command-line interpreter inspired by bash — parsing, tokenizing, expanding, and executing commands with pipes, redirections, and builtins.*

</div>

---

## 📖 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Built-in Commands](#-built-in-commands)
- [How It Works](#-how-it-works)
  - [Parsing & Tokenization](#1-parsing--tokenization)
  - [Process Building](#2-process-building)
  - [Execution](#3-execution)
- [Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#-usage)
- [Signal Handling](#-signal-handling)
- [Project Structure](#-project-structure)
- [Makefile Targets](#-makefile-targets)
- [Authors](#-authors)

---

## 🧠 About

**Minishell** is one of the most ambitious projects in the 42 curriculum — a fully functional command-line interpreter that replicates core `bash` behavior. It reads user input, parses and tokenizes it, expands variables, handles quoting, manages redirections and pipes, and executes both built-in and external commands.

This project strengthens key systems programming concepts:

- **Process creation** with `fork()` and `execve()`
- **Pipe** and **file descriptor** management
- **Signal handling** (`SIGINT`, `SIGQUIT`) across parent and child processes
- **Lexical analysis** — tokenization & syntax validation
- **Environment variable** expansion and quoting rules
- **Heredoc** implementation with temp files
- **Memory management** — no leaks across complex data structures

---

## ✨ Features

| Feature | Description |
|:--------|:------------|
| 🖥️ **Interactive Prompt** | Displays `minishell>` with readline for line editing and history |
| 🔧 **Command Execution** | Runs external commands by searching `$PATH`, or by absolute/relative path |
| 🔗 **Pipes** | Chains commands with `\|`, connecting stdout → stdin across a pipeline |
| 📂 **Redirections** | `<` input, `>` output (truncate), `>>` append, `<<` heredoc |
| 💲 **Variable Expansion** | Expands `$VAR`, `$?` (last exit status), and handles edge cases |
| 🔄 **Re-tokenization** | After expansion, rebuilds the token stream so `l$var"l"` → `ls -l` works correctly |
| 🔤 **Quoting** | Single quotes preserve literals; double quotes allow `$` expansion |
| 📡 **Signal Handling** | `Ctrl-C`, `Ctrl-\`, and `Ctrl-D` behave like bash in all contexts |
| 🧹 **Clean Memory** | Thorough freeing on every loop iteration, exit, and error path |

---

## 💻 Built-in Commands

<div align="center">

| Command | Description |
|:--------|:------------|
| `echo` | Print arguments to stdout (supports `-n` flag) |
| `cd` | Change working directory (supports `-`, `~`, relative & absolute paths) |
| `pwd` | Print the current working directory |
| `export` | Set or display environment variables |
| `unset` | Remove environment variables |
| `env` | Display the current environment |
| `exit` | Exit the shell with an optional status code |

</div>

---

## ⚙️ How It Works

The shell operates in a continuous **read → parse → execute** loop:

```
┌─────────────────────────────────────────────────────────────────┐
│                         SHELL LOOP                              │
│                                                                 │
│  ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌────────────┐    │
│  │  READ    │──▶│  PARSE   │──▶│  BUILD   │──▶│  EXECUTE   │    │
│  │  INPUT   │   │ TOKENIZE │   │ PROCESS  │   │  COMMANDS  │    │
│  └──────────┘   └──────────┘   └──────────┘   └────────────┘    │
│       ▲                                              │          │
│       └──────────────── free & loop ─────────────────┘          │
└─────────────────────────────────────────────────────────────────┘
```

### 1. Parsing & Tokenization

```
Input: echo "hello $USER" | cat -e > out.txt

  ┌─ Syntax Validation ─────────────────────────────┐
  │  ✓ Quotes closed                                │
  │  ✓ Pipes valid                                  │
  │  ✓ Redirections valid                           │
  └─────────────────────────────────────────────────┘
                      ↓
  ┌─ Tokenization ──────────────────────────────────┐
  │  [CMD:echo] [ARG:"hello $USER"] [PIPE:|]        │
  │  [CMD:cat] [ARG:-e] [REDIR_OUT:>] [ARG:out.txt] │
  └─────────────────────────────────────────────────┘
                      ↓
  ┌─ Expansion & Quote Removal ─────────────────────┐
  │  [CMD:echo] [ARG:hello mmiguelo] [PIPE:|]       │
  │  [CMD:cat] [ARG:-e] [REDIR_OUT:>] [ARG:out.txt] │
  └─────────────────────────────────────────────────┘
```

- **Syntax validation** — checks for unclosed quotes, misplaced pipes, and invalid redirections
- **Tokenization** — breaks input into a linked list of typed tokens (`CMD`, `ARG`, `PIPE`, `REDIR_IN`, `REDIR_OUT`, `APPEND`, `HEREDOC`)
- **Expansion** — resolves `$VAR` and `$?`, then re-tokenizes if needed
- **Quote removal** — strips quotes while preserving their semantic effect

### 2. Process Building

The token stream is converted into a linked list of **process nodes** (`t_node`):

```
Token list:  [echo] [hello] [|] [cat] [-e] [>] [out.txt]
                      ↓
Process 1:  cmd: "echo"    args: ["echo", "hello"]    redir: NULL
                      ↓
Process 2:  cmd: "cat"     args: ["cat", "-e"]         redir: > out.txt
```

- Each pipe delimiter creates a new process node
- Redirections are extracted into a separate `t_redir` linked list per node
- Heredocs generate temporary files in `/tmp/` that are read during execution

### 3. Execution

```
Single command (builtin)     →  Execute in main process
Single command (external)    →  Fork → execve in child
Pipeline (N commands)        →  Fork N children with pipe fds
```

- **Builtins** like `cd`, `export`, `exit` run in the parent process (they modify shell state)
- **External commands** are searched in `$PATH` and executed via `fork()` + `execve()`
- **Pipelines** create a child process per command, with `pipe()` connecting their I/O
- **Exit codes** — `127` (command not found), `126` (permission denied), and `$?` tracking

---

## 🚀 Getting Started

### Prerequisites

- **GCC** or **CC** compiler
- **Make**
- **readline** library

```bash
# Debian / Ubuntu
sudo apt-get install libreadline-dev
```

### Installation

```bash
# Clone the repository
git clone https://github.com/mmiguelo/Minishell.git
cd Minishell

# Build the project
make
```

---

## 🎯 Usage

```bash
./minishell
```

You'll be greeted with an interactive prompt:

```
minishell> echo "Hello, World!"
Hello, World!
minishell> ls -la | grep Makefile | wc -l
1
minishell> export NAME="42 Student"
minishell> echo $NAME
42 Student
minishell> cat << EOF > output.txt
> line one
> line two
> EOF
minishell> exit 42
```

### Supported Syntax

```bash
# Pipes
ls -la | grep ".c" | wc -l

# Redirections
echo "hello" > file.txt
cat < input.txt
echo "append" >> file.txt

# Heredoc
cat << DELIMITER

# Variable expansion
echo $HOME $USER $?

# Quoting
echo 'no $expansion here'
echo "but $expansion here"

# Combined
< infile grep "pattern" | sort | uniq > outfile
```

---

## 📡 Signal Handling

The shell intercepts signals to replicate bash behavior:

<div align="center">

| Signal | Context | Behavior |
|:------:|:--------|:---------|
| `Ctrl-C` | Interactive prompt | Displays new prompt on a new line |
| `Ctrl-C` | Running command | Terminates the child process |
| `Ctrl-C` | Heredoc | Closes heredoc and returns to prompt |
| `Ctrl-\` | Interactive prompt | Ignored |
| `Ctrl-\` | Running command | Terminates with core dump message |
| `Ctrl-D` | Interactive prompt | Exits the shell (EOF) |
| `Ctrl-D` | Heredoc | Closes heredoc with warning |

</div>

---

## 📁 Project Structure

```
Minishell/
├── 📄 Makefile
├── 📖 README.md
├── includes/
│   └── minishell.h                 # All structs, defines & prototypes
├── libft/                          # Custom C library (libft + ft_printf + GNL)
└── src/
    ├── main.c                      # Entry point & shell loop
    ├── shell_helper.c              # Input & token utilities
    ├── 00_init/                    # Shell & environment initialization
    │   ├── init.c
    │   └── init_helper.c
    ├── 01_frees/                   # Memory cleanup functions
    │   ├── free.c
    │   ├── free_shell.c
    │   ├── free_exit.c
    │   └── free_child.c
    ├── 02_errors/                  # Error message printing
    │   └── print_error.c
    ├── 03_signals/                 # Signal setup & handlers
    │   ├── signal.c
    │   ├── signal_handler.c
    │   └── setget_signo.c
    ├── 04_parsing/                 # Syntax validation
    │   ├── parsing.c
    │   ├── syntax_pipes.c
    │   ├── syntax_quotes.c
    │   ├── syntax_redir.c
    │   └── syntax_error_helper.c
    ├── 05_tokenizer/               # Tokenization engine
    │   ├── tokenizer.c
    │   ├── token_tools.c
    │   ├── 00_handle_spaces/       # Whitespace splitting
    │   ├── 01_handle_expansions/   # $VAR expansion
    │   ├── 02_handle_quote/        # Quote processing
    │   └── 03_add_new_token/       # Token list management
    ├── 06_process/                 # Process node building
    │   ├── process.c
    │   ├── node.c
    │   └── process_helper.c
    ├── 07_heredoc/                 # Heredoc implementation
    │   ├── heredoc.c
    │   ├── init_heredoc.c
    │   └── generate_tempfile_path.c
    ├── 08_executer/                # Command execution engine
    │   ├── executer.c
    │   ├── executer_single.c
    │   ├── executer_pipes.c
    │   ├── executer_pipes2.c
    │   ├── executer_utils.c
    │   ├── redir_exec_handler.c
    │   └── backup_stdio.c
    └── 09_builtin/                 # Built-in command implementations
        ├── cd.c / cd1.c
        ├── echo.c
        ├── env.c
        ├── exit.c
        ├── export.c / export1-3.c
        ├── pwd.c
        ├── unset.c
        └── builtin_utils.c
```

---

## 🛠️ Makefile Targets

| Command | Description |
|:--------|:------------|
| `make` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full recompile |
| `make r` | Build and run minishell |
| `make rv` | Build and run with Valgrind |
| `make renv` | Run with Valgrind without environment |
| `make valgrind` | Run with Valgrind + readline suppression file |

---

## 👥 Authors

**mmiguelo** — 42 Student

[![mmiguelo](https://img.shields.io/badge/GitHub-mmiguelo-181717?style=for-the-badge&logo=github)](https://github.com/mmiguelo)
[![frbranda](https://img.shields.io/badge/frbranda-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/KrispyFbacon)

---

<div align="center">

*Made with ❤️ at 42*

<p>(<a href="#readme-top">⬆️ back to top</a>)</p>

</div>
