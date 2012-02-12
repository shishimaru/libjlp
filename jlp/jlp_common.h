#include <stdlib.h>

#define JLP_DEFAULT_BUFSIZE 5

typedef enum JLP_Bool {
    JLP_FALSE = 0,
    JLP_TRUE = 1
} JLP_Bool;

typedef enum JLP_Error {
    JLP_ERROR_NONE = 0,
    JLP_ERROR_PARAMETER,
    JLP_ERROR_MEMORY,
    JLP_ERROR_REQUEST,
    JLP_ERROR_SERVER
} JLP_Error;

#define JLP_Malloc(size) malloc(size)
#define JLP_Calloc(nmemb, size) calloc(nmemb, size)
#define JLP_Realloc(ptr, size) realloc(ptr, size)
#define JLP_Free(ptr) free(ptr)
