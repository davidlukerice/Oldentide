// File:     Character.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.

#ifndef OLDENTIDE_CHARACTER_H_
#define OLDENTIDE_CHARACTER_H_

#include <string>

class Character {

    protected:

    std::string name;
    std::string lastname;
    std::string race;
    std::string gender;
    std::string face;
    std::string skin;
    std::string zone;
    int level;
    int hp;
    int maxHp;
    int bp;
    int maxBp;
    int mp;
    int maxMp;
    int ep;
    int maxEp;
    int strength;
    int constitution;
    int intelligence;
    int dexterity;
    float x;
    float y;
    float z;
    float pitch;
    float yaw;

    public:

    // Constructors
    Character(std::string name, std::string lastname, std::string race, std::string gender, 
              std::string face, std::string skin, std::string zone, int level, int hp, int maxHp, 
              int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, 
              int constitution, int intelligence, int dexterity, float x, float y, float z, 
              float pitch, float yaw);

    //~Character();
    
    // Getter Functions
    std::string getName();
    std::string getLastname();
    std::string getRace();
    std::string getGender();
    std::string getFace();
    std::string getSkin();
    std::string getZone();
    int getLevel();
    int getHp();
    int getMaxHp();
    int getBp();
    int getMaxBp();
    int getMp();
    int getMaxMp();
    int getEp();
    int getMaxEp();
    int getStrength();
    int getConstitution();
    int getIntelligence();
    int getDexterity();
    float getX();
    float getY();
    float getZ();
    float getPitch();
    float getYaw();

    // Setter Functions
    void setName(std::string name);
    void setLastname(std::string lastname);
    void setRace(std::string race);
    void setGender(std::string gender);
    void setFace(std::string face);
    void setSkin(std::string skin);
    void setZone(std::string zone);
    void setLevel(int level);
    void setHp(int hp);
    void setMaxHp(int hp);
    void setBp(int bp);
    void setMaxBp(int bp);
    void setMp(int mp);
    void setMaxMp(int mp);
    void setEp(int ep);
    void setMaxEp(int ep);
    void setStrength(int strength);
    void setConstitution(int constitution);
    void setIntelligence(int intelligence);
    void setDexterity(int dexterity);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setPitch(float pitch);
    void setYaw(float yaw);

    // Class Functions

};

#endif //OLDENTIDE_CHARACTER_H_

