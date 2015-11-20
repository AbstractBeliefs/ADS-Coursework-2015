#ifndef __ClarkeWright_h__
#define __ClarkeWright_h__

#include <stdio.h>

typedef struct customer_cwt {
    int x;                      // X Coord
    int y;                      // Y Coord
    int load;                   // Load to pick up
    struct customer_cwt *next;    // Previous link in route. NULL means depot.
    struct customer_cwt *prev;    // Next link in route. NULL means depot.
} customer_cwt;
 
typedef struct {
    int x;
    int y;
    int trucksize;
} depot_cwt;

typedef struct {
    customer_cwt *i;
    customer_cwt *j;
    double saving;
} saving_cwt;

int populateCustomers(FILE* problem, depot_cwt* depot, customer_cwt** *customers);
int closeCustomers(customer_cwt** *customers);
int closeRoutes(customer_cwt** *routes);
customer_cwt** solveClarkeWright(depot_cwt depot, customer_cwt** customers);

#endif
