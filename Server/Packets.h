// Filename:    Packets.h
// Author:      Joseph DeVictoria
// Date:        Feb_14_2016
// Purpose:     UDP Packet Struct Definitions.

#ifndef PACKETS_H
#define PACKETS_H

// Enumerate list of packet types (One-hot encoded)
enum PTYPE{
    GENERIC,
    ACK,
    CONNECT,
    DISCONNECT,
    GETSALT,
    CREATEACCOUNT,
    LOGIN,
    LISTCHARACTERS,
    SELECTCHARACTER,
    DELETECHARACTER,
    CREATECHARACTER,
    INITIALIZEGAME,
    UPDATEPC,
    UPDATENPC,
    SENDPLAYERCOMMAND,
    SENDPLAYERACTION,
    SENDSERVERACTION,
    MESSAGE,
    GETLATESTMESSAGE,
};

struct PACKET_GENERIC {
    PTYPE packetType = GENERIC;
    int packetId;
    int sessionId;
    char dummy[2000];
};

struct PACKET_ACK {
    PTYPE packetType = ACK;
    int packetId;
    int sessionId;
};

struct PACKET_CONNECT {
    PTYPE packetType = CONNECT;
    int packetId;
    int sessionId;
};

struct PACKET_DISCONNECT {
    PTYPE packetType = DISCONNECT;
    int packetId;
    int sessionId;
};

struct PACKET_GETSALT {
    PTYPE packetType = GETSALT;
    int packetId;
    int sessionId;
    char account[30];
    // 512-bit key -> 64 bytes -> 2 chars per byte for hex -> 128 + 1 null = 129
    char saltStringHex[129];
};

struct PACKET_CREATEACCOUNT {
    PTYPE packetType = CREATEACCOUNT;
    int packetId;
    int sessionId;
    char account[30];
    // 512-bit key -> 64 bytes -> 2 chars per byte for hex -> 128 + 1 null = 129
    char saltStringHex[129];
    char keyStringHex[129];
};

struct PACKET_LOGIN {
    PTYPE packetType = LOGIN;
    int packetId;
    int sessionId;
    char account[30];
    // 512-bit key -> 64 bytes -> 2 chars per byte for hex -> 128 + 1 null = 129
    char keyStringHex[129];
};

struct PACKET_LISTCHARACTERS {
    PTYPE packetType = LISTCHARACTERS;
    int packetId;
    int sessionId;
    char character0[25];
    char character1[25];
    char character2[25];
    char character3[25];
    char character4[25];
    char character5[25];
    char character6[25];
    char character7[25];
    char character8[25];
    char character9[25];
};

struct PACKET_SELECTCHARACTER {
    PTYPE packetType = SELECTCHARACTER;
    int packetId;
    int sessionId;
    char character[25];
};

struct PACKET_DELETECHARACTER {
    PTYPE packetType = DELETECHARACTER;
    int packetId;
    int sessionId;
    char character[25];
};

struct PACKET_CREATECHARACTER {
    PTYPE packetType = CREATECHARACTER;
    int packetId;
    int sessionId;
    char firstName[25];
    char lastName[25];
    char race[25];
    char gender[25];
    char profession[25];
    int strength;
    int constitution;
    int intelligence;
    int dexterity;
    int axe;
    int dagger;
    int unarmed;
    int hammer;
    int polearm;
    int spear;
    int staff;
    int sword;
    int archery;
    int crossbow;
    int sling;
    int thrown;
    int armor;
    int dualWeapon;
    int shield;
    int bardic;
    int conjuring;
    int druidic;
    int illusion;
    int necromancy;
    int sorcery;
    int shamanic;
    int spellcraft;
    int summoning;
    int focus;
    int armorsmithing;
    int tailoring;
    int fletching;
    int weaponsmithing;
    int alchemy;
    int lapidary;
    int calligraphy;
    int enchanting;
    int herbalism;
    int hunting;
    int mining;
    int bargaining;
    int camping;
    int firstAid;
    int lore;
    int pickLocks;
    int scouting;
    int search;
    int stealth;
    int traps;
    int aeolandis;
    int hieroform;
    int highGundis;
    int oldPraxic;
    int praxic;
    int runic;
};

struct PACKET_INITIALIZEGAME {
    PTYPE packetType = INITIALIZEGAME;
    int packetId;
    int sessionId;
};

struct PACKET_UPDATEPC {
    PTYPE packetType = UPDATEPC;
    int packetId;
    int sessionId;
    char firstName[25];
    char lastName[25];
    char race[25];
    char gender[25];
    char profession[25];
    int level;
    int hp;
    int bp;
    int mp;
    int ep;
    int x;
    int y;
    int z;
    float direction;
};

struct PACKET_UPDATENPC {
    PTYPE packetType = UPDATENPC;
    int packetId;
    int sessionId;
};

struct PACKET_SENDPLAYERCOMMAND {
    PTYPE packetType = SENDPLAYERCOMMAND;
    int packetId;
    int sessionId;
    char command[500];
};

struct PACKET_SENDPLAYERACTION {
    PTYPE packetType = SENDPLAYERACTION;
    int packetId;
    int sessionId;
};

struct PACKET_SENDSERVERACTION {
    PTYPE packetType = SENDSERVERACTION;
    int packetId;
    int sessionId;
};

// TODO: Make a send message packet?
// This packet will be used for both sending and receiving messages
// If messageNumber is empty, it is a message being sent from the client
// If messageNumber is not empty, it is a message lookup
struct PACKET_MESSAGE {
    PTYPE packetType = MESSAGE;
    int packetId;
    int sessionId;
    // The contents of the chat
    char message[500];
    // The message number assigned to this chat
    long long int globalMessageNumber;
    // The name of the account associated with the message
    char accountName[30];
};

struct PACKET_GETLATESTMESSAGE {
    PTYPE packetType = GETLATESTMESSAGE;
    int packetId;
    int sessionId;
    // The message number of the most recent message on the server
    long long int globalMessageNumber;
};

#endif //PACKETS_H
