#include <unistd.h>
#include <sys/wait.h>

// Based on: https://www.youtube.com/watch?v=u2Juz5sQyYQ

int real_waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options, void*);

int main () {
	char command[255];
	
	for(;;) {
        write(STDOUT_FILENO, "# ", 2);
        int count = read(STDIN_FILENO, command, 255);
        command[count -1] = 0; // replace's the enter's \n by a \0 (null terminator) so it marks the end of string
        
        pid_t fork_result = fork();
        if (fork_result == 0) {
            execve(command, 0, 0);
            break; // If something fails in the execve, just return the process
        } else {
            siginfo_t info;
            real_waitid(P_ALL, 0, &info, WEXITED, 0);
        }
    }

   _exit(0); // Not using c library anymore, so we need to manually exit 
}
