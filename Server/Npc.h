// File:     Npc.h
// Created:  January 31, 2016
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any NPC in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_NPC_H_
#define OLDENTIDE_NPC_H_

#include "Character.h"
#include <string>

class Npc : public Character {
    
    protected:

    int id;

    public:

    // Constructors.
    Npc(int id, std::string name, std::string lastname, std::string race, std::string gender,
        std::string face, std::string skin, std::string zone, int level, int hp, int maxHp, 
        int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, int constitution, 
        int intelligence, int dexterity, float x, float y, float z, float pitch, float yaw);
    
    //~Npc();

    // Getter Functions.
    
    int getId();

    // Setter Functions.
    
    void setId(int id);
    
    // Class Functions.
    
};

#endif //OLDENTIDE_NPC_H_

