#ifndef MATRIXEDCPP_CMATRIXEXCEPTION_H
#define MATRIXEDCPP_CMATRIXEXCEPTION_H

#include <exception>
#include <stdio.h>
#include <cstdlib>
#include <string.h>

/**
 * CMatrixException class
 *
 * Used to throw custom exceptions inside the Matrixed project
 */
class CMatrixException : public std::exception {

public:
    /**
     * CMatrixException constructor
     *
     * @see defines.h For the list of available error codes
     * @param errorCode Error code used to identify the exception
     * @param message Message describing the exception
     */
    explicit CMatrixException(int errorCode, char* message) noexcept;
    /**
     * @inheritDoc
     */
    ~CMatrixException() override = default;
    /**
     * @inheritDoc
     */
    const char* what() const noexcept override;

private:
    /**
     * Message describing the exception
     */
    char* sMAEMessage;

    /**
     * Error code used to identify the exception
     *
     * @see defines.h For the list of available error codes
     */
    int iMAEErrorCode;

};

#endif //MATRIXEDCPP_CMATRIXEXCEPTION_H
