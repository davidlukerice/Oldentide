// File:     Player.h
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any player in Oldentide.
//        :  Inherits from "Character" class.

#ifndef OLDENTIDE_PLAYER_H_
#define OLDENTIDE_PLAYER_H_

#include "Character.h"
#include <string>

class Player : public Character {
    
    protected:

    std::string account;
    std::string profession;
    int id;
    int session; 
    float weight;
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

    public:

    // Constructors.
    Player(std::string account, std::string profession, int id, int session, float weight, int axe,
           int dagger, int unarmed, int hammer, int polearm, int spear, int staff, int sword, 
           int archery, int crossbow, int sling, int thrown, int armor, int dualWeapon, int shield,
           int bardic, int conjuring, int druidic, int illusion, int necromancy, int sorcery, 
           int shamanic, int spellcraft, int summoning, int focus, int armorsmithing, 
           int tailoring, int fletching, int weaponsmithing, int alchemy, int lapidary, 
           int calligraphy, int enchanting, int herbalism, int hunting, int mining, int bargaining,
           int camping, int firstAid, int lore, int pickLocks, int scouting, int search, 
           int stealth, int traps, int aeolandis, int hieroform, int highGundis, int oldPraxic,
           int praxic, int runic, std::string name, std::string lastname, std::string race, 
           std::string gender, std::string face, std::string skin, std::string zone, int level, 
           int hp, int maxHp, int bp, int maxBp, int mp, int maxMp, int ep, int maxEp, int strength, 
           int constitution, int intelligence, int dexterity, float x, float y, float z, 
           float pitch, float yaw);

    //~Player();

    // Getter Functions.
    
    std::string getAccount();
    std::string getProfession();
    int getId();
    int getSession();
    float getWeight();
    int getAxe();
    int getDagger();
    int getUnarmed();
    int getHammer();
    int getPolearm();
    int getSpear();
    int getStaff();
    int getSword();
    int getArchery();
    int getCrossbow();
    int getSling();
    int getThrown();
    int getArmor();
    int getDualWeapon();
    int getShield();
    int getBardic();
    int getConjuring();
    int getDruidic();
    int getIllusion();
    int getNecromancy();
    int getSorcery();
    int getShamanic();
    int getSummoning();
    int getSpellcraft();
    int getFocus();
    int getArmorsmithing();
    int getTailoring();
    int getFletching();
    int getWeaponsmith();
    int getAlchemy();
    int getLapidary();
    int getCalligraphy();
    int getEnchanting();
    int getHerbalism();
    int getHunting();
    int getMining();
    int getBargaining();
    int getCamping();
    int getFirstAid();
    int getLore();
    int getPickLocks();
    int getScouting();
    int getSearch();
    int getStealth();
    int getTraps();
    int getAeolandis();
    int getHieroform();
    int getHighGundis();
    int getOldPraxic();
    int getPraxic();
    int getRunic();

    // Setter Functions.
    
    void setAccount(std::string account);
    void setProfession(std::string profession);
    void setId(int id);
    void setSession(int session);
    void setWeight(float weight);
    void setAxe(int axe);
    void setDagger(int dagger);
    void setUnarmed(int unarmed);
    void setHammer(int hammer);
    void setPolearm(int polearm);
    void setSpear(int spear);
    void setStaff(int staff);
    void setSword(int sword);
    void setArchery(int archery);
    void setCrossbow(int crossbow);
    void setSling(int sling);
    void setThrown(int thrown);
    void setArmor(int armor);
    void setDualWeapon(int dualWeapon);
    void setShield(int shield);
    void setBardic(int bardic);
    void setConjuring(int conjuring);
    void setDruidic(int druidic);
    void setIllusion(int illusion);
    void setNecromancy(int necromancy);
    void setSorcery(int sorcery);
    void setShamanic(int shamanic);
    void setSummoning(int summoning);
    void setSpellcraft(int spellcraft);
    void setFocus(int focus);
    void setArmorsmithing(int armorsmithing);
    void setTailoring(int tailoring);
    void setFletching(int fletching);
    void setWeaponsmith(int weaponsmithing);
    void setAlchemy(int alchemy);
    void setLapidary(int lapidary);
    void setCalligraphy(int calligraphy);
    void setEnchanting(int enchanting);
    void setHerbalism(int herbalism);
    void setHunting(int hunting);
    void setMining(int mining);
    void setBargaining(int bargaining);
    void setCamping(int camping);
    void setFirstAid(int firstAid);
    void setLore(int lore);
    void setPickLocks(int pickLocks);
    void setScouting(int scouting);
    void setSearch(int search);
    void setStealth(int stealth);
    void setTraps(int traps);
    void setAeolandis(int aeolandis);
    void setHieroform(int hieroform);
    void setHighGundis(int highGundis);
    void setOldPraxic(int oldPraxic);
    void setPraxic(int praxic);
    void setRunic(int runic);

    // Class Functions.
    
};

#endif //OLDENTIDE_PLAYER_H_
