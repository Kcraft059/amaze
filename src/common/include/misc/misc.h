/**-----------------------------------------------------------------------*
 * Miscellaneous common utilities for client / server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#ifndef _MISC_H
#define _MISC_H

#include <misc/log.h>

/// Argument Parser

/**
 * Executes code given following args
 *
 * @param argv Args following the given argument
 * @param argc Pointer to int var in which the function will store how much args it "consummed"
 *
 * @return Error code
 */
typedef err (*argumentFunc)(char** argv, int* argc);

/**
 * Program argument struct
 */
struct programArgument {
  char* name;        // Name of the arguement eg: "-c"
  char* description; // Argument description
  argumentFunc func; // Associated function
};

/**
 * Eval arguments in the context of the given argument table
 *
 * @param argv Arguments to parse
 * @param args Argument table for matching (NULL-Terminated)
 *
 * @return Error code
 */
void evalArgsContext(char** argv, int argc, const struct programArgument* args);

#endif // _MISC_H
