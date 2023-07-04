#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex[3];

void* process1(void* arg) {
    printf("** Entered P1\n");

    //Lists all files and directories in the present working directory 
    system("ls -l");

    //signal
    printf("** Exiting P1\n");
    sem_post(&mutex[0]);
}

void* process2(void* arg) {
    printf("** Entered P2\n");

//Lists the currently running processes and their PIDs along with some other information
    system("ps -l");

    //signal
    printf("** Exiting P2\n");
    sem_post(&mutex[1]);
}

void* process3(void* arg) {
    //wait
    sem_wait(&mutex[0]);
    sem_wait(&mutex[1]);

    printf("** Entered P3\n");

//display system status
    system("uptime");

    //signal
    printf("** Exiting P3\n");
    sem_post(&mutex[2]);
    sem_post(&mutex[3]);
}

void* process4(void* arg) {
    //wait
    sem_wait(&mutex[2]);
    printf("** Entered P4\n");

  //Lists files in the present working directory and in sub-directories as well 
    system("ls -R"); //

    printf("** Exiting P4\n");
}

void* process5(void* arg) {
    //wait
    sem_wait(&mutex[3]);
    printf("** Entered P5\n");

    //Shows the usernames of users currently logged in to the current host
    system("users"); 

    printf("** Exiting P5\n");
}

int main() {
    for (int i = 0; i < 4; i++) {
        sem_init(&mutex[i], 0, 0);
    }
    pthread_t t1, t2, t3, t4, t5;
    pthread_create(&t1,NULL,process1,NULL);
    sleep(2);
    pthread_create(&t2,NULL,process2,NULL);
    sleep(2);
    pthread_create(&t3,NULL,process3,NULL);
    sleep(2);
    pthread_create(&t4,NULL,process4,NULL);
    sleep(2);
    pthread_create(&t5,NULL,process5,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);

    for (int i = 0; i < 4; i++) {
        sem_destroy(&mutex[i]);
    }
    return 0;
}
