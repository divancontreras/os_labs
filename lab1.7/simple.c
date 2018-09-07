#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

// FCFS IMPLEMENTATION

struct {
    int id;  
    int burstTime; 
    int priority;
    int arrivalTime;
    int rtime;
} typedef Process;

int front_fcfs = 0;
int rear_fcfs = -1;
int itemCount_fcfs = 0;
int pid_fcfs = 0;

Process queue_process_fcfs[MAX];


Process insert_fcfs() {
    Process process;
    process.id = pid_fcfs;
    process.burstTime = rand() % 1024;
    if(itemCount_fcfs != MAX) {
    
      if(rear_fcfs == MAX-1) {
         rear_fcfs = -1;            
     }       
     queue_process_fcfs[++rear_fcfs] = process;
     itemCount_fcfs++;
     pid_fcfs++;
    }
    return process;
}

Process remove_fcfs() {
    Process data = queue_process_fcfs[front_fcfs++];
    if(front_fcfs == MAX) {
        front_fcfs = 0; 
    }
    itemCount_fcfs--;
    return data;
}

void print_fcfs() {
    int x;
    Process aux;
    if (itemCount_fcfs == 0)
        printf("The queue is empty! \n");
    for (x = 0; x < itemCount_fcfs; x++){
        aux = queue_process_fcfs[x];
        printf("pid_fcfs: %d, burstTime %d\n", aux.id, aux.burstTime);
    }
}

void simulation_fcfs() {
    int d;
    Process p;
    printf("Adding 10 process!\n");
    for (d = 0; d < 10; d++){
        p = insert_fcfs();
        printf("pid_fcfs: %d, burstTime %d\n", p.id, p.burstTime);
    }
    printf("Removing 10 process!\n");
    for (d = 0; d < 10; d++){
        p = remove_fcfs();
        printf("pid_fcfs: %d, burstTime %d\n", p.id, p.burstTime);
    }

}

void test_FCFS() {
    Process t;
    int input;
    do {
        printf("MENU FCFS: \n 1.- simulation\n 2.- add\n 3.- remove \n 4.- print \n 5.- Exit \n");   
        printf(">> ");
        scanf("%d", &input);
        switch(input){
            case 1:
                simulation_fcfs();
                break; 
            case 2:
                insert_fcfs();
                break;
            case 3:
                remove_fcfs();
                break;
            case 4:
                print_fcfs();
                break;
            case 5:
                return;
                break;
        }
    } while (input != 5);
}


/////////// Implementing Prioirty Scheduling ////////////////

int pid_priority = 0;

typedef struct {
    Process *nodes;
    int len;
    int size;
} heap_t;

void push (heap_t *h) {
    int priority = rand() % 100;
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (Process *)realloc(h->nodes, h->size * sizeof (Process));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    int bt = rand() % 1024;
    h->nodes[i].priority = priority;
    h->nodes[i].id = pid_priority;
    h->nodes[i].burstTime = bt;
    h->len++;
    printf("Adding: pid: %d, priority: %d, bt: %d \n", pid_priority, priority, bt);
    pid_priority++;
}
 
void *pop (heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }

    int pid = h->nodes[1].id;
    int bt = h->nodes[1].burstTime;
    int priority = h->nodes[1].priority;
 
    h->nodes[1] = h->nodes[h->len];
 
    h->len--;
 
    i = 1;
    while (i!=h->len+1) {
        k = h->len+1;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority < h->nodes[k].priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    printf("Removing: pid: %d, priority: %d, bt: %d \n", pid, priority, bt);
}

void simulation_Priority() {
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    int d;
    for (d = 0; d < 10; d ++) {
        push(h);
    }
    for (d = 0; d < 10; d ++) {
        pop(h);
    }
}

void test_Priority() {
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    Process t;
    int input;
    do {
        printf("MENU PQ: \n 1.- simulation\n 4.- Exit \n");
        printf(">> ");
        scanf("%d", &input);
        switch(input){
            case 1:
                simulation_Priority();
                break;
            case 4:
                return;
        }
    } while (input != 5);
}



//////// SHORTEST-JOB-FIRST /////////////////

int pid_sjf = 0;

