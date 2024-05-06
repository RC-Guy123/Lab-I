#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
    #define N 201
    #define M 3
    #define MAXCHAR 100
    double data[N][M];
    char buffer[MAXCHAR];
    int row = 0;
    int column = 0;
    char *ptr;
    char fn[] = "data.csv";
    FILE *fptr;
    fptr = fopen(fn, "r");
    while (fgets(buffer, MAXCHAR, fptr)) {
        column = 0;
        row++;
        if (row == 1) {
            continue;
        }
        char* value = strtok(buffer, ", ");
        while (value) {  
            data[row-2][column] = strtod(value,&ptr);
            value = strtok(NULL, ", ");
            column++;
        }
    }
    fclose(fptr);
    fptr = NULL;
    for (int j = 0; j < M; j++) {
        double column_data[N];
        for (int i = 0; i < N; i++) {
            column_data[i] = data[i][j];
        }
        for (int i = 0; i < N - 1; i++) {
            for (int k = i + 1; k < N; k++) {
                if (column_data[i] > column_data[k]) {
                    double temp = column_data[i];
                    column_data[i] = column_data[k];
                    column_data[k] = temp;
                }
            }
        }
        double median;
        if (N % 2 == 0) {
            median = (column_data[N / 2 - 1] + column_data[N / 2]) / 2.0;
        } else {
            median = column_data[N / 2];
        }
        printf("%.2f", median);
        if (j < M - 1) {
            printf(",");
        }
    }
    printf("\n");
    return EXIT_SUCCESS;
}