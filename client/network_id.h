#ifndef NETWORK_ID_H
#define NETWORK_ID_H

/*
 * Packages ID System:
 * 
 * Auth ID range: [ 1; 999 ]
 * System ID range: [ 1000; 2999 ]
 * Lobby ID range: [ 3000; 4999 ]
 * Room ID range: [ 5000; 9999 ]
 * Profile ID range: [ 10000; 10999 ]
*/

// AUTH
#define GET_AUTH_FORM_ID 10

// SYSTEM
#define C01_ID 1000
#define LOGIN_ID 1001
#define GET_ACCOUNT_DATA_ID 1100
#define GET_AVATAR_DATA_ID 1200

// LOBBY
#define GET_INIT_ROOMS_ID 3100
#define CREATE_ROOM_ID 3500

// ROOM
#define GET_INIT_ROOM_MESSAGES_ID 5100

// PROFILE

#endif // NETWORK_ID_H