void push_sjf (heap_t *h) {
    int priority = rand() % 100;
    int bt = rand() % 1024;
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (Process *)realloc(h->nodes, h->size * sizeof (Process));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].burstTime > bt) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].id = pid_sjf;
    h->nodes[i].burstTime = bt;
    h->len++;
    printf("Adding: pid: %d, priority: %d, bt: %d \n", pid_sjf, priority, bt);
    pid_sjf++;
}
 
void *pop_sjf (heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }

    int pid = h->nodes[1].id;
    int bt = h->nodes[1].burstTime;
    int priority = h->nodes[1].priority;
 
    h->nodes[1] = h->nodes[h->len];
 
    h->len--;
 
    i = 1;
    while (i!=h->len+1) {
        k = h->len+1;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].burstTime < h->nodes[k].burstTime) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].burstTime < h->nodes[k].burstTime) {
            k = j + 1;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    printf("Removing: pid: %d, priority: %d, bt: %d \n", pid, priority, bt);
}

void simulation_Sjf() {
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    int d;
    for (d = 0; d < 10; d ++) {
        push_sjf(h);
    }
    for (d = 0; d < 10; d ++) {
        pop_sjf(h);
    }
}

void test_SJF() {
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    Process t;
    int input;
    do {
        printf("MENU SJF: \n 1.- simulation\n 4.- Exit \n");
        printf(">> ");
        scanf("%d", &input);
        switch(input){
            case 1:
                simulation_Sjf();
                break;
            case 4:
                return;
        }
    } while (input != 5);
}



////////// ROUND ROBING IMPLMENTATION //////////////

Process queue_process_rr[MAX];

int itemCount_rr = 0;
int pid_rr = 0;

void insert_rr() {
    Process aux;
    aux.id = pid_rr;
    int at = rand()%50;
    int bt = rand()%50;
    aux.burstTime = bt;
    aux.arrivalTime = at;
    aux.rtime = aux.burstTime;
    queue_process_rr[itemCount_rr] = aux;
    itemCount_rr++;
    pid_rr++;
    printf("Adding: pid: %d, burst time: %d, arrival time: %d \n", pid_rr, bt, at); 
}

void remove_rr() {
    int i, total;
    int time_quantum = rand() % 20;
    int counter=0;
    int it_count=0;
    int tournaround = 0;
    int limit = MAX;
    Process aux;
    for(total = 0, i = 0; i < limit;) {
        if (it_count == itemCount_rr)
            return;
        aux = queue_process_rr[i];
        if (aux.rtime <= time_quantum && aux.rtime > 0) {
            total = total + aux.rtime;
            aux.rtime = 0;
            counter = 1;
        } else if (aux.rtime > 0) {
            aux.rtime = aux.rtime - time_quantum;
            total = total + time_quantum;
        }
        if (aux.rtime == 0 && counter == 1) {
            it_count++;
            limit--;
            tournaround = tournaround + total - aux.arrivalTime;
            printf("Removing: pid: %d, burst time: %d, turnaround time: %d, waiting time: %d\n",aux.id, aux.burstTime, total - aux.arrivalTime, tournaround); 
            counter = 0;
        }
        if (i == itemCount_rr - 1) {
            i = 0;
        } else if (queue_process_rr[i+1].arrivalTime <= total) {
            i++;
        } else {
            i = 0;
        }
    }   
}

void simulation_RR() {
    int i;
    for (i=0 ; i < 10 ; i++) {
        insert_rr(); 
    }
    remove_rr();
    
}


void test_RR() {
    int input;
    do {
        printf("MENU SJF: \n 1.- simulation\n 4.- Exit \n");
        printf(">> ");
        scanf("%d", &input);
        switch(input){
            case 1:
                simulation_RR();
                break;
            case 4:
                return;
        }
    } while (input != 5);   
}


int main()
{
    int input;
    do {
        printf("MENU:\n 1.- FCFS\n 2.- SJF \n 3.- PQ \n 4.- RR \n 5.- Exit \n");   
        printf(">> ");
        scanf("%d", &input);
        switch(input){
        case 1:
            test_FCFS();
            break;
        case 2:
            test_SJF(); 
            break;
        case 3:
            test_Priority();
            break;
        case 4:
            test_RR();
            break;
        case 5:
            exit(0);
            break;
        }
    } while (1);
    return 0;
}
