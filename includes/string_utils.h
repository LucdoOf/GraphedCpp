#ifndef MATRIXEDCPP_STRING_UTILS_H
#define MATRIXEDCPP_STRING_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/**
 * Merge vargs strings into one newly allocated string
 *
 * @param count Number of strings given in vargs
 * @param ... Strings to merge
 * @return vargs merged into one string
 */
char* strMultiCat(int count, ...);

/**
 * Allocate a string and fill it with the given int
 *
 * @param num Int that will be converted to string
 * @return String containing the given int
 */
char* itoa(int num);

/**
 * Merge the content of s1 and s2 into s1 and realloc s1 if not large enough
 *
 * @param s1 String 1 to merge (original string, will be returned and re-allocated)
 * @param s2 String 2 to merge
 * @return s1 and s2 merged into s1
 */
char * strSafeCat(char *s1, const char *s2);

#endif //MATRIXEDCPP_STRING_UTILS_H
