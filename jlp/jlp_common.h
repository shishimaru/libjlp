#ifndef JLP_COMMON_H
#define JLP_COMMON_H

#include <stdlib.h>

/** Default buffer size. */
#define JLP_DEFAULT_BUFSIZE 256
/**
 * Type of boolean.
 */
typedef enum JLP_Bool {
    /** false */
    JLP_FALSE = 0,
    /** true */
    JLP_TRUE = 1
} JLP_Bool;
/**
 * Type of error codes.
 */
typedef enum JLP_Error {
    /** no error */
    JLP_ERROR_NONE = 0,
    /** parameter error */
    JLP_ERROR_PARAMETER,
    /** memory error */
    JLP_ERROR_MEMORY,
    /** request error */
    JLP_ERROR_REQUEST,
    /** server error */
    JLP_ERROR_SERVER
} JLP_Error;

#define JLP_Malloc(size) malloc(size)
#define JLP_Calloc(nmemb, size) calloc(nmemb, size)
#define JLP_Realloc(ptr, size) realloc(ptr, size)
#define JLP_Free(ptr) free(ptr)

#endif /* JLP_COMMON_H */
