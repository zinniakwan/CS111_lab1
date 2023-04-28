#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	if (argc<=1) {
		exit(EINVAL);
	}

	int fdread;
	int fd[2];
	int ret;


	for (int i=1; i < argc; i++){
		if (pipe(fd) == -1) {
			exit(errno); //if pipe operation fails
		}
		ret = fork();

		// printf("forked%d \n", i);
		if (ret<0){
			exit(errno); //fork error
		}
		else if (ret==0){
			//child process
			if (i!=1){
				if (dup2(fdread, STDIN_FILENO)<0) exit(errno); //will automatically close when it's execution ends
				close(fdread);
			}
			if (i!=(argc-1)){
				if (dup2(fd[1], STDOUT_FILENO)<0) exit(errno);
			}
			close(fd[1]);
			close(fd[0]);
			if (execlp(argv[i], argv[i], NULL)==-1) {
				exit(errno);
			}
		}
		else{
			if (i!=1){
				close(fdread);
			}
			close(fd[1]); //need to close the file descriptors
			fdread=fd[0];
		}
		int status=0;
		waitpid(ret, &status, 0);
		if (WEXITSTATUS(status)){
			close (fd[0]);
			return WEXITSTATUS(status);
		}
	}

	close (fd[0]); //clean up open file descriptor
	return 0;








	// int fd1[2];
	// if (pipe(fd1) ==-1) {	
	// 	return 10;
	// }; //create a pipe of two ends
	// int ret1 = fork();

	// if (ret1<0){
	// 	return 1; //error with forking
	// }

	// if (ret1==0){
	// 		//child process
	// 	dup2(fd1[1], STDOUT_FILENO); //will automatically close when it's execution ends
	// 	close(fd1[0]);
	// 	close(fd1[1]); //need to close the file descriptors
	// 	execlp(argv[1], argv[1], NULL);
	// }

	// close(fd1[1]); //need to close the file descriptors

	// int fd2[2];
	// if (pipe(fd2) == -1){
	// 	return 10;
	// }

	// int ret2 = fork();
	// if (ret2<0){
	// 	return 2; //error with forking
	// }

	// if (ret2==0){
	// 		//child process
	// 	int status=0;
	// 	waitpid(ret1, &status, 0);
	// 	dup2(fd1[0], STDIN_FILENO); //will automatically close when it's execution ends
	// 	dup2(fd2[1], STDOUT_FILENO);
	// 	close(fd1[0]);
	// 	close(fd2[1]);
	// 	close(fd2[0]);
	// 	execlp(argv[2], argv[2], NULL);
	// }

	// close(fd1[0]);
	// close(fd2[1]); //need to close the file descriptors


	// int ret3 = fork();
	// if (ret3<0){
	// 	return 3; //error with forking
	// }

	// if (ret3==0){
	// 		//child process
	// 	int status= 0;
	// 	waitpid(ret2, &status, 0);
	// 	dup2(fd2[0], STDIN_FILENO); //will automatically close when it's execution ends
	// 	close(fd2[0]);
	// 	execlp(argv[3], argv[3], NULL);
	// }
	
	// close(fd2[0]); //need to close the file descriptors
	// waitpid(ret3, NULL, 0);
	// return 0;
}
