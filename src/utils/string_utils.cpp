#include "string_utils.h"
#include <cstdio>

/**
 * Merge vargs strings into one newly allocated string
 *
 * @param count Number of strings given in vargs
 * @param ... Strings to merge
 * @return vargs merged into one string
 */
char* strMultiCat(int count, ...) {
    // Initialize vargs objects
    va_list ap;
    va_start(ap, count);
    char* toReturn = (char*) malloc(sizeof(char) * 128);
    toReturn[0] = (char) 0;
    toReturn[1] = '\0';

    // Loop through the vargs
    for (int i = 0; i < count; i++) {
        // Retrieve the vargs string at position i
        char* string = va_arg(ap, char*);
        // Prevent NPTR exceptions
        if (string == nullptr) continue;
        // Cat the previous string with the actual string using safeCat method to handle memory overflow issues
        toReturn = strSafeCat(toReturn, string);
    }

    // Close the vargs stream and return the final string
    va_end(ap);
    return toReturn;
}

/**
 * Allocate a string and fill it with the given int
 *
 * @param num Int that will be converted to string
 * @return String containing the given int
 */
char * strSafeCat(char *s1, const char *s2) {
    // Prevent NPTR exceptions
    if (s2 == nullptr) return s1;

    const size_t s1Length = strlen(s1);
    const size_t s2Length = strlen(s2);
    const size_t totalLength = s1Length + s2Length + 1;

    // Re-allocate s1 to make it long enough for the two strings
    s1 = (char*) realloc(s1, totalLength);

    // Copy the content of s2 into the new remaining space of s1
    memcpy(s1 + s1Length, s2, s2Length + 1);

    // Return the final string
    return s1;
}

/**
 * Reverse the given string from the character i to the character j
 *
 * @param string String to reverse
 * @param start First character to reverse position
 * @param end Last character to reverse position
 * @return The string reversed from the character i to the character j
 */
char* itoa(int value) {
    char* buffer = (char*) malloc(sizeof(char) * 100);
    // Print the int value into the buffer
    sprintf(buffer, "%d", value);
    return buffer;
}
