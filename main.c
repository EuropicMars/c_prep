#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>


void shoot(bool *load, int size) 
{
    // Simulate shooting at the load
    for(int i = 0; i < size; i++) 
    {
        while (getchar() != '\n');

        if (load[i]) 
        {
            printf("Shot at index %d: Live!\n", i);
        }else 
        {
            printf("Shot at index %d: Blank!\n", i);
        }
    }
}

bool* createLoad(int *size) 
{
    //Generate the load size
    srand(time(0));
    const int min = 4;
    const int max = 10;
    *size = rand() % (max - min + 1) + min;


    int min_live = 1;
    bool *load = (bool*)malloc(*size * sizeof(bool));
    if (!load) 
    {
        perror("malloc failed");
        exit(1);
    }
    for (int i = 0; i < min_live; i++) 
    {
        load[i] = true;
    }
    for (int i = min_live; i < *size; i++) 
    {
        load[i] = rand() % 2;
    }
    for (int i = *size - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        bool temp = load[i];
        load[i] = load[j];
        load[j] = temp;
    }

    return load;
}


int main() 
{
    while (1) 
    {
        int size;
        bool *load = createLoad(&size);
        printf("Load array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", load[i]);
        }
        printf("\n");

        int live_count = 0, blank_count = 0;
        for (int i = 0; i < size; i++) {
            if (load[i]) live_count++;
            else blank_count++;
        }
        printf("Live count: %d, Blank count: %d\n", live_count, blank_count);

        shoot(load, size);

        free(load);
        Sleep(3000);
    }

    return 0;
}