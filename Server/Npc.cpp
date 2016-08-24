// File:     Npc.cpp
// Created:  January 31, 2016
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any NPC in Oldentide.
//        :  Inherits from "Character" class.

#include "Npc.h"

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Npc::Npc(int id, string name, string lastname, string race, string gender, string face, string skin,
         string zone, int level, int hp, int maxHp, int bp, int maxBp, int mp, int maxMp, int ep, 
         int maxEp, int strength, int constitution, int intelligence, int dexterity, float x, 
         float y, float z, float pitch, float yaw) 
    :Character(name, lastname, race, gender, face, skin, zone, level, hp, maxHp, bp, maxBp, mp, 
               maxMp, ep, maxEp, strength, constitution, intelligence, dexterity, x, y, z, pitch, 
               yaw){ 
    setId(id);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

int Npc::getId(){
    return id;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void Npc::setId(int id){
    this->id = id;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//

