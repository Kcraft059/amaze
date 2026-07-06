/**-----------------------------------------------------------------------*
 * Miscellaneous common utilities for client / server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#ifndef _MISC_H
#define _MISC_H

#include <error.h>

/// Argument Parser

/**
 * Executes code given following args
 *
 * @param argv Args following the given argument
 * @param argc Pointer to int var in which the function will store how much args it "consummed"
 *
 * @return Error code
 */
typedef error_code (*argumentFunc)(char** argv, int* argc);

/**
 * Program argument struct
 */
typedef struct {
  char* name;        // Name of the arguement eg: "-c"
  char* description; // Argument description
  argumentFunc func; // Associated function
} programArgument;

/**
 * Eval arguments in the context of the given argument table
 *
 * @param argv Arguments to parse
 * @param args Argument table for matching (NULL-Terminated)
 *
 * @return Error code
 */
error_code evalArgsContext(char** argv, const programArgument* args);

#endif // _MISC_H
