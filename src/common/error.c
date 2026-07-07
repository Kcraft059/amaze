/**-----------------------------------------------------------------------*
 * Common error codes for client/server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#include <misc/error.h>

const char* error_messages[_ERR_COUNT] = {
    [OK] = "Operation suceeded.",
    [ERR_INVALID_ARG] = "Invalid argument.",
};

const char* errorCodeToStr(error_code code) {
  if (code < 0 || code >= _ERR_COUNT) return "Unknown error."; // If error code isn't in enum, it's unknown
  return error_messages[code];                                // Return corresponding error code
};
