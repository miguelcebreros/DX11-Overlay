#pragma once

#include <array>
#include "vectors.h"
#include <cstring>

class Bot
{
    int m_team = 0; 
    int m_health = 0; 

    std::array<char, 32> m_name{}; 

    Vector3 m_headPos{}; 
    Vector3 m_feetPos{}; 

public: 

    int getTeam() const noexcept; 
    int getHealth() const noexcept; 

    const char* getName() const noexcept; 
    
    const Vector3& getHeadPos() const noexcept; 
    const Vector3& getFeetPos() const noexcept; 

    void setTeam(int team) noexcept; 
    void setHealth(int healt) noexcept; 
    void setName(const char* name) noexcept; 

    void setHeadPos(const Vector3& pos) noexcept; 
    void setFeetPos(const Vector3& pos) noexcept; 
};