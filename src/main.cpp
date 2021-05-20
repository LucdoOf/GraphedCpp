#include "CGraphReader.h"
#include "CGraphException.h"

/**
 * Program entry point, run tests with the provided files as arguments
 *
 * @param argc Number of arguments
 * @param argv Argument list, all arguments will be treated as serialized graph files
 * @return The program exit code
 */
int main(int argc, char** argv){
    if (argc == 2) {
        auto reader = new CGraphReader(argv[1]);
        CGraph* graph = reader->GRRRead();
        graph->GRAPrint();
        CGraph* invertedGraph = graph->GRAInvert();
        invertedGraph->GRAPrint();
        delete reader;
        delete graph;
        delete invertedGraph;
    } else {
        throw CGraphException(GRAPH_EXCEPTION_INVALID_PROGRAM_PARAMETERS, strMultiCat(3,
            "Example program need 1 parameter, given ", itoa(argc)));
    }
}