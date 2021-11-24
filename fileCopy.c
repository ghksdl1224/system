	if(mlock(shmaddr, SHMSIZE) != 0) {
		perror("mlock failed");
		exit(1);
		}
	strcat(path, "_copy");
	if((copy_fp = fopen(path,"w")) == NULL){
		perror("fopen");
		exit(1);
		}
	p(send);
	printf("Parent Process %d : somaphore in use \n". gitpid());
	fwite(shmaddr, sizeog(char),SHMSIZE, copy_fp);
	fclose(copy_fp);
	if(munmap(shmaddr, SHMSIZE) == -1) {
		perror("munmap failed");
		exit(1);
		}
	printf("Parents Process %d : putting semaphore\n",getid());
	v(send);
	close(shmd);
	if(shm_unlink(SHMNAME)== -1){
		perror("shm_unlick failed");
		exit(1);
		}
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
			exit(1);
			}
		}
		
	void v(sem_t *send){
		if(sem_post(semd) != 0 ) {
			perror("sem_post failed");\
			exit(1);
			}
		
