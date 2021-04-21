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
CMatrix<double>* CGraphReader::GRRRead() {
    FILE* file = this->GRRGetFile();
    if (file) {
        // Variables initialization
        CMatrix<double> *matrix;                    // Current matrix
        int bufferLength = 1024;                    // Max buffer length (by line)
        char buffer[1024];                          // Buffer used to read the file
        int fileLineCounter = 0;                    // Actual number of the file lines that have been analyzed
        int graphVertexCounter = 0;                 // Number of vertexes in the graph
        int graphArcCounter = 0;                    // Number of arcs in the graph
        int actualGraphVertexCounter = 0;           // Number of graph vertices that have been analyzed
        int actualGraphArcCounter = 0;              // Number of graph arcs that have been analyzed
        bool vertexTableClosed = false;             // Whether the vertex table is closed or not
        // Check if the malloc failed
        if (!buffer) throw CGraphException(GRAPH_EXCEPTION_MEMORY_ERROR, "Can't allocate read buffer");
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
                    matrix = new CMatrix<double>(matrixLineCounter, matrixColumnCounter);
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
                                // TODO ADD VERTEX
                            } else {
                                throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, strMultiCat(4,
                                               "Syntax error at line ", itoa(fileLineCounter),
                                               ", expected \"Numero=[int]\" got ", buffer));
                            }
                        }
                    }
                    // Second case, arcs definition table
                    else {
                        // Check if the line is the closing bracket
                        if (strcmp(buffer, "]\n") == 0) {
                            // If the number of arcs declared is inconsistent with the actual number of
                            // arcs, an exception is thrown
                            if (actualGraphArcCounter != graphArcCounter) {
                                throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_INCONSISTENT_ARC_AMOUNT,
                                      strMultiCat(6,
                                                  "Syntax error at line ", itoa(fileLineCounter),
                                                  ", Expected an amount of ", itoa(graphArcCounter),
                                                  " arcs, "
                                                  "declared ", itoa(actualGraphArcCounter)));
                            }
                        }
                        // Else the line describe an arc
                        else {
                            int startVertexId = 0;
                            int endVertexId = 0;
                            if (sscanf(buffer, "Debut=%d, Fin=%d", &startVertexId, &endVertexId) == 2) {
                                // TODO ADD ARC
                            } else {
                                throw CGraphException(GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, strMultiCat(4,
                                               "Syntax error at line ", itoa(fileLineCounter),
                                               ", expected \"Debut=[int], Fin=[int]\" got ", buffer));
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

