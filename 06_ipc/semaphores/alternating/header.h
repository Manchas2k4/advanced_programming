#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int acquire(int semid, int sem_num, unsigned int val) {
	struct sembuf op;

	op.sem_num = sem_num;
	op.sem_op = -val;
	op.sem_flg = 0; // IPC_NOWAIT;
	return semop(semid, &op, 1);
}

int release(int semid, int sem_num, unsigned int val) {
	struct sembuf op;

	op.sem_num = sem_num;
	op.sem_op = +val;
	op.sem_flg = 0;
	return semop(semid, &op, 1);
}

#endif
