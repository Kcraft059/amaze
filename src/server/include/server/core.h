/**-----------------------------------------------------------------------*
 * Amaze mini-game server
 *
 * Copyright (C) 2026 @kcraft059 - GPL v3
 *-----------------------------------------------------------------------**/

#ifndef _SERVER_CORE_H
#define _SERVER_CORE_H

int initServerSocket(int port);
void /* queue object */ initSocketMUX();
void handleConnectionRequests(/* queue object */);

#endif // _SERVER_CORE_H
