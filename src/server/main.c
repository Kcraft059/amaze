/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <error.h>
#include <misc.h>
#include <stdio.h>

const programArgument args[] = {
    {.name = NULL, .description = NULL, .func = NULL}, // Signify end of array
};

int main(int argc, char** argv) {
  evalArgsContext(argv, args);
}
