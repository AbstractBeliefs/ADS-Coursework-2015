customer_cwt** solveClarkeWright(depot_cwt depot, customer_cwt** customers){
    // Build the finalised list of routes
    size_t num_routes = 0;
    for (size_t i = 0; customers[i]; i++){
        if (customers[i]->prev == NULL){
            num_routes++;
        }
    }
    customer_cwt* *routes = malloc(sizeof(customer_cwt*) * (num_routes+1));
    size_t idx = 0;
    for (size_t i = 0; customers[i]; i++){
        if (customers[i]->prev == NULL){
            routes[idx] = customers[i];
            routes[++idx] = NULL;
        }
    }

    return routes;
}
