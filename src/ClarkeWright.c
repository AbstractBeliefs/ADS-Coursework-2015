#include "ClarkeWright.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int populateCustomers(FILE* problem, depot_t* depot, customer_t** *customers){
    // Read the file, count the number of customers, and allocate buffers
    int numCustomers = 0;
    char c;
    do {
        c = fgetc(problem);
        if (c == '\n'){
            numCustomers++;
        }
    } while (c != EOF);

    if (numCustomers < 2){ // Check we actually got enough
        return 1;
    }

    *customers = malloc(sizeof(customer_t*) * (numCustomers));  // -1 for depot, +1 for sentinel null.
    if (!(*customers)){
        return 2;
    }

    rewind(problem);

    // Read and parse depot and customer lines into their appropriate objects
    char line[1024];
    int buffer[3] = {0,0,0};

    // Get depot first
    fgets(line, 1024, problem);
    int i = 0; // Field counter, since you can't use the comma op with multiple types in a single for
    for (const char* token = strtok(line, ","); token; token = strtok(NULL, ",")){
        buffer[i++] = atoi(token);
        if (i >= 3){ break; }
    }
    depot->x = buffer[0];
    depot->y = buffer[1];
    depot->trucksize = buffer[2];

    int j = 0; // Line counter, as above for i.
    while (fgets(line, 1024, problem)){
        i = 0;
        for (const char* token = strtok(line, ","); token; token = strtok(NULL, ",")){
            buffer[i++] = atoi(token);
            if (i >= 3){ break; }
        }
        (*customers)[j] = malloc(sizeof(customer_t));
        if (!(*customers)[j]){ return 3; }
        (*customers)[j]->x = buffer[0];
        (*customers)[j]->y = buffer[1];
        (*customers)[j]->load = buffer[2];
        (*customers)[++j] = NULL;  // Sentinel the end of list
    }

    return 0;
}

int closeCustomers(customer_t** *customers){
    for (int i = 0; (*customers)[i]; i++){
        free((*customers)[i]);
        (*customers)[i] = NULL;
    }
    free(*customers);
    (*customers) = NULL;
    return 0;
}
