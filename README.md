UNDERSTANDING SHELL AND THE SIMPLE SHELL PROJECT
GENERAL CONCEPTS
Who designed and implemented the original Unix operating system
The original Unix operating system was designed and implemented by Ken Thompson and Dennis Ritchie at Bell Labs in the late 1960s and early 1970s. Thompson is credited with writing the first version of Unix in assembly language, while Ritchie created the C programming language and used it to rewrite Unix. The two worked together to develop many of the key concepts and tools that would become the foundation of Unix, including the shell, file system, and pipes. Unix has since become one of the most influential operating systems in the world, serving as the basis for many other operating systems, including Linux and macOS.
Who wrote the first version of the UNIX shell
The first version of the Unix shell was written by Ken Thompson, one of the creators of the Unix operating system. The shell, which is a command-line interface that allows users to interact with the operating system, was originally called the "Command Language" or "sh" for short. Thompson created the shell in 1971, as a way to make it easier for users to interact with the Unix system. The original shell had a limited set of commands, but it was designed to be extensible, so that users could add their own commands and features. Over time, the Unix shell has evolved and been replaced by newer shells such as the Bourne-Again shell (bash) and the Z shell (zsh), but the original "sh" shell still exists and is still used in some Unix systems today.

Who invented the B programming language (the direct predecessor to the C programming language)
The B programming language, which was the direct predecessor to the C programming language, was invented by Ken Thompson, one of the creators of the Unix operating system. Thompson created B in the early 1970s while working on the first version of the Unix operating system at Bell Labs. B was based on the BCPL language and was designed to be a simpler and more efficient language that could be used to develop operating systems and other system-level software. The syntax of B was simple and compact, and it included features such as pointers, arrays, and structures. B was eventually replaced by the C programming language, which was also developed by Thompson, and which included additional features such as data types, functions, and a more extensive library of standard functions.
Who is Ken Thompson
Ken Thompson is a computer scientist and programmer who is best known as one of the creators of the Unix operating system, along with Dennis Ritchie. Thompson was born on February 4, 1943, in New Orleans, Louisiana, and he studied electrical engineering at the University of California, Berkeley, where he received his bachelor's and master's degrees.
Thompson worked at Bell Labs for much of his career, where he made many significant contributions to computer science and programming. In addition to his work on Unix, Thompson also invented the B programming language and was one of the co-inventors of the Go programming language. He also contributed to the development of other technologies, such as the Plan 9 operating system and the UTF-8 character encoding.
Thompson has received numerous awards and honors for his contributions to computer science, including the Turing Award in 1983, which is often referred to as the "Nobel Prize of Computing." He is widely regarded as one of the most influential computer scientists of all time, and his work has had a major impact on the development of modern computing.



How does a shell work
A shell is a command-line interface (CLI) that allows users to interact with an operating system (OS). It is a program that takes commands from the user, interprets them, and executes them. The shell is the outermost layer of an OS, and it is responsible for managing and controlling the input and output of other programs that run on the OS.

When a user types a command into the shell, the shell first parses the command into its individual components (such as the command name and its arguments). It then searches for the command in its list of executable programs, either in the system directories or in the directories specified in the PATH environment variable. Once the shell finds the program, it executes it and redirects its input and output as necessary.

The shell also has the ability to execute commands within a shell script, which is a file containing a sequence of commands that the shell can run in order. Shell scripts can be used to automate repetitive tasks or to perform complex operations that require multiple commands.

In addition to executing commands and scripts, the shell also provides features such as command history, tab completion, and shell variables. These features make it easier and more efficient for users to interact with the OS and to perform tasks on the command line.
What is a pid and a ppid
In a Unix-like operating system, every process (running program) is identified by a unique process ID (PID). The PID is a non-negative integer that is assigned to the process by the operating system when it is created. The PID allows the operating system to keep track of the process and to manage its resources, such as memory and CPU time.

The parent process ID (PPID) is the PID of the process that created the current process. When a process is created, it is usually created by another process, and the PPID of the new process is set to the PID of its parent process. This creates a hierarchy of processes, with each process having a parent process (except for the init process, which is the first process created by the operating system and has a PPID of 1).

The PPID is used by the operating system to manage the relationships between processes. For example, when a parent process terminates, the operating system sends a signal to all of its child processes, letting them know that their parent has died. The child processes can then take appropriate action, such as terminating themselves or attaching themselves to another process.

In summary, a PID is a unique identifier assigned to a process by the operating system, and a PPID is the PID of the process that created the current process.

How to manipulate the environment of the current process
 You can set an environment variable in the current shell using the export command. For example, to set the MY_VAR environment variable to the value foo, you can run:

