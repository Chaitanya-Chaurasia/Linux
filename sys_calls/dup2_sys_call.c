// dup2() is a syscall in C that enables the user to duplicate a file descriptor
// A file descriptor is a unique integer assigned to any open file/I/O stream. 
// This could be a pipe, socket, or terminal—within that process’s context.
//  the kernel allocates an entry in the process’s file‐descriptor table and returns its index to the application.
// Example syntax of dup2() to redirect a program's output to a log.txt file:

int fd = open("log.txt", O_WRONLY|O_CREAT, 0644);
dup2(fd, STDOUT_FILENO);  // now printf() goes to log.txt
