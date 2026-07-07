/**-----------------------------------------------------------------------*
 * Miscellaneous common utilities for client/server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <misc/error.h>
#include <misc/misc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

error_code evalArgsContext(char** argv, const struct programArgument* args) {
  for (int arg_idx = 1; argv[arg_idx] != NULL; arg_idx++) { // Start at i = 1 because we don't care about path
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

    if (!match) return ERR_INVALID_ARG; // Return error if no match

    int offset;
    int result = match_arg->func(argv + arg_idx + 1, &offset); // Execute associated function and pass all args after arg_name

    if (result != OK) return result; // Return if error
    arg_idx += offset;
  }

  return OK;
}
