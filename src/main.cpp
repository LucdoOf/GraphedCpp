#include "CMatrix.h"
#include "CMatrixReader.h"
#include <iostream>
#include <math.h>

/**
 * Program entry point, run tests with the provided files as arguments
 *
 * @param argc Number of arguments
 * @param argv Argument list, all arguments will be treated as serialized matrix files
 * @return The program exit code
 */
int main(int argc, char** argv){
    try {
        // Check that program arguments are valid
        if (argc <= 1) {
            throw CMatrixException(MATRIX_EXCEPTION_INVALID_PROGRAM_PARAMETERS, "Please provide at least 1 matrix file as program parameter");
        }

        // Initialise the matrix table
        int iMatrixTableLength = argc - 1;
        auto pMatrixTable = (CMatrix<double>**) malloc(sizeof(CMatrix<double>) * iMatrixTableLength);
        for (int i = 1; i < argc; i++) {
            // Read the matrix serialized files
            auto reader = new CMatrixReader(argv[i]);
            pMatrixTable[i - 1] = reader->MARRead();
            delete reader;
        }

        // Retrieve the input number for tests
        double c = 0;
        printf("\n");
        printf("Veuillez saisir un nombre c: ");
        scanf("%lf", &c);
        printf("\n");

        // Matrices * c
        std::cout << "================= Matrices inchangées: =================" << std::endl;
        for (int i = 0; i < iMatrixTableLength; i++){
            printf("\n");
            std::cout << "Matrice " << i+1 << ": " << std::endl;
            (*pMatrixTable[i]).MATPrint();
        }

        // Matrices * c
        std::cout << "================= Multiplication de chaque matrices par c: =================" << std::endl;
        for (int i = 0; i < iMatrixTableLength; i++){
            printf("\n");
            std::cout << "Matrice " << i+1 << ": " << std::endl;
            ((*pMatrixTable[i]) * c).MATPrint();
        }

        // Matrices / c
        std::cout << "================= Division de chaque matrices par c: =================" << std::endl;
        for (int i = 0; i < iMatrixTableLength; i++){
            printf("\n");
            std::cout << "Matrice " << i+1 << " : " << std::endl;
            ((*pMatrixTable[i]) / c).MATPrint();
        }

        // Matrices sum
        std::cout << "================= Addition de chaque matrices entre elles: =================" << std::endl;
        auto tempMatrix1 = *pMatrixTable[0];
        for (int i = 1; i < iMatrixTableLength; i++){
            tempMatrix1 = tempMatrix1 + *pMatrixTable[i];
        }
        tempMatrix1.MATPrint();

        // Matrices alternate sum
        std::cout << "================= Addition alternée de chaque matrices entre elles: =================" << std::endl;
        auto tempMatrix2 = *pMatrixTable[0];
        for (int i = 1; i < iMatrixTableLength; i++){
            tempMatrix2 = tempMatrix2 + ((*pMatrixTable[i]) * pow(-1, i));
        }
        tempMatrix2.MATPrint();

        // Matrices product
        std::cout << "================= Produit de chaque matrices entre elles: =================" << std::endl;
        auto tempMatrix3 = *pMatrixTable[0];
        for (int i = 1; i < iMatrixTableLength; i++){
            tempMatrix3 = ((tempMatrix3 * *pMatrixTable[i]));
        }
        tempMatrix3.MATPrint();

        // Matrices transposed
        std::cout << "================= Matrices transposées: =================" << std::endl;
        for (int i = 0; i < iMatrixTableLength; i++){
            pMatrixTable[i]->MATTranspose()->MATPrint();
        }

        // Everything gone well :)
        return 0;
    } catch (CMatrixException &e) {
        // Something went wrong :(
        std::cerr << e.what() << std::endl;
        return 1;
    }
}