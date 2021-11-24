#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#define SHMSIZE 4096
#define SEMNAME "/my_sem"
#define SHMNAME "/my_shm"

void p(sem_t *semd);
void v(sem_t *semd);
void main(int argc, char* argv[]){
	FILE *fp, *copy_fp;
	char *path = argv[1];
	char buf[SHMSIZE];
	int status, shmd, count;
	void *shmaddr;
	pid_t pid;
	sem_t *semd;
	int i, val;
	if((semd = sem_open(SEMNAME, O_CREAT, 0600, 1)) == SEM_FAILED) {
		perror("sem_open failed");
		exit(1);
	}
	sem_getvalue(semd, &val);
	memset(buf, 0, SHMSIZE);
	if ((pid == fork()) == 0) {
		if ((shmd = shm_open(SHMNAME, O_CREAT | O_RDWR, 0666)) == -1) {
			perror("shm_open failed");
			exit(1);
		}
		if (ftruncate(shmd, SHMSIZE) != 0) {
			perror("ftruncate failed");
			exit(1);
		}
		if ((shmaddr = mmap(0, SHMSIZE, PROT_WRITE, MAP_SHARED, shmd, 0)) == MAP_FAILED) {
			perror("mmap failed");
			exit(1);
		}
		if ((fp = fopen(path, "r")) == NULL) {
			perror("fopen");
			exit(1);
		}
		if (mlock(shmaddr, SHMSIZE) != 0) {
			perror("mlock failed");
			exit(1);
		}
		
		p(semd);
		printf("Child Process %d : semaphore in use\n", getpid());
		while (feof(fp) != 0){
			count = fread(buf, sizeof(char), SHMSIZE, fp);
			strcpy((char *)shmaddr, buf);
		}
		v(semd);
		printf("Child Process %d : putting semaphore\n", getpid());
		if (munmap(shmaddr, SHMSIZE) == -1){
			perror("munmap failed");
			exit(1);
		}
		
		fclose(fp);
		close(shmd);
		exit(0);
	}
	else if (pid > 0) {
		pid = wait(&status);
		if ((shmd = shm_open(SHMNAME, O_RDWR, 0666)) == -1) {
			perror("shm_open failed");
			exit(1);
		}
		if(mlock(shmaddr, SHMSIZE) != 0) {
		perror("mmap failed");
		exit(1);
		}
	if(mlock(shmaddr, SHMSIZE) != 0) {
		perror("mlock failed");
		exit(1);
		}	
	strcat(path, "_copy");
	if((copy_fp = fopen(path,"w")) == NULL){
		perror("fopen");
		exit(1);
		}
	p(semd);
	printf("Parent Process %d : somaphore in use \n", getpid());
	fwrite(shmaddr, sizeof(char),SHMSIZE, copy_fp);
	fclose(copy_fp);
	if(munmap(shmaddr, SHMSIZE) == -1) {
		perror("munmap failed");
		exit(1);
		}
		
	printf("Parents Process %d : putting semaphore\n",getpid());
	v(semd);
	close(shmd);
	if(shm_unlink(SHMNAME)== -1){
		perror("shm_unlick failed");
		exit(1);
		}
		if (sem_close(semd) == -1) {
			perror("sen_close failed");
			exit(1);
			}
		}
		else{
			perror("fork Error");
			exit(1);
			}
		}
		
	void p(sem_t *semd){
		int ret;
		if((ret = sem_trywait(semd)) != 0 && errno == EAGAIN)
			sem_wait(semd);
		else if (ret !=0){
			perror("sem_trywait failed");
			exit(1);
			}
		}
		
	void v(sem_t *semd){
		if(sem_post(semd) != 0 ) {
			perror("sem_post failed");\
			exit(1);
		}
	}
			
