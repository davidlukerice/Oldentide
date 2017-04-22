// Filename:    Packets.h
// Author:      Joseph DeVictoria
// Date:        Feb_14_2016
// Purpose:     UDP Packet Struct Definitions.

#ifndef PACKETS_H
#define PACKETS_H

#include <msgpack.hpp>

// Enumerate list of packet types (One-hot encoded)
enum PTYPE{
    // Reserve 0 for null/uninitialized
    GENERIC = 1,
    ACK = 2,
    CONNECT = 3,
    DISCONNECT = 4,
    GETSALT = 5,
    CREATEACCOUNT = 6,
    LOGIN = 7,
    LISTCHARACTERS = 8,
    SELECTCHARACTER = 9,
    DELETECHARACTER = 10,
    CREATECHARACTER = 11,
    INITIALIZEGAME = 12,
    UPDATEPC = 13,
    UPDATENPC = 14,
    SENDPLAYERCOMMAND = 15,
    SENDSERVERCOMMAND = 16,
    SENDPLAYERACTION = 17,
    SENDSERVERACTION = 18,
    UNITY = 19
};


// Use this to send enums over messagepack - currently not needed
// MSGPACK_ADD_ENUM(PTYPE);

// Define packet maximums
// Generally, to avoid packet fragmentation, it is suggested to keep it to around 512 for maximum leniency,
// though they say you can go up to about 1400 for general use.
// See http://stackoverflow.com/questions/2862071/how-large-should-my-recv-buffer-be-when-calling-recv-in-the-socket-library
// See http://stackoverflow.com/questions/1098897/what-is-the-largest-safe-udp-packet-size-on-the-internet
#define PACKET_MAX_SIZE 512
#define PACKET_HEADER_SIZE 3
const uint16_t MSGPCK_MAX_PAYLOAD_SIZE = PACKET_MAX_SIZE - PACKET_HEADER_SIZE;


class TestData {
    public:
        std::string value;
        int i;
        MSGPACK_DEFINE(value, i); // write the member variables that you want to pack
    // private:
    //     PTYPE packetType;
};





struct PACKET_GENERIC {
    PTYPE packetType = GENERIC;
    int packetId;
    int sessionId;
    char dummy[600];
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

struct PACKET_LISTCHARACTERS {
    PTYPE packetType = LISTCHARACTERS;
    int packetId;
    int sessionId;
    char character1[25];
    char character2[25];
    char character3[25];
    char character4[25];
    char character5[25];
    char character6[25];
    char character7[25];
    char character8[25];
    char character9[25];
    char character10[25];
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
    char guild[50];
    char race[25];
    char gender[25];
    char face[25];
    char skin[25];
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
    float x;
    float y;
    float z;
    float pitch;
    float yaw;
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

struct PACKET_SENDSERVERCOMMAND {
    PTYPE packetType = SENDSERVERCOMMAND;
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

struct PACKET_UNITY {
    PTYPE packetType = UNITY;
    int data1;
    int data2;
    int data3;
    int data4;
    int data5;
};



#endif //PACKETS_H
