#include <stdio.h>
#include <string.h>

#include "ClarkeWright.h"

int main(int argc, char* argv[]){
    FILE* problem = fopen(argv[argc-1], "r");
    depot_t depot;
    customer_t* *customers;

    populateCustomers(problem, &depot, &customers);

    printf("The depot at (%3d,%3d) has a truck size %d\n", depot.x, depot.y, depot.trucksize);
    for (int i = 0; customers[i]; i++){
        printf("Customer %d at (%3d,%3d) has a load %d\n",
                i, customers[i]->x, customers[i]->y, customers[i]->load);
    }
    return 0;
}
