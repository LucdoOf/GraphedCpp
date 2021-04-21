#ifndef GRAPHEDCPP_CGRAPHEXCEPTION_H
#define GRAPHEDCPP_CGRAPHEXCEPTION_H

#include <exception>
#include <stdio.h>
#include <cstdlib>
#include <string.h>

/**
 * CGraphException class
 *
 * Used to throw custom exceptions inside the Graphed project
 */
class CGraphException : public std::exception {

public:
    /**
     * CGraphException constructor
     *
     * @see defines.h For the list of available error codes
     * @param errorCode Error code used to identify the exception
     * @param message Message describing the exception
     */
    explicit CGraphException(int errorCode, char* message) noexcept;
    /**
     * @inheritDoc
     */
    ~CGraphException() override = default;
    /**
     * @inheritDoc
     */
    const char* what() const noexcept override;

private:
    /**
     * Message describing the exception
     */
    char* sGREMessage;

    /**
     * Error code used to identify the exception
     *
     * @see defines.h For the list of available error codes
     */
    int iGREErrorCode;

};

#endif //GRAPHEDCPP_CGRAPHEXCEPTION_H
