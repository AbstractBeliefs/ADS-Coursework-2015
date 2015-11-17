#include "ClarkeWright.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sglib.h"

#define CMP_SAVING(s1, s2) (s2.saving - s1.saving)

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
        (*customers)[j]->next = NULL;
        (*customers)[j]->prev = NULL;
        (*customers)[++j] = NULL;  // Sentinel the end of list
    }

    return 0;
}

int closeCustomers(customer_t** *customers){
    for (size_t i = 0; (*customers)[i]; i++){
        free((*customers)[i]);
        (*customers)[i] = NULL;
    }
    free(*customers);
    (*customers) = NULL;
    return 0;
}

double getDistance(int x1, int y1, int x2, int y2){
    // Pythagorean distance
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
}

double getSavings(customer_t* i, customer_t* j, depot_t depot){
    double c_0i = getDistance(i->x, i->y, depot.x, depot.y);
    double c_j0 = getDistance(j->x, j->y, depot.x, depot.y);
    double c_ij = getDistance(i->x, i->y, j->x, j->y);

    return c_0i + c_j0 - c_ij;
}

int customerNotInRoute(customer_t* customer, customer_t* route){
    for (; route; route = route->next){
        if (customer == route){ return 0; }
    }
    return 1;
}

unsigned int routeLoad(customer_t* route){
    // rewind to start of route
    for (; route->prev; route = route->prev){}

    // Sum the load between the start and end of the route
    unsigned int total_load = 0;

    do {
        total_load += route->load;
    } while ((route = route->next));

    return total_load;
}

customer_t** solveClarkeWright(depot_t depot, customer_t** customers){
    // Allocate enough for a fully connected graph (n*(n-1)/2) plus sentinel
    size_t num_savings = 0;
    size_t num_customers = 0;
    for (size_t i = 0; customers[i]; i++){
        num_customers++;
    }

    num_savings = (num_customers * (num_customers-1)) / 2;
    saving_t* savings = malloc(sizeof(saving_t) * num_savings);

    // Calculate the savings for all pairings and sort them best to worst
    size_t idx = 0;
    for (size_t i = 0; customers[i+1]; i++){
        for (size_t j = i+1; customers[j]; j++){
            savings[idx].i = customers[i];
            savings[idx].j = customers[j];
            savings[idx++].saving = getSavings(
                customers[i],
                customers[j],
                depot
            );
        }
    }
    SGLIB_ARRAY_SINGLE_QUICK_SORT(saving_t, savings, num_savings, CMP_SAVING);

    // Apply these savings, building routes as we go
    for (size_t i = 0; i<num_savings; i++){
        if (
                (savings[i].i->next == NULL && savings[i].j->prev == NULL) &&
                (routeLoad(savings[i].i) + routeLoad(savings[i].j) <= depot.trucksize) &&
                (customerNotInRoute(savings[i].i, savings[i].j))
                ){
            savings[i].i->next = savings[i].j;
            savings[i].j->prev = savings[i].i;
        } else if (
                (savings[i].i->prev == NULL && savings[i].j->next == NULL) &&
                (routeLoad(savings[i].i) + routeLoad(savings[i].j) <= depot.trucksize) &&
                (customerNotInRoute(savings[i].j, savings[i].i))
                ){
            savings[i].i->prev = savings[i].j;
            savings[i].j->next = savings[i].i;
        } else {
            continue;    // route wasn't mergeable in either direction.
        }
    }

    // Build the finalised list of routes
    size_t num_routes = 0;
    for (size_t i = 0; customers[i]; i++){
        if (customers[i]->prev == NULL){
            num_routes++;
        }
    }
    customer_t* *routes = malloc(sizeof(customer_t*) * (num_routes+1));
    idx = 0;
    for (size_t i = 0; customers[i]; i++){
        if (customers[i]->prev == NULL){
            routes[idx] = customers[i];
            routes[++idx] = NULL;
        }
    }

    return routes;
}
