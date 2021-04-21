#include "CMatrixException.h"

/**
 * CMatrixException constructor
 *
 * @see defines.h For the list of available error codes
 * @param errorCode Error code used to identify the exception
 * @param message Message describing the exception
 */
CMatrixException::CMatrixException(int errorCode, char *message) noexcept {
    this->iMAEErrorCode = errorCode;
    this->sMAEMessage = message;
}

/**
 * @inheritDoc
 */
const char *CMatrixException::what() const noexcept {
    char* toReturn = (char*) malloc(sizeof(this->sMAEMessage) + sizeof(char) * 5);
    sprintf(toReturn, "E%d: %s", this->iMAEErrorCode, this->sMAEMessage);
    return toReturn;
}
