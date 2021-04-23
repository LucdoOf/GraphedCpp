#include "CGraphReader.h"
#include <iostream>
#include <math.h>

/**
 * Program entry point, run tests with the provided files as arguments
 *
 * @param argc Number of arguments
 * @param argv Argument list, all arguments will be treated as serialized graph files
 * @return The program exit code
 */
int main(int argc, char** argv){
    auto reader = new CGraphReader(argv[1]);
    reader->GRRRead();
}