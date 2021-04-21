//
// Created by lucas on 31/03/2021.
//

#ifndef GRAPHEDCPP_CGRAPHREADER_H
#define GRAPHEDCPP_CGRAPHREADER_H

#include <string.h>
#include "defines.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "CMatrix.h"
#include "string_utils.h"

/**
 * CGraphReader class
 *
 * This class is intended to create graph objects from flat files and to handle
 * exceptions if flat files does not respect the correct graph format
 */
class CGraphReader {

private:
    /**
     * Reader provided file name
     */
    const char* pGRRFilename;
    /**
     * Temporary file buffer for inner operations
     */
    FILE* pGRRFile;
    /**
     * Opens a file stream if the provided file has not been opened yet,
     * then returns the provided file as a FILE pointer
     *
     * @return
     */
    FILE* GRRGetFile();

public:
    /**
     * CGraphReader default constructor
     *
     * @param filename Path of the serialized graph file
     */
    explicit CGraphReader(const char* filename);
    /**
     * CGraphReader copy constructor
     *
     * @param reader Reader model
     */
    CGraphReader(CGraphReader const &reader);
    /**
     * CGraphReader destructor
     *
     * Close the reader file if it is opened and then destroy it
     */
    ~CGraphReader();
    /**
     * Analyze the reader provided file and build a graph from it
     * The provided file must follow the follow format:
     *
     * TypeMatrice=[type]
     * NBLignes=[int]
     * NBColonnes=[int]
     * Matrice=[
     * [double] [double] ...
     * [double] [double] ...
     * ...
     * ]
     *
     * @warning If the number of lines / columns declared in the matrix core is inconsistent with the number of lines / columns
     * declared above, an exception will be thrown
     * @warning Currently the library only supports deserialization of double matrix, if an other type is specified, an
     * exception will be thrown
     * @throw CGraphException if no file have been found, if the file is mal-formed
     * @return A fresh new graph initialized and filled following the reader file instructions
     */
    CMatrix<double>* GRRRead();
    /**
     * Retrieves the reader provided file name
     *
     * @return The reader provided file name
     */
    inline const char* GRRGetFilename();

};

#endif //GRAPHEDCPP_CGRAPHREADER_H