export MY_VAR=foo





You can view the value of an environment variable using the echo command. For example, to view the value of the MY_VAR variable, you can run

echo $MY_VAR

You can unset an environment variable using the unset command. For example, to unset the MY_VAR variable, you can run:

unset MY_VAR
You can modify the value of an environment variable using various text manipulation utilities such as sed, awk, or cut. For example, to replace all occurrences of foo with bar in the value of the MY_VAR variable, you can run:

export MY_VAR=$(echo $MY_VAR | sed 's/foo/bar/g')

What is the difference between a function and a system call
A function and a system call are both mechanisms for performing a task in a program or an operating system, but they differ in several ways.

A function is a piece of code that performs a specific task within a program. It is a block of code that can be called by other parts of the program, and it may or may not return a value. Functions are typically used to break down a program into smaller, more manageable pieces, and to reduce code duplication.

A system call, on the other hand, is a request made by a user-level program to the operating system kernel to perform a privileged task on behalf of the program. System calls are used to interact with the operating system and access its resources, such as files, devices, and network connections. Some common system calls include opening or closing a file, creating a new process, or allocating memory.

Here are some key differences between functions and system calls:
1)Invocation: A function is invoked by a simple function call within the program, while a system call is made using a specific interface provided by the operating system, such as a system call library or a kernel API.
2)Privileges: A function does not require any special privileges to execute, while a system call requires the program to have sufficient permissions to access the requested resource or perform the requested task.
3)Overhead: A function call is typically faster and has lower overhead than a system call, which involves a context switch from user mode to kernel mode and back.
4)Accessibility: Functions are typically defined and implemented within the program itself, while system calls are implemented within the operating system kernel and are not directly accessible or modifiable by user-level programs.
In summary, functions are used for program-internal tasks and are invoked by simple function calls, while system calls are used for privileged tasks and are made using a specific interface provided by the operating system.





How to create processes
Using the fork() system call: The fork() system call creates a new process by duplicating the calling process. After the fork, both the parent and child processes continue to run independently, but with different process IDs. The child process is a duplicate of the parent process, with its own memory space, file descriptors, and execution context.
Using the exec() family of system calls: The exec() system calls replace the current process with a new process, typically a new program to be executed. The exec() system calls load the new program into memory, set up its execution environment, and start its execution from the beginning.

Using the system() function: The system() function allows a program to execute a shell command in a new process. The system() function creates a new shell process and passes the command to be executed as an argument to the shell.








Here's an example of how to use the fork() system call in a C program:
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork(); // create a new process

    if (pid == 0) { // child process
        printf("Hello from child process (PID %d)\n", getpid());
    } else if (pid > 0) { // parent process
        printf("Hello from parent process (PID %d)\n", getpid());
    } else { // error
        printf("Error: fork() failed\n");
        return 1;
    }

    return 0;
}

What are the three prototypes of main
1.int main(): This is the most common prototype and is used when the program does not take any command line arguments. The main() function returns an integer value, which is usually used to indicate the success or failure of the program.

2.int main(int argc, char *argv[]): This prototype is used when the program takes command line arguments. The first argument argc is an integer that specifies the number of command line arguments passed to the program, and the second argument argv[] is an array of strings that contains the actual arguments passed to the program. The main() function returns an integer value.

3.int main(int argc, char *argv[], char *envp[]): This prototype is similar to the second one, but also includes the environment variables passed to the program. The envp[] argument is an array of strings that contains the environment variables passed to the program. The main() function returns an integer value.
It's important to note that the first prototype int main() is equivalent to int main(void), which explicitly indicates that the main() function takes no arguments.




How does the shell use the PATH to find the programs
In Unix-like operating systems, including Linux and macOS, the shell uses the PATH environment variable to locate executable programs.

The PATH variable is a colon-separated list of directories that the shell searches in order when you enter a command. When you type a command in the shell, the shell looks for an executable program with that name in each directory listed in the PATH, in the order specified. If the shell finds an executable program with the same name as the command you entered in one of the directories in the PATH, it executes that program.

For example, if your PATH variable is set to /usr/local/bin:/usr/bin:/bin, and you type the command ls in the shell, the shell will search for an executable program called ls in the following directories, in order:

/usr/local/bin
/usr/bin
/bin
If the shell finds an executable program called ls in the /usr/bin directory, it will execute that program.

If the shell cannot find an executable program with the same name as the command you entered in any of the directories listed in the PATH, it will display an error message such as "command not found".

How to execute another program with the execve system call

How to suspend the execution of a process until one of its children terminates
What is EOF / “end-of-file”?

