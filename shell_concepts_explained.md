# How Real Shells Work: Programs, Commands, and Execution

## Table of Contents
1. [What is a Shell?](#what-is-a-shell)
2. [Commands vs Programs](#commands-vs-programs)
3. [Built-in Commands vs External Programs](#built-in-commands-vs-external-programs)
4. [Command Execution Process](#command-execution-process)
5. [Windows-Specific Considerations](#windows-specific-considerations)
6. [PATH Resolution](#path-resolution)
7. [Process Creation and Management](#process-creation-and-management)
8. [Practical Examples](#practical-examples)

## What is a Shell?

A shell is a command-line interpreter that provides a user interface for accessing an operating system's services. It reads commands from the user, interprets them, and executes them. Shells can be:

- **Interactive**: Accept commands directly from a user via a terminal
- **Non-interactive**: Execute commands from a script file

Common shells include:
- Unix/Linux: bash, zsh, dash, fish
- Windows: cmd.exe, PowerShell

Shells provide features like:
- Command history
- Tab completion
- Variables and scripting capabilities
- Job control (background/foreground processes)
- Input/output redirection
- Pipeline operations

## Commands vs Programs

### Commands
A **command** is an instruction given to the shell to perform a specific action. Commands can be:
- Built-in shell functions (like `cd`, `export`)
- Executable programs (like `ls`, `grep`)
- Shell functions defined by the user
- Aliases for other commands

### Programs
A **program** is an executable file stored on disk that performs a specific function when run. Programs are:
- Standalone executables compiled from source code
- Interpreted scripts (Python, Bash, etc.)
- Binary files that the operating system can execute

The relationship:
- All programs can be commands, but not all commands are programs
- A command is the interface concept, while a program is the implementation

## Built-in Commands vs External Programs

### Built-in Commands
Built-in commands are implemented directly within the shell itself. They:
- Execute faster (no process creation overhead)
- Have direct access to shell internals (variables, functions, etc.)
- Can modify the shell's state (current directory, environment variables)

Examples in bash:
```bash
cd        # Change directory
export    # Set environment variables
alias     # Create command aliases
history   # Show command history
jobs      # List background jobs
```

### External Programs
External programs are separate executable files that the shell runs as child processes. They:
- Require process creation (fork/exec on Unix, CreateProcess on Windows)
- Cannot directly modify the shell's internal state
- Are standalone utilities that communicate through arguments and return codes

Examples:
```bash
/bin/ls       # List directory contents
/usr/bin/grep # Search text
/bin/cat      # Concatenate files
```

Why the distinction?
1. **Performance**: Built-ins avoid process creation overhead
2. **Functionality**: Some operations require shell state modification
3. **Modularity**: External programs can be developed independently

## Command Execution Process

When you type a command in a shell, this is what typically happens:

### 1. Parsing
The shell breaks down the command line into:
- Command name
- Arguments
- Redirections
- Pipelines

Example: `ls -l /home > output.txt`
- Command: `ls`
- Arguments: `-l`, `/home`
- Redirection: `> output.txt`

### 2. Command Lookup
The shell determines what the command refers to by checking in this order:
1. **Aliases**: User-defined shortcuts
2. **Shell reserved words**: Language constructs (`if`, `for`, `while`)
3. **Functions**: User-defined shell functions
4. **Built-in commands**: Commands implemented in the shell
5. **External programs**: Executables in PATH directories

### 3. Execution
Based on the command type:
- **Built-in/functions**: Execute directly in the shell process
- **External programs**: Create a new process to run the program

### 4. Process Management
For external programs:
1. Fork a new process (Unix) or create a new process (Windows)
2. Set up input/output redirection
3. Execute the program in the new process
4. Wait for completion (unless run in background with `&`)

## Windows-Specific Considerations

Windows shells differ significantly from Unix-like systems:

### Command Extensions
Windows cmd.exe supports:
- `.exe`, `.com`, `.bat`, `.cmd` files automatically
- File associations (using `PATHEXT` environment variable)
- Different syntax for many operations

### Process Creation
Instead of fork/exec model:
- Uses `CreateProcess()` API
- No true fork operation
- Different process inheritance model

### Path Separators
- Windows uses backslashes `\` (though forward slashes often work)
- PATH separator is semicolon `;` instead of colon `:`

### Built-in Commands
Windows cmd.exe built-ins include:
```cmd
cd        # Change directory
dir       # List directory (equivalent to ls)
copy      # Copy files (equivalent to cp)
del       # Delete files (equivalent to rm)
set       # Set environment variables
```

### PowerShell Differences
PowerShell treats everything as objects rather than text streams:
- Cmdlets instead of commands
- Object pipelines instead of text pipelines
- Different syntax and concepts

## PATH Resolution

The PATH environment variable contains directories where the shell looks for executable programs.

### Unix/Linux PATH
```bash
# Typical PATH
PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin
```
- Directories separated by colons `:`
- Searched in order from left to right
- Security consideration: Current directory (.) usually not included

### Windows PATH
```cmd
# Typical PATH
PATH=C:\Windows\system32;C:\Windows;C:\Program Files\Git\bin
```
- Directories separated by semicolons `;`
- Case insensitive
- Supports both forward and back slashes

### Resolution Process
1. Check if command contains path separators (`/` or `\`)
   - If yes: Try to execute directly
   - If no: Proceed to PATH lookup
2. For each directory in PATH:
   - Check if `{directory}/{command}` exists and is executable
   - On Windows: Also check with extensions from PATHEXT
3. Return first match or "command not found" error

### PATHEXT (Windows Specific)
Contains executable file extensions:
```
PATHEXT=.COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH;.MSC
```
When looking for `ping`, Windows checks:
- ping.com
- ping.exe
- ping.bat
- ping.cmd
- etc.

## Process Creation and Management

### Unix Process Model
Uses fork/exec pattern:
1. `fork()` creates a copy of the current process
2. Child process calls `exec()` to replace itself with the new program
3. Parent process can wait for child completion or continue independently

```c
// Simplified Unix process creation
pid_t pid = fork();  // Create child process
if (pid == 0) {
    // Child process
    execlp("ls", "ls", NULL);  // Replace with ls command
} else {
    // Parent process
    wait(NULL);  // Wait for child to complete
}
```

### Windows Process Model
Uses CreateProcess API:
```c
// Simplified Windows process creation
STARTUPINFO si;
PROCESS_INFORMATION pi;
CreateProcess(NULL, "ping.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
WaitForSingleObject(pi.hProcess, INFINITE);  // Wait for completion
```

### Process Control
Shells provide job control features:
- Foreground execution (wait for completion)
- Background execution (run concurrently with `&`)
- Process suspension (Ctrl+Z)
- Process resumption (`fg`, `bg`)

## Practical Examples

### Example 1: Simple Command Execution
```bash
$ ls -l /home/user
```
1. Parse: command=`ls`, args=`["-l", "/home/user"]`
2. Lookup: Find `ls` executable in PATH
3. Execute: Create process running `/bin/ls -l /home/user`
4. Wait: Display output when complete

### Example 2: Built-in Command
```bash
$ cd /tmp
```
1. Parse: command=`cd`, args=`["/tmp"]`
2. Lookup: Recognize as built-in command
3. Execute: Call internal chdir() function
4. Complete: Update shell's current directory

### Example 3: Pipeline
```bash
$ ps aux | grep nginx | awk '{print $2}'
```
1. Parse: Three commands connected by pipes
2. Execute: Create three processes with pipes between them
3. Connect: stdout of `ps` → stdin of `grep`; stdout of `grep` → stdin of `awk`
4. Collect: Output from final command displayed

### Example 4: Windows Command
```cmd
C:\> dir *.txt | findstr report
```
1. Parse: `dir` with wildcard, piped to `findstr`
2. Lookup: `dir` is built-in, `findstr` is external program
3. Execute: Run `dir` internally, create process for `findstr.exe`
4. Connect: Pipe output between commands
5. Display: Final results shown

### Example 5: PATH Resolution
When you type `python`:
1. Check current directory for `python`
2. Check each PATH directory:
   - `/usr/local/bin/python`? No
   - `/usr/bin/python`? Yes → Execute this
3. Run `/usr/bin/python` as new process

This explains why you can run `git` anywhere but not `./my_script.sh` without `./` prefix.

## Conclusion

Understanding how shells work helps you:
- Write more efficient scripts
- Debug command execution issues
- Understand performance implications
- Appreciate cross-platform differences

Key takeaways:
- Commands are interfaces; programs are implementations
- Built-ins are fast but limited; externals are powerful but slower
- PATH resolution follows predictable patterns
- Process models differ between Unix and Windows
- Shells orchestrate complex interactions between processes

Whether you're using bash on Linux, cmd.exe on Windows, or working on your own C++ shell implementation, these fundamental concepts remain the same.