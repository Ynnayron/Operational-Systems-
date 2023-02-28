#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N          5
#define LEFT       (i + N-1) % N
#define RIGHT      (i + 1) % N
#define THINKING   0
#define HUNGRY     1
#define EATING     2

typedef sem_t semaphore;
int up(sem_t *mutex) { return sem_post(mutex);}
int down(sem_t *mutex) { return sem_wait(mutex);}

int phili[N] = { 0, 1, 2, 3, 4 };
int state[N];
semaphore mutex;
semaphore S[N];

void* philosopher(void* num) {

	while (1) {
		int* i = num;
		sleep(1);
		take_fork(*i);
		sleep(0);
		put_fork(*i);
	}
}

void take_fork(int i) {

	down(&mutex);
	state[i] = HUNGRY;
	printf("Philosopher %d is hungry\n", i + 1);
	test(i); 
	up(&mutex);
	down(&S[i]); 
	sleep(1);
}

void put_fork(int i) {

	down(&mutex);
	state[i] = THINKING;
	printf("Philosopher %d putting forks %d and %d on the table\n", i + 1, LEFT + 1, i + 1);
	printf("Philosopher %d is thinking\n", i + 1);
	test(LEFT);
	test(RIGHT);
	up(&mutex);
}

void test(int i) {

	if (state[i] == HUNGRY && state[LEFT] != EATING	&& state[RIGHT] != EATING) {

		state[i] = EATING;
		sleep(2);
		printf("Philosopher %d took the forks %d and %d\n",	i + 1, LEFT + 1, i + 1);
		printf("Philospher %d is eating\n", i + 1);
		up(&S[i]);
	}
}

int main() {

	int i;
	pthread_t thread_id[N];
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++) sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {
		pthread_create(&thread_id[i], NULL,	philosopher, &phili[i]);
		printf("Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++) pthread_join(thread_id[i], NULL);
}
