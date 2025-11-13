# 🚀 Minishell

![Status](https://img.shields.io/badge/status-Completed-blue)
![Language](https://img.shields.io/badge/language-C-orange)
![License](https://img.shields.io/badge/license-GPL--3.0-green)
![Last update](https://img.shields.io/github/last-commit/Alelith/minishell)

---

## 🧠 Description

Minishell is a lightweight UNIX shell implementation developed as part of the 42 School curriculum. It provides core shell functionality including command execution, piping, I/O redirection, environment variable management, and built-in commands. This project demonstrates low-level system programming, process management, and parser design principles.

---

## 🧩 Table of Contents

- [Description](#-description)
- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Architecture](#-architecture)
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [Execution](#-execution)
- [Usage Examples](#-usage-examples)
- [Documentation](#-documentation)
- [Learnings & Future Improvements](#-learnings--future-improvements)
- [Contributing](#-contributing)
- [Credits](#-credits)
- [License](#-license)
- [Author](#-author)

---

## 🌟 Features

-   [x] Interactive command line with readline support
-   [x] Command execution with PATH resolution
-   [x] Piping between multiple commands (|)
-   [x] Input/Output redirection (<, >, >>)
-   [x] Heredoc implementation (<<)
-   [x] Environment variable management
-   [x] Variable expansion ($VAR)
-   [x] Built-in commands (echo, cd, pwd, export, unset, env, exit)
-   [x] Signal handling (Ctrl-C, Ctrl-D, Ctrl-\\)
-   [x] Quote handling (single and double quotes)
-   [x] Command history
-   [x] Exit status tracking ($?)

---

## ⚙️ Technologies Used

**Languages:** C\
**Libraries:** GNU Readline, Custom Survival Library\
**System Calls:** fork, execve, pipe, dup2, wait, signal, stat\
**Tools:** Git, Make, GCC, Doxygen\
**Standards:** POSIX, 42 School Norminette

---

## 🏗️ Architecture

-   **Architecture Pattern:** Modular layered architecture with clear separation of concerns
-   **Parser:** Tokenization and command structure generation with quote and variable expansion
-   **Executor:** Fork/exec model with built-in command detection
-   **Environment:** Linked list-based environment variable storage
-   **Signal Management:** Custom signal handlers for interactive shell behavior

``` mermaid
flowchart TD
    A[User Input] --> B[Readline]
    B --> C[Tokenizer]
    C --> D[Parser]
    D --> E{Command Type?}
    E -->|Built-in| F[Built-in Executor]
    E -->|External| G[Fork + Execve]
    F --> H[Environment Manager]
    G --> H
    H --> I[Signal Handler]
    I --> J[Output]
    J --> A
```

---

## 📂 Project Structure

```
/minishell
 ├── include/
 │   ├── minishell.h          # Main header with data structures and function prototypes
 │   └── survival_lib.h       # Custom utility library header
 ├── lib/
 │   └── survivalib.a         # Precompiled utility library
 ├── src/
 │   ├── main.c               # Entry point and shell initialization
 │   ├── command_utils/       # Pipeline and process management utilities
 │   │   ├── utils1.c         # Command routing and pipe management
 │   │   ├── utils2.c         # Fork execution and built-in detection
 │   │   └── utils3.c         # Process cleanup and pipeline finalization
 │   ├── environment_vars/    # Environment variable management
 │   │   ├── add_env.c        # Add new environment variables
 │   │   ├── delete_env.c     # Remove environment variables
 │   │   ├── dict_utils.c     # Key-value manipulation
 │   │   ├── env_to_string_list.c  # Convert env list to string array
 │   │   ├── exists_env.c     # Check variable existence
 │   │   ├── free_env.c       # Memory cleanup for env list
 │   │   ├── search_env.c     # Query environment variables
 │   │   ├── set_env.c        # Initialize environment from system
 │   │   └── update_env.c     # Modify existing variables
 │   ├── execution/           # Command execution and built-ins
 │   │   ├── cd.c             # Change directory built-in
 │   │   ├── echo.c           # Echo built-in with -n flag support
 │   │   ├── env.c            # Environment display built-in
 │   │   ├── execute.c        # External command execution
 │   │   ├── exit.c           # Exit built-in with status code
 │   │   ├── export.c         # Export built-in for env variables
 │   │   ├── pwd.c            # Print working directory built-in
 │   │   ├── signals.c        # Signal handler configuration
 │   │   ├── try_command.c    # Main command execution dispatcher
 │   │   └── unset.c          # Unset built-in for env removal
 │   ├── parsing/             # Command line parsing and tokenization
 │   │   ├── checker.c        # Command line validation
 │   │   ├── tokenizer.c      # Main tokenization logic
 │   │   ├── tokenizer_command.c  # Command token processing
 │   │   ├── tokenizer_redir.c    # Redirection token processing
 │   │   └── tokenizer_utils.c    # Parsing helper functions
 │   ├── print/               # Output formatting
 │   │   ├── banner.c         # Welcome/exit banner display
 │   │   └── export_vars.c    # Export command output formatting
 │   ├── split_utils/         # String manipulation utilities
 │   │   ├── utils1.c         # Token splitting and extraction
 │   │   └── utils2.c         # Quote and escape handling
 │   └── utils/               # General utility functions
 │       ├── any_has_error.c  # Error checking across commands
 │       ├── free_commands.c  # Command structure cleanup
 │       ├── get_last_path.c  # Path manipulation
 │       ├── handle_heredoc.c # Heredoc input processing
 │       ├── is_builtin.c     # Built-in command detection
 │       ├── is_redirection.c # Redirection character detection
 │       ├── pipes_utils.c    # Pipe management utilities
 │       ├── search_command.c # PATH resolution for commands
 │       └── split_command.c  # Command line splitting
 ├── Makefile                 # Build system configuration
 ├── Doxyfile                 # Doxygen documentation configuration
 ├── LICENSE                  # GPL-3.0 license file
 └── README.md                # This file
```

---

## 📦 Installation

### Prerequisites

Before you begin, ensure you have the following installed:

-   **GCC** version 4.8 or higher
-   **GNU Make**
-   **GNU Readline** library and development headers
-   **Git**

On Debian/Ubuntu systems:
``` bash
sudo apt-get install build-essential libreadline-dev
```

On macOS:
``` bash
brew install readline
```

### Steps

Clone the repository:
``` bash
git clone https://github.com/Alelith/minishell.git
cd minishell
```

Build the project:
``` bash
make
```

The compilation will create the `minishell` executable in the project root directory.

---

## ▶️ Execution

### Local

Run the shell:
``` bash
./minishell
```

You will see a welcome banner and the interactive prompt:
```
minishell~>
```

To exit the shell, use:
- The `exit` command
- Ctrl-D (EOF)

### Cleaning

To remove object files:
``` bash
make clean
```

To remove all compiled files including the executable:
``` bash
make fclean
```

To rebuild from scratch:
``` bash
make re
```

---

## 🧪 Usage Examples

### Basic Commands

Execute external commands:
``` bash
minishell~> ls -la
minishell~> cat file.txt
minishell~> /bin/echo "Hello World"
```

### Built-in Commands

**Echo** with -n flag:
``` bash
minishell~> echo "Hello, Minishell!"
Hello, Minishell!
minishell~> echo -n "No newline"
No newline minishell~>
```

**Change directory:**
``` bash
minishell~> pwd
/home/user/projects/minishell
minishell~> cd ..
minishell~> pwd
/home/user/projects
minishell~> cd -
/home/user/projects/minishell
```

**Environment variables:**
``` bash
minishell~> export MY_VAR="test value"
minishell~> echo $MY_VAR
test value
minishell~> env | grep MY_VAR
MY_VAR=test value
minishell~> unset MY_VAR
```

### Piping

Chain multiple commands:
``` bash
minishell~> ls -l | grep ".c" | wc -l
minishell~> cat file.txt | grep "pattern" | sort | uniq
```

### Redirections

**Input redirection:**
``` bash
minishell~> wc -l < input.txt
```

**Output redirection (truncate):**
``` bash
minishell~> echo "New content" > output.txt
```

**Output redirection (append):**
``` bash
minishell~> echo "Additional line" >> output.txt
```

**Heredoc:**
``` bash
minishell~> cat << EOF
> Line 1
> Line 2
> EOF
Line 1
Line 2
```

### Complex Pipeline Example

``` bash
minishell~> cat /etc/passwd | grep "root" | cut -d: -f1,7 | sort > users.txt
```

### Quote Handling

``` bash
minishell~> echo 'Single quotes: $HOME'
Single quotes: $HOME
minishell~> echo "Double quotes: $HOME"
Double quotes: /home/user
```

### Exit Status

``` bash
minishell~> ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
minishell~> echo $?
2
minishell~> ls
file1.txt file2.txt
minishell~> echo $?
0
```

---

## 📖 Documentation

The complete code documentation is generated with Doxygen and includes:
- Detailed function descriptions and parameter documentation
- Module organization (Parsing, Execution, Environment, Utils)
- Data structure definitions with member documentation
- Code examples and usage patterns
- Architecture overview and design decisions

To generate the documentation locally:
```bash
doxygen Doxyfile
```

The documentation will be generated in the `docs/` directory. Open `docs/html/index.html` in your browser to view it.

The documentation includes:
- Complete API reference for all modules
- Detailed descriptions of data structures (t_command, t_env, t_shell, etc.)
- Function call graphs and dependency diagrams
- Source code cross-references
- Module groupings for easy navigation

---

## 🧭 Learnings & Future Improvements

### Key Learnings

- **Process Management:** Deep understanding of fork/exec model and inter-process communication
- **Parser Design:** Implementing a robust tokenizer with quote handling and variable expansion
- **Signal Handling:** Managing UNIX signals in an interactive application
- **Memory Management:** Careful resource allocation and deallocation in C
- **System Programming:** Extensive use of POSIX system calls and file descriptors

### Challenges Overcome

- Proper pipe file descriptor management in multi-command pipelines
- Quote parsing with nested quotes and escape sequences
- Environment variable expansion with special cases ($?, $PATH)
- Signal handling to mimic bash behavior (Ctrl-C, Ctrl-D, Ctrl-\\)
- Heredoc implementation with variable expansion

### Future Improvements

- Implement logical operators (&& and ||)
- Add wildcard expansion (globbing) support
- Implement subshells with parentheses
- Add job control (background processes with &)
- Improve error messages and diagnostics
- Add command line editing features (Ctrl-A, Ctrl-E, etc.)
- Implement alias support
- Add configuration file support (.minishellrc)

---

## 🤝 Contributing

Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

1. **Fork** the repository
2. **Create** a new branch (`git checkout -b feature/YourFeature`)
3. **Commit** your changes (`git commit -m 'Add some feature'`)
4. **Push** to the branch (`git push origin feature/YourFeature`)
5. **Open** a Pull Request

Please make sure to:
- Follow the 42 School Norminette coding style
- Write clear commit messages
- Test your changes thoroughly
- Update documentation as needed
- Ensure no memory leaks (use valgrind)

---

## 🤝 Credits

-   **42 School** for the project specification and curriculum
-   **GNU Readline** library for interactive input functionality
-   **Bash documentation** for reference implementation behavior
-   **The Linux Programming Interface** (Michael Kerrisk) for POSIX system programming concepts

---

## 📜 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

This license allows you to:
- Use the code for any purpose
- Study and modify the source code
- Share the original or modified code

Under the conditions that:
- Source code must be made available when distributing
- Modifications must be released under the same license
- Changes made to the code must be documented

---

## 👩‍💻 Author

**Lilith Estévez Boeta**  
💻 Backend & Multiplatform Developer  
📍 Málaga, Spain

🔗 [GitHub](https://github.com/Alelith) | [LinkedIn](https://www.linkedin.com/in/alelith/)

**Begoña Varea Kuhn**  
💻 Software Developer  
📍 Málaga, Spain

🔗 [GitHub](hhttps://github.com/bvarea-k)

---

<p align="center">
  <b>⭐ If you like this project, don't forget to leave a star on GitHub ⭐</b>
</p>
