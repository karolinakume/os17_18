 /* Tests producer/consumer communication with different numbers of threads.
 * Automatic checks only catch severe problems like crashes.
 */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"       

int num_of_producer_threads;
int num_of_consumer_threads;
//int semaphore=1;
//int size;
//int mutex=1;
int count=0;
int count1=0;
int count2=0;
//char array[10];
char str[]="Hello World";
char buffer[10];
//int arg;
struct lock _lock;
struct condition notEmpty;
struct condition notFull;

//static void sema_test_helper (void*);

void producer(void* num_producer);
void consumer(void* num_consumer);

void producer_consumer(unsigned int num_producer, unsigned int num_consumer);

void test_producer_consumer(void)
{
    /*producer_consumer(0, 0);
    producer_consumer(1, 0);
    producer_consumer(0, 1);
    producer_consumer(1, 1);
    producer_consumer(3, 1);                       
    producer_consumer(1, 3);
    producer_consumer(4, 4);
    producer_consumer(7, 2);
    producer_consumer(2, 7);*/
    producer_consumer(7,2);
    pass();
}


void producer_consumer(UNUSED unsigned int num_producer, UNUSED unsigned int num_consumer)
{
            num_of_producer_threads=num_producer;
        num_of_consumer_threads=num_consumer;
        lock_init (&_lock);
        cond_init(&notEmpty);
        cond_init(&notFull);
        int i;
        for (i=0;i<num_of_producer_threads;i++){
       
                char prod[16];

                snprintf(prod, sizeof prod, "prod_%d",i);
                thread_create(prod,PRI_DEFAULT,producer,&i);
        }
       
        int j;
        for (j=0;j<num_of_consumer_threads;j++){
                char cons[16];

                snprintf(cons, sizeof cons, "prod_%d",j);
                thread_create(cons,PRI_DEFAULT,consumer,&j);
       
        }
       
}

void producer(void* num_producer){
                /* P operation */
                lock_acquire(&_lock);
                while (count >= 10) {
                printf("Buffer is full: Wait for it to get empty");
                cond_wait(&notFull, &_lock);
                }
                buffer[count2]=str[count2];
                count2++;
                count++;
                cond_signal(&notEmpty, &_lock);
                lock_release(&_lock);/*Q operation*/
               
}

void consumer(void* num_consumer){
                /* P operation */
                lock_acquire(&_lock);
                while (count <= 0) {
                printf("The buffer is empty");
                cond_wait(&notEmpty, &_lock);               
                    }
                int i;
                for(i=count1;i<sizeof(str);i++)
                buffer[i]=buffer[i+1];
                for(i=count1;i<sizeof(buffer);i++)
                printf("%c",buffer[i]);
                count--;
                cond_signal(&notFull, &_lock);               
                lock_release(&_lock);/*Q operation*/
               
}
