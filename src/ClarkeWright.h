#ifndef __ClarkeWright_h__
#define __ClarkeWright_h__

#include <stdio.h>

enum error {
    ENOCUSTOMERS = 1,
    EFAILEDTOMEMORY
};

typedef struct {
    int x;
    int y;
    int load;
} customer_t;
 
typedef struct {
    int x;
    int y;
    int trucksize;
} depot_t;

int populateCustomers(FILE* problem, depot_t* depot, customer_t** *customers);

#endif
