#ifndef TYPES_VARIABLES_H
#define TYPES_VARIABLES_H

typedef signed char int8;
typedef signed short int16;
#if defined(__LP64__) && __linux__
typedef signed int int32;
typedef signed long int64;
#else
typedef signed long int32;
typedef signed long long int64;
#endif

typedef unsigned char uint8;
typedef unsigned short uint16;
#if defined(__LP64__) && __linux__
typedef unsigned int uint32;
typedef unsigned long uint64;
#else
typedef unsigned long uint32;
typedef unsigned long long uint64;
#endif

#endif // TYPES_VARIABLES_H
