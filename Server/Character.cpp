// File:     Character.cpp
// Created:  April 19, 2015
// Author:   Joseph DeVictoria
// Purpose:  Child class representing any living object in Oldentide.

#include "Character.h"

using namespace std;

//------------------------------------------------------------------------------//
//----------                     Class Constructors                   ----------//
//------------------------------------------------------------------------------//

Character::Character(string name, string lastname, string race, string gender, string face, 
                     string skin, string zone, int level, int hp, int maxHp, int bp, int maxBp, 
                     int mp, int maxMp, int ep, int maxEp, int strength, int constitution, 
                     int intelligence, int dexterity, float x, float y, float z, float pitch, 
                     float yaw) {
    setName(name);
    setLastname(lastname);
    setRace(race);
    setGender(gender);
    setFace(face);
    setSkin(skin);
    setZone(zone);
    setLevel(level);
    setHp(hp);
    setMaxHp(maxHp);
    setBp(bp);
    setMaxBp(maxBp);
    setMp(mp);
    setMaxMp(maxMp);
    setEp(ep);
    setMaxEp(maxEp);
    setStrength(strength);
    setConstitution(constitution);
    setIntelligence(intelligence);
    setDexterity(dexterity);
    setX(x);
    setY(y);
    setZ(z);
    setPitch(pitch);
    setYaw(yaw);
}

//------------------------------------------------------------------------------//
//----------                      Getter Functions                    ----------//
//------------------------------------------------------------------------------//

string Character::getName(){
    return name;
}

string Character::getLastname(){
    return lastname;
}

string Character::getRace(){
    return race;
}

string Character::getGender(){
    return gender;
}

string Character::getFace(){
    return face;
}

string Character::getSkin(){
    return skin;
}

string Character::getZone(){
    return zone;
}

int Character::getLevel(){
    return level;
}

int Character::getHp(){
    return hp;
}

int Character::getMaxHp(){
    return maxHp;
}

int Character::getBp(){
    return bp;
}

int Character::getMaxBp(){
    return maxBp;
}

int Character::getMp(){
    return mp;
}

int Character::getMaxMp(){
    return maxMp;
}

int Character::getEp(){
    return ep;
}

int Character::getMaxEp(){
    return maxEp;
}

int Character::getStrength(){
    return strength;
}

int Character::getConstitution(){
    return constitution;
}

int Character::getIntelligence(){
    return intelligence;
}

int Character::getDexterity(){
    return dexterity;
}

float Character::getX(){
    return x;
}

float Character::getY(){
    return y;
}

float Character::getZ(){
    return z;
}

float Character::getPitch(){
    return pitch;
}

float Character::getYaw(){
    return yaw;
}

//------------------------------------------------------------------------------//
//----------                      Setter Functions                    ----------//
//------------------------------------------------------------------------------//

void Character::setName(string name){
    this->name = name;
}

void Character::setLastname(string lastname){
    this->lastname = lastname;
}
void Character::setRace(string race){
    this->race = race;
}

void Character::setGender(string gender){
    this->gender = gender;
}

void Character::setFace(string face){
    this->face = face;
}

void Character::setSkin(string skin){
    this->skin = skin;
}

void Character::setZone(string zone){
    this->zone = zone;
}

void Character::setLevel(int level){
    this->level = level;
}

void Character::setHp(int hp){
    this->hp = hp;
}

void Character::setMaxHp(int maxHp){
    this->maxHp = maxHp;
}

void Character::setBp(int bp){
    this->bp = bp;
}

void Character::setMaxBp(int maxBp){
    this->maxBp = maxBp;
}

void Character::setMp(int mp){
    this->mp = mp;
}

void Character::setMaxMp(int maxMp){
    this->maxMp = maxMp;
}

void Character::setEp(int ep){
    this->ep = ep;
}

void Character::setMaxEp(int maxEp){
    this->maxEp = maxEp;
}

void Character::setStrength(int strength){
    this->strength = strength;
}

void Character::setConstitution(int constitution){
    this->constitution = constitution;
}

void Character::setIntelligence(int intelligence){
    this->intelligence = intelligence;
}

void Character::setDexterity(int dexterity){
    this->dexterity = dexterity;
}

void Character::setX(float x){
    this->x = x;
}

void Character::setY(float y){
    this->y = y;
}

void Character::setZ(float z){
    this->z = z;
}

void Character::setPitch(float pitch){
    this->pitch = pitch;
}

void Character::setYaw(float yaw){
    this->yaw = yaw;
}

//------------------------------------------------------------------------------//
//----------                      Class Functions                     ----------//
//------------------------------------------------------------------------------//

