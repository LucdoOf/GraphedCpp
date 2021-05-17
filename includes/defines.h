#ifndef GRAPHEDCPP_DEFINES_H
#define GRAPHEDCPP_DEFINES_H

// ================= Global error codes ================= //

/**
 * Thrown when a memory-linked error occured
 * 
 * @example Malloc fail
 */
#define GRAPH_EXCEPTION_MEMORY_ERROR 0
/**
 * Thrown when a file is not readable bu the program or does not exist
 */
#define GRAPH_EXCEPTION_NO_SUCH_FILE 1
/**
 * Thrown when an arithmetic error occurred
 *
 * @example Division by zero, number overflow
 */
#define GRAPH_EXCEPTION_INCONSISTENT_ARITHMETIC 6
/**
 * Thrown when an operation between several matrices is impossible because of their incompatible dimensions
 *
 * @example Incompatible dimensions during multiplication / addition of two matrices
 */
#define GRAPH_EXCEPTION_INCONSISTENT_DIMENSIONS 7
/**
 * Thrown when the program parameters provided by the user are invalid
 *
 * @example Not enough / too much parameters
 */
#define GRAPH_EXCEPTION_INVALID_PROGRAM_PARAMETERS 8

// ================= Deserialization error codes ================= //

/**
 * Thrown when a provided type for a GRAPH during deserialization is unsupported
 *
 * @important Only the double type will not throw this exception at the time
 */
#define GRAPH_EXCEPTION_DESERIALIZATION_UNSUPPORTED_TYPE 2
/**
 * Thrown when the deserialization detected a syntax error
 *
 * @example The file is incomplete, a line is wrong
 */
#define GRAPH_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT 3
/**
 * Thrown when the amount of vertices declared / detected is not valid during deserialization
 *
 * @example The file said that there were 3 vertices but the file also declared 4 vertices
 */
#define GRAPH_EXCEPTION_DESERIALIZATION_INCONSISTENT_VERTEX_AMOUNT 4
/**
 * Thrown when the amount of arcs declared / detected is not valid during deserialization
 *
 * @example The file said that there were 3 arcs but the file also declared 4 arcs
 */
#define GRAPH_EXCEPTION_DESERIALIZATION_INCONSISTENT_ARC_AMOUNT 5
/**
 * Thrown when an arc starts or ends by an unknown vertex
 */
#define GRAPH_EXCEPTION_DESERIALIZATION_UNKNOWN_VERTEX 6

#endif //GRAPHEDCPP_DEFINES_H
