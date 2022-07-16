#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#define MAXSIZE 32

int a[MAXSIZE];
int key = 0;
int ind = -1;
int found = -1;
long foundid;


void * search(void * args)
{

	int keytemp = (int)args;

	if (found == -1) {
		if (a[keytemp] == key) {
			ind = keytemp;
			foundid = (long)pthread_self();
			found = 1;
		}
	}

	pthread_exit(NULL);
}

int main()
{
	for (int i = 0; i < MAXSIZE; i++)a[i] = i;

	printf("Key : ");
	scanf("%d", &key);
	pthread_t thread[MAXSIZE];


	int threadcount = 0;



	for (int i = 0 ; i < MAXSIZE; i++) {
		threadcount++;
		pthread_create(&thread[i], NULL,  search, i);
		printf("Thread %d : %ld\n", i, thread[i]);
	}

	printf("%d\n", threadcount);

	for (int i = 0 ; i < threadcount; i++) {
		pthread_join(thread[i], NULL);
	}


	if (ind != -1) {
		printf( "KEY FOUND at position: %d by thread: %ld \n", ind + 1, foundid);
	}
	else {
		printf( "KEY NOT FOUND \n" );
	}
	return 0;
}

// Time Complexity of A : O(N)
// Space Complexity of A : O(N)

// Time Complexity of B : O(N)
// each thread is only O(1), but creating N threads take O(N)
// Space Complexity is O(N)