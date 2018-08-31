#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

struct taskFCFS {
   int id;  
   int time; 
};

int front = 0;
int rear = -1;
int itemCount = 0;
int pid = 0;
int lastwritten = 0;

struct taskFCFS queue_tasks[MAX];

struct taskFCFS peek() {
   return queue_tasks[front];
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}  

struct taskFCFS insert() {
    struct taskFCFS task;
    task.id = pid;
    task.time = rand() % 1024;
    if(!isFull()) {
    
      if(rear == MAX-1) {
         rear = -1;            
     }       
     queue_tasks[++rear] = task;
     itemCount++;
     pid++;
    }
    return task;
}

struct taskFCFS removeData() {
   struct taskFCFS data = queue_tasks[front++];
    
   if(front == MAX) {
      front = 0;
   }
   itemCount--;
   return data;  
}

int main()
{
    int input;
    char *exit_flag;
    struct taskFCFS t;
    int d = 0;
    printf("MENU: 1.- FCFS, 2.- SJF, 3.- PQ, 4.- RR");   
    do {
        scanf("%d", &input);
        switch(input){
        case 1:
            printf("values inserted! \n");
            for (d ; d < 10 ; d++) {
                t = insert();
                printf("pid: %d\n", t.id);
                printf("time: %d\n", t.time);
            }
            printf("values removed! \n");
            d = 0;
            for (d ; d < 10 ; d++) { 
                t = removeData();
                printf("pid: %d\n", t.id);
                printf("time: %d\n", t.time);
            }
            exit(0);
            break;
        case 2:
            break;
        case 3:
            
            break;
        case 4:
            break;
        }
    } while (0);
    return 0;
}
