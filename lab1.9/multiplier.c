#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define LIST_MAX      2000

pthread_mutex_t *mutexes;
long ** buffers;
int NUM_BUFFERS;
long * result;
long *matB, *matA;
int counter = 0;
typedef struct {
    int row;
    int column;
} arguments;

long * readMatrix(char *filename)
{
    static long matrix[LIST_MAX*LIST_MAX];
    int value, count = 0;
    FILE *file;
    file = fopen(filename,"r");
    printf("%s\n", filename);
    if (file)
    {
        while (fscanf(file, "%d", &value) != EOF)
        {
            matrix[count++] = value;
        }
    }
    fclose(file);
    return matrix;
}

long * getColumn(int col, long *matrix)
{
    static long aux[LIST_MAX];
    int j, i;
    for (i = col, j = 0; j < LIST_MAX; i = i + LIST_MAX, j++)
    {
        aux[j] = matrix[i];
    }
 
    return aux;
}

long * getRow(int row, long *matrix)
{
    static long aux[LIST_MAX];
    int i, j, offset;
    offset = LIST_MAX * row;
    for (i = offset, j = 0; j < LIST_MAX; i++, j++)
    {
        aux[j] = matrix[i];
    }
    return aux;   
}

long dotProduct(long *vec1, long *vec2)
{
    int i;
    long sum = 0;
    for (i = 0; i < LIST_MAX; i++)
    {
        sum += vec1[i] + vec2[i];
    }
    return sum;
}

void *thread_multiply(void *param) 
{
    int status;
    long *column;
    long *row;
    arguments *params = param;
    row=malloc(LIST_MAX*sizeof(long));
    column=malloc(LIST_MAX*sizeof(long));
    memcpy(row, getRow(params->row, matA), LIST_MAX*sizeof(long)); 
    memcpy(column, getColumn(params->column, matB), LIST_MAX*sizeof(long));
    do {
        status = getLock();
    } while(status < 0);
    result[counter++] = dotProduct(row, column);
    releaseLock(status);
}

long *multiply(long *matA, long *matB)
{
    pthread_t tid [LIST_MAX];
    int i, j;
    long * result;
    pthread_attr_t attr;
    long *column;
    long *row;
    pthread_attr_init(&attr);
    arguments args;   
    for (i = 0; i < LIST_MAX    ; i++)
    {
        for (j = 0; j < LIST_MAX; j++)
        {
            args.row = j;
            args.column = i;
            pthread_create(&tid[i],&attr,thread_multiply,(void *)&args);
        }
    }
    return result;
}


int getLock()
{
    int i = 0;
    while (i < NUM_BUFFERS){
        if(pthread_mutex_trylock(&mutexes[i]) == 0){
            return i;
        }
        i++;
    }
    return -1;
}

int releaseLock(int lock)
{
    if(pthread_mutex_unlock(&mutexes[lock]) == 0)
        return 0;
    else
        return -1;
}

int saveResultMatrix(long *result)
{
    FILE *file;
    file = fopen("result.data", "w");
    int i;
    if (file == NULL || file == NULL) 
    {   
        printf("Error! Could not open file\n"); 
        return -1;
    }
    for (i = 0 ; i < LIST_MAX ; i++)
    {
        fprintf(file, "%d\n", result[i]);
    }
    return 0;
}

int main(int argc, char **argv)
{   
    int i;
    if(argc!=2)
    {
        printf("Arguments missing!\n");
        return -1;
    }
    NUM_BUFFERS = (int)argv[1];
    buffers = malloc(NUM_BUFFERS*sizeof(long*)) ;
    mutexes=malloc(NUM_BUFFERS*sizeof(pthread_mutex_t)); 
    matA = readMatrix("matC.dat");
    matB = readMatrix("matD.dat");
    result = multiply(matA, matB);
    if (saveResultMatrix(result)<0)
        printf("file failed!");
}
