#include "CGraphReader.h"
#include "CGraphException.h"

/**
 * CGraphReader default constructor
 *
 * @param filename Path of the serialized graph file
 */
CGraphReader::CGraphReader(const char *filename) {
    this->pGRRFilename = filename;
}

/**
 * CGraphReader copy constructor
 *
 * @param reader Reader model
 */
CGraphReader::CGraphReader(const CGraphReader &reader) {
    this->pGRRFilename = reader.pGRRFilename;
}

/**
 * Close the reader file if it opened then destroy it
 */
CGraphReader::~CGraphReader() {
    if (this->pGRRFile != nullptr) {
        fclose(this->pGRRFile);
    }
}

/**
 * Analyze the reader provided file and build a graph from it
 *
 * @warning Currently the library only supports deserialization of double matrix, if an other type is specified, an
 * exception will be thrown
 * @throw CGraphException if no file have been found, if the file is mal-formed
 * @return A fresh new graph initialized and filled following the reader file instructions
 */
CGraph* CGraphReader::GRRRead() {
    FILE* file = this->GRRGetFile();
    if (file) {
        // Variables initialization
        CGraph* graph;                              // Current graph
        int bufferLength = 1024;                    // Max buffer length (by line)
        char buffer[1024];                          // Buffer used to read the file
        int fileLineCounter = 0;                    // Actual number of the file lines that have been analyzed
        int graphVertexCounter = 0;                 // Number of vertexes in the graph
        int graphArcCounter = 0;                    // Number of arcs in the graph
        int actualGraphVertexCounter = 0;           // Number of graph vertices that have been analyzed
        int actualGraphArcCounter = 0;              // Number of graph arcs that have been analyzed
        bool vertexTableClosed = false;             // Whether the vertex table is closed or not
        bool arcTableOpened = false;                // Whether the arc table is opened or not
        // Buffer will iterate through all of the file lines
        while (fgets(buffer, bufferLength - 1, file) != NULL) {
            // Increment the number of the file lines analyzed
            fileLineCounter++;
            // The buffer treatment will depend on the actual number of lines analyzed
            switch (fileLineCounter) {
                // NBSommets=[int]
                case 1:
                    if (sscanf(buffer, "NBSommets=%d", &graphVertexCounter) != 1) {
                        throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, strMultiCat(4,
                                       "Syntax error at line ", itoa(fileLineCounter),
                                       ", expected \"NBSommets=[int]\" got ", buffer));
                    }
                    break;
                // NBArcs=[int]
                case 2:
                    if (sscanf(buffer, "NBArcs=%d", &graphArcCounter) != 1) {
                        throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, strMultiCat(4,
                                       "Syntax error at line ", itoa(fileLineCounter),
                                       ", expected \"NBArcs=[int]\" got ", buffer));
                    }
                    break;
                // Sommets=[
                case 3:
                    if (strcmp(buffer, "Sommets=[\n") != 0) {
                        throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, strMultiCat(4,
                                       "Syntax error at line ", itoa(fileLineCounter),
                                       R"(, expected "Sommets=[\n" got )", buffer));
                    }
                    graph = new CGraph();
                    break;
                // Lines with double separated with spaces or last line (])
                // There should be the same number of double in a line than the "NBColonnes" field plus,
                // There should be the same number of lines than the "NBLignes" field
                default:
                    // First case, vertices definition table
                    if (!vertexTableClosed) {
                        // Check if the line is the closing bracket
                        if (strcmp(buffer, "]\n") == 0) {
                            vertexTableClosed = true;
                            // If the number of vertices declared is inconsistent with the actual number of
                            // vertices, an exception is thrown
                            if (actualGraphVertexCounter != graphVertexCounter) {
                                throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_INCONSISTENT_VERTEX_AMOUNT,
                                      strMultiCat(6,
                                                  "Syntax error at line ", itoa(fileLineCounter),
                                                  ", Expected an amount of ", itoa(graphVertexCounter),
                                                  " vertices, "
                                                  "declared ", itoa(actualGraphVertexCounter)));
                            }
                        }
                        // Else the line describe a vertex
                        else {
                            int vertexId = 0;
                            if (sscanf(buffer, "Numero=%d", &vertexId) == 1) {
                                actualGraphVertexCounter++;
                                graph->GRAAddVertex(new CSommet(vertexId));
                            } else {
                                throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, strMultiCat(4,
                                               "Syntax error at line ", itoa(fileLineCounter),
                                               R"(, expected "Numero=[int]" got ")", buffer));
                            }
                        }
                    }
                    // Second case, arcs definition table
                    else {
                        // If the line "Arcs=[" have been analyzed
                        if (arcTableOpened) {
                            // Check if the line is the closing bracket
                            if (strcmp(buffer, "]") == 0) {
                                // If the number of arcs declared is inconsistent with the actual number of
                                // arcs, an exception is thrown
                                if (actualGraphArcCounter != graphArcCounter) {
                                    throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_INCONSISTENT_ARC_AMOUNT,strMultiCat(6,
                                                  "Syntax error at line ", itoa(fileLineCounter),
                                                  ", Expected an amount of ", itoa(graphArcCounter),
                                                  " arcs, "
                                                  "declared ", itoa(actualGraphArcCounter)));
                                } else {
                                    return graph;
                                }
                            }
                            // Else the line describe an arc
                            else {
                                int startVertexId = 0;
                                int endVertexId = 0;
                                int cost = 0;
                                int maximumFlow = 0;
                                if (sscanf(buffer, "Debut=%d, Fin=%d, Cout=%d, FlotMaximum=%d", &startVertexId, &endVertexId, &cost, &maximumFlow) == 4) {
                                    actualGraphArcCounter++;
                                    CSommet* existingStartVertex = graph->GRAGetVertexById(startVertexId);
                                    CSommet* existingEndVertex = graph->GRAGetVertexById(endVertexId);
                                    if (existingStartVertex != nullptr && existingEndVertex != nullptr) {
                                        if (cost > 0 && maximumFlow > 0) {
                                            CArc* arc = new CArc(existingEndVertex->SOMGetId(), cost, maximumFlow);
                                            existingEndVertex->SOMAddIncomingArc(arc);
                                            existingStartVertex->SOMAddLeavingArc(arc);
                                            printf("Adding incoming for %d (%d) New size: %d\n", existingEndVertex->SOMGetId(), existingStartVertex->SOMGetId(), existingEndVertex->SOMGetIncomingArcs()->getSize());
                                        } else {
                                            throw CGraphException(GRAPH_EXCEPTION_WRONG_ARC_ATTRIBUTES, strMultiCat(4,
                                                "Syntax error at line ", itoa(fileLineCounter),
                                                " wrong cost or maximum flow ", buffer));
                                        }
                                    } else {
                                        throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_UNKNOWN_VERTEX,strMultiCat(4,
                                                 "Syntax error at line ", itoa(fileLineCounter),
                                                 " unknown start or end vertex ",
                                                 buffer));
                                    }
                                } else {
                                    throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,strMultiCat(4,
                                                  "Syntax error at line ", itoa(fileLineCounter),
                                                  R"(, expected "Debut=[int], Fin=[int], Cout=[int], FlotMaximum=[int]" got ")",
                                                  buffer));
                                }
                            }
                        }
                        // Else we need to ensure that the line "Arcs=[" is the next line
                        else {
                            if (strcmp(buffer, "Arcs=[\n") == 0) {
                                arcTableOpened = true;
                            } else {
                                throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,strMultiCat(4,
                                              "Syntax error at line ", itoa(fileLineCounter),
                                              R"(, expected "Arcs=[" got ")",
                                              buffer));
                            }
                        }
                    }
                    break;
            }
        }
        // If the method goes so far, then no graph have been returned or in other words, the file is not complete,
        // It syntax is correct but lines are missing
        throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, "File is not complete");
    } else {
        // If file is null, then the fopen call failed and the file is not readable / does not exist
        throw CGraphException(GRAPH_EXCEPTION_NO_SUCH_FILE, strMultiCat(3,
                        "No such file ", this->GRRGetFilename(), " (or the file is not readable by the program)"));
    }
}

/**
 * Opens a file stream if the provided file has not been opened yet,
 * then returns the provided file as a FILE pointer
 *
 * @return
 */
FILE* CGraphReader::GRRGetFile() {
    if (this->pGRRFile == nullptr) {
        this->pGRRFile = fopen(this->pGRRFilename, "r");
    }
    return this->pGRRFile;
}

/**
 * Retrieves the reader provided file name
 *
 * @return The reader provided file name
 */
inline const char* CGraphReader::GRRGetFilename() {
    return this->pGRRFilename;
}

