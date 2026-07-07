/**-----------------------------------------------------------------------*
 * Miscellaneous common utilities for client/server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <misc/misc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>

void evalArgsContext(char** argv, int argc, const struct programArgument* args) {
  for (int arg_idx = 1; arg_idx < argc; arg_idx++) { // Start at i = 1 because we don't care about path
    const struct programArgument* match_arg;
    char* name_arg = argv[arg_idx];
    bool match = false;

    for (int match_idx = 0; args[match_idx].name != NULL; match_idx++) { // Search for name match in arguements array
      match_arg = &args[match_idx];

      if (strcmp(name_arg, match_arg->name) == 0) { // If name of args matches with an available arg
        match = true;
        break;
      }
    }

    if (!match) panicErrorf(EINVAL, "Evaluating arg \"%s\"", name_arg); // Return error if no match

    int offset = argc - arg_idx - 1;
    err result;

    result = match_arg->func(argv + arg_idx + 1, &offset);                 // Execute associated function and pass all args after arg_name
    if (result != OK) panicErrorf(result, "Parsing arg \"%s\"", name_arg); // Return if error

    arg_idx += offset;
  }
}
