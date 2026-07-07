/**-----------------------------------------------------------------------*
 * Common error codes for client/server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#ifndef _MISC_ERROR_H
#define _MISC_ERROR_H

/**
 * Error codes
 */
typedef enum {
  OK = 0,
  ERR_INVALID_ARG,

  _ERR_COUNT,
} error_code;

/**
 * Array of error error messages corresponding to error codes
 */
extern const char* error_messages[_ERR_COUNT];

/**
 * Converts an integer error code to an error string
 *
 * @param code Error code
 *
 * @return Error string
 */
const char* errorCodeToStr(error_code code);

#endif // _MISC_ERROR_H
