#ifndef __ClarkeWright_h__
#define __ClarkeWright_h__

#include <stdio.h>

enum error {
    ENOCUSTOMERS = 1,
    EFAILEDTOMEMORY
};

typedef struct customer_t {
    int x;                      // X Coord
    int y;                      // Y Coord
    int load;                   // Load to pick up
    struct customer_t *next;    // Previous link in route. NULL means depot.
    struct customer_t *prev;    // Next link in route. NULL means depot.
} customer_t;
 
typedef struct {
    int x;
    int y;
    int trucksize;
} depot_t;

int populateCustomers(FILE* problem, depot_t* depot, customer_t** *customers);
int closeCustomers(customer_t** *customers);

#endif
