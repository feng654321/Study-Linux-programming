#include <pthread.h>
#include <stdio.h>

int global=0;

void cal(void){
	for(int i=0;i<100000;i++){
		global +=1;
	}
}

void main(void){
	pthread_t pt1,pt2;
	pthread_create(&pt1, NULL, (void *)cal,NULL);
	pthread_create(&pt2, NULL, (void *)cal,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	printf("100000+100000=%d\n",global);
}