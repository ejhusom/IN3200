#include "PE_functions_ejhusom.h"

int main(int argc, char *argv[]){

    char *filename;
    if(argc > 1){
        filename = argv[1];
    } else {
        printf("Give file name as command line argument.\n");
        return 0;
    }

    int *from_node_id = NULL; 
    int *to_node_id = NULL;

    read_graph_from_file(filename, from_node_id, to_node_id);


    free(from_node_id);
    free(to_node_id);

    return 0;
}
