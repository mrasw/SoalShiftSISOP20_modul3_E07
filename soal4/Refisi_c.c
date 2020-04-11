#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() {
	
	// untuk menyimpan pipe
    int fds[2];
    pipe(fds);

    if (pipe(fds)==-1) 
	{ 
		fprintf(stderr, "Pipe Failed" ); 
		return 1; 
	} 

    pid_t pid = fork();

    if(pid < 0 ) {
        perror("fork error");
    }

	// proses anak berhasil dibuat
    else if(pid==0) {
        close(1); //close std output child fd
        dup(fds[1]); // write input to pipe
        close(fds[0]); // close pipe
        execlp("/bin/ls","ls",NULL);
    }
    
    // parent process
    else {
        close(0); // close stdin fd parent
        dup(fds[0]); // read output dri pipe
        close(fds[1]); // close write pipe
        execlp("/usr/bin/wc","wc","-l",NULL); // count file & folder dari ls child
    }
}
