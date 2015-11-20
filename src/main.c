#include <stdio.h>
#include <string.h>

#include "ClarkeWright.h"

int main(int argc, char* argv[]){
    printf("40099603 Clarke-Wright route optimiser\n");

    printf("Loading depot and customer information from file... ");
    FILE* problem = fopen(argv[argc-2], "r");
    depot_t depot;
    customer_t* *customers;
    printf("\x1b[32mdone.\x1b[0m\n");

    printf("Parsing CSV and populating entries... ");
    populateCustomers(problem, &depot, &customers);
    fclose(problem);
    printf("\x1b[32mdone.\x1b[0m\n");

    printf("Solving... ");
    customer_t* *routes = solveClarkeWright(depot, customers);
    printf("\x1b[32mdone.\x1b[0m\n");

    FILE* solution = fopen(argv[argc-1], "w");
    for (size_t i = 0; routes[i]; i++){
        for (customer_t* current = routes[i]; current; current = current->next){
            fprintf(solution, "%f,%f,%d,", (float)current->x, (float)current->y, current->load);
        }
        fseek(solution, -1, SEEK_CUR);
        fprintf(solution, "\n");
    }

    printf("Deallocating problem... ");
    closeCustomers(&customers);
    printf("\x1b[32mdone.\x1b[0m\n");

    return 0;
}
