#include "CMatrixReader.h"
#include "CMatrixException.h"

/**
 * CGraphReader default constructor
 *
 * @param filename Path of the serialized matrix file
 */
CGraphReader::CGraphReader(const char *filename) {
    this->pMARFilename = filename;
}

/**
 * CGraphReader copy constructor
 *
 * @param reader Reader model
 */
CGraphReader::CGraphReader(const CMatrixReader &reader) {
    this->pMARFilename = reader.pMARFilename;
}

/**
 * Close the reader file if it opened then destroy it
 */
CGraphReader::~CGraphReader() {
    if (this->pMARFile != nullptr) {
        fclose(this->pMARFile);
    }
}

/**
 * Analyze the reader provided file and build a matrix from it
 *
 * @warning Currently the library only supports deserialization of double matrix, if an other type is specified, an
 * exception will be thrown
 * @throw CMatrixException if no file have been found, if the matrix is not of of the type double or the file is mal-formed
 * @return A fresh new matrix initialized and filled following the reader file instructions
 */
CMatrix<double>* CGraphReader::MARRead() {
    FILE* file = this->MARGetFile();
    if (file) {
        // Variables initialization
        CMatrix<double> *matrix;                    // Current matrix
        int bufferLength = 1024;                     // Max buffer length (by line)
        char buffer[1024];                          // Buffer used to read the file
        int fileLineCounter = 0;                    // Actual number of the file lines that have been analyzed
        int matrixLineCounter = 0;                  // Number of lines in the matrix
        int matrixColumnCounter = 0;                // Number of columns in the matrix
        char matrixType[50];                        // Type of the matrix items
        int actualMatrixLineCounter = 0;            // Number of matrix lines that have been analyzed
        int actualMatrixColumnCounter = 0;          // Number of matrix columns that have been analyzed
        // Check if the malloc failed
        if (!buffer) throw CMatrixException(MATRIX_EXCEPTION_MEMORY_ERROR, "Can't allocate read buffer");
        // Buffer will iterate through all of the file lines
        while (fgets(buffer, bufferLength - 1, file) != NULL) {
            // Increment the number of the file lines analyzed
            fileLineCounter++;
            // The buffer treatment will depend on the actual number of lines analyzed
            switch (fileLineCounter) {
                // TypeMatrice=double
                case 1:
                    if (sscanf(buffer, "TypeMatrice=%s", matrixType) == 1) {
                        // Only the double type is supported for now
                        if (strcmp(matrixType, "double") != 0) {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_UNSUPPORTED_TYPE,strMultiCat(3,
                                       "Type ", matrixType, " isn't supported yet by deserialization, please use double only"));
                        }
                    } else {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,strMultiCat(4,
                                       "Syntax error at line ", itoa(fileLineCounter), ", expected \"TypeMatrice=[type]\" got ", buffer));
                    }
                    break;
                // NBLignes=[int]
                case 2:
                    if (sscanf(buffer, "NBLignes=%d", &matrixLineCounter) == 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,strMultiCat(4,
                                       "Syntax error at line ", itoa(fileLineCounter), ", expected \"NBLignes=[int]\" got ", buffer));
                    }
                    break;
                // NBColonnes=[int]
                case 3:
                    if (sscanf(buffer, "NBColonnes=%d", &matrixColumnCounter) == 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,strMultiCat(4,
                                       "Syntax error at line ", itoa(fileLineCounter), ", expected \"NBColonnes=[int]\" got ", buffer));
                    }
                    break;
                // Matrice=[
                case 4:
                    if (strcmp(buffer, "Matrice=[\n") != 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,strMultiCat(4,
                                       "Syntax error at line ", itoa(fileLineCounter), R"(, expected "Matrice=[\n" got )", buffer));
                    }
                    matrix = new CMatrix<double>(matrixLineCounter, matrixColumnCounter);
                    break;
                // Lines with double separated with spaces or last line (])
                // There should be the same number of double in a line than the "NBColonnes" field plus,
                // There should be the same number of lines than the "NBLignes" field
                default:
                    if (strcmp(buffer, "]") == 0) {
                        // If the number of rows declared is inconsistent with the actual number of
                        // rows, an exception is thrown
                        if (actualMatrixLineCounter != matrixLineCounter) {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_INCONSISTENT_LINE_AMOUNT,strMultiCat(6,
                                           "Syntax error at line ", itoa(fileLineCounter),
                                           ", Expected an amount of ", itoa(matrixLineCounter), " lines, "
                                           "declared ", itoa(actualMatrixLineCounter)));
                        } else {
                            return matrix;
                        }
                    } else {
                        int i = 0;
                        int actualDoubleIndex = 0;
                        char actualDouble[100];
                        actualMatrixColumnCounter = 0;
                        // Loop through all of the line characters
                        while (buffer[i] != '\n') {
                            // If the number of columns declared is inconsistent with the actual number of
                            // columns, break the loop and an exception is thrown just after
                            if (actualMatrixColumnCounter > matrixColumnCounter) break;
                            // Build the current double by updating a temp array of char and the last char index or,
                            // If the current char is not a digit, not a dot or not a space, an exception is thrown
                            if (buffer[i] == '.' || isdigit(buffer[i])) {
                                actualDouble[actualDoubleIndex] = buffer[i];
                                actualDoubleIndex++;
                            } else if (buffer[i] != ' ') {
                                char wrongChar[2] = {buffer[i], '\0'};
                                throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,strMultiCat(5,
                                               "Syntax error at line ", itoa(fileLineCounter),
                                                ", Unexpected character ", wrongChar,
                                                ", expected number"));
                            }
                            // If the character is a space or if the next character is the end of the buffer,
                            // Increment the number of analyzed columns then,
                            // Update the matrix item with the previous analyzed number
                            if ((buffer[i] == ' ' || buffer[i + 1] == '\n') && actualDoubleIndex > 0) {
                                actualDouble[actualDoubleIndex] = '\0';
                                double matrixItem = atof(actualDouble);
                                matrix->MATSetItemAt(actualMatrixLineCounter, actualMatrixColumnCounter, matrixItem);
                                actualDoubleIndex = 0;
                                actualMatrixColumnCounter++;
                            }
                            i++;
                        }
                        // If the number of column is inconsistent with the number declared, an exception is thrown
                        if (actualMatrixColumnCounter != matrixColumnCounter) {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_INCONSISTENT_COLUMN_AMOUNT,strMultiCat(6,
                                           "Syntax error at line ", itoa(fileLineCounter),
                                           ", Expected an amount of ", itoa(matrixColumnCounter), " columns, "
                                           "declared ", itoa(actualMatrixColumnCounter)));
                        }
                        actualMatrixLineCounter++;
                    }
                    break;
            }
        }
        // If the method goes so far, then no matrix have been returned or in other words, the file is not complete,
        // It syntax is correct but lines are missing
        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, "File is not complete");
    } else {
        // If file is null, then the fopen call failed and the file is not readable / does not exist
        throw CMatrixException(MATRIX_EXCEPTION_NO_SUCH_FILE, strMultiCat(3,
                                                                          "No such file ", this->MARGetFilename(), " (or the file is not readable by the program)"));
    }
}

/**
 * Opens a file stream if the provided file has not been opened yet,
 * then returns the provided file as a FILE pointer
 *
 * @return
 */
FILE* CGraphReader::MARGetFile() {
    if (this->pMARFile == nullptr) {
        this->pMARFile = fopen(this->pMARFilename, "r");
    }
    return this->pMARFile;
}

/**
 * Retrieves the reader provided file name
 *
 * @return The reader provided file name
 */
inline const char* CGraphReader::MARGetFilename() {
    return this->pMARFilename;
}

