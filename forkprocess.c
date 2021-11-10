/* forkprocess.c */
/* fork example */
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
 int main()
 {
	jomvi();
 }
 void creat(){
 	pid_t pid; /* 부모에서 프로세스 식별번호 저장 */

	printf("Calling fork \n");
	pid = fork(); /* 새로운 프로세스 생성 */
	if (pid == 0)
		printf("I'm the child process\n");
	else if (pid > 0)
	printf("I'm the parent process\n");
	else
		printf("fork failed\n");
 }
 void by(){
 	int exit_status;
	printf("enter exit status: ");
	scanf("%d", &exit_status);
	exit(exit_status);

 }
 void wai(){
/* waitprocess.c */
/* wait example */

	pid_t pid;
	int status, exit_status;
	if ((pid = fork()) < 0)
 		perror ("fork failed");
 	if (pid == 0) {
		sleep(4); /* 수행을 4초 동안 중단 */
 	exit(5);
 	}

 /* 부모 코드: 자식이 퇴장(exit)할 때까지 대기 */
	 if ((pid = wait(&status)) == -1) {

 		perror("wait failed");

		 exit(2);
 		}
	 if (WIFEXITED(status)) {
 		exit_status = WEXITSTATUS(status);
 		printf("Exit status from %d was %d\n", pid, exit_status);
 	}
 	exit(0);
 }
void jomvi(){
	pid_t pid;
	if ((pid = fork()) < 0) {
	perror("folk");
	exit(1);
	 }
	else if (pid == 0) /* child */
		exit(0);
 /* parent */
		sleep(4);
		system("ps -o pid,ppid,state,tty,command");
		exit(0);
}
 
