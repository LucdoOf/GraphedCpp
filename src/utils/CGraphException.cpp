#include "CGraphException.h"

/**
 * CGraphException constructor
 *
 * @see defines.h For the list of available error codes
 * @param errorCode Error code used to identify the exception
 * @param message Message describing the exception
 */
CGraphException::CGraphException(int errorCode, char *message) noexcept {
    this->iGREErrorCode = errorCode;
    this->sGREMessage = message;
}

/**
 * @inheritDoc
 */
const char *CGraphException::what() const noexcept {
    char* toReturn = (char*) malloc(sizeof(this->sGREMessage) + sizeof(char) * 5);
    sprintf(toReturn, "E%d: %s", this->iGREErrorCode, this->sGREMessage);
    return toReturn;
}
