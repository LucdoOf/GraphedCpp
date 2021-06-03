#include "CGraphReader.h"
#include "CGraphException.h"
#include <iostream>

using namespace std;

/**
 * Program entry point, run tests with the provided files as arguments
 *
 * @param argc Number of arguments
 * @param argv Argument list, all arguments will be treated as serialized graph files
 * @return The program exit code
 */
int main(int argc, char** argv){
    try {
        if (argc == 2) {
            printf("\nGraph %s: ", argv[1]);
            auto reader = new CGraphReader(argv[1]);
            CGraph* graph = reader->GRRRead();
            graph->GRAPrint();
            printf("\n");
            printf("Graph %s inverted: ", argv[1]);
            CGraph* invertedGraph = graph->GRAInvert();
            invertedGraph->GRAPrint();
            printf("\nFlow amounts:\n");
            graph->GRAAskFlowAmounts();
            bool test = graph->GRATestConservationLaw();
            printf(test ? "\nThe graph have passed the conservation law !\n" : "\nThe graph didn't passed the conservation law :(\n");
            printf("The graph total cost is %d\n", graph->GRAGetTotalCost());
            printf("\nDetails:\n");
            graph->GRAPrintConservationLaw();
            delete reader;
            delete graph;
            delete invertedGraph;
        }
        else {
            throw CGraphException(GRAPH_EXCEPTION_INVALID_PROGRAM_PARAMETERS, strMultiCat(3,
                "Example program need 1 parameter, given ", itoa(argc)));
        }
    } catch (CGraphException &e) {
        cerr << "\n" << e.what() << "\n";
    }
}