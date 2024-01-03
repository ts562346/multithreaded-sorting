#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *sorter (void *params); /* thread that performs basic sorting algorithm */
void *merger (void *params); /* thread that performs merging of results */

int unsortedList[500];
int sortedList[500];

typedef struct {
    int start_index;
    int end_index;
}parameters;

int main (int argc, const char *argv[]){

    FILE *file;
    char filename[] = "IntegerList.txt";
    char line[1000];

    file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int i = 0; // Number of integers read
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        while (token != NULL) {
            int num = atoi(token); // Convert the token to an integer
            unsortedList[i] = num; // Store the integer
            i++;

            token = strtok(NULL, ","); // Get the next token
        }
    }

    /* create the first sorting thread */
    parameters *data = (parameters *) malloc(sizeof (parameters));
    data->start_index = 0;
    data->end_index = i/2;

    pthread_t tid;
    pthread_create(&tid, NULL, sorter, data);

    /* create the second sorting thread */
    parameters *data2 = (parameters *) malloc(sizeof (parameters));
    data2->start_index = i/2;
    data2->end_index = i;

    pthread_t tid2;
    pthread_create(&tid2, NULL, sorter, data2);

    /* now wait for the 2 sorting threads to finish */
    pthread_join (tid, NULL);
    pthread_join(tid2, NULL);

    /* create the merge thread */
    parameters *data3 = (parameters *) malloc(sizeof (parameters));
    data3->start_index = 0;
    data3->end_index = i;

    pthread_t tid3;
    pthread_create(&tid3, NULL, merger, data3);

    /* wait for the merge thread to finish */
    pthread_join(tid3, NULL);

    /* output the sorted array */
    FILE *outputFile = fopen("SortedIntegerList.txt", "w");

    for (int k = 0; k < i; k++) {
        fprintf(outputFile, "%d", sortedList[k]);
        // printf("%d", sortedList[k]); // for printing to console

        // Add a comma if it's not the last number
        if (k < i - 1) {
            fprintf(outputFile, ",");
            // printf(","); 
        }
    }

    // printf("\n");

    return 0;
}

int compare (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

void *sorter (void *params){
    /* sorting algorithm implementation */
    parameters *param = (parameters *)params;
    qsort(&unsortedList[param->start_index],
          param->end_index - param->start_index,
          sizeof(int),
          compare);
}

void *merger (void *params){
    /* merging algorithm implementation */
    parameters *param = (parameters *)params;

    // Merge the sorted portions into the sortedList
    int i = param->start_index;
    int j = (param->start_index + param->end_index) / 2;
    int k = param->start_index;

    while (i < j && j < param->end_index) {
        if (unsortedList[i] < unsortedList[j]) {
            sortedList[k++] = unsortedList[i++];
        } else {
            sortedList[k++] = unsortedList[j++];
        }
    }

    // Copy any remaining elements from the left portion
    while (i < j) {
        sortedList[k++] = unsortedList[i++];
    }

    // Copy any remaining elements from the right portion
    while (j < param->end_index) {
        sortedList[k++] = unsortedList[j++];
    }
}