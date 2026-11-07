#include "bot.h"    

int Bot::getTeam() const noexcept
{
    return m_team; 
} 

int Bot::getHealth() const noexcept
{
    return m_health; 
}

const char* Bot::getName() const noexcept 
{
    return m_name.data();  
}

const Vector3& Bot::getHeadPos() const noexcept
{
    return m_headPos;
} 

const Vector3& Bot::getFeetPos() const noexcept
{
    return m_feetPos; 
} 

void Bot::setTeam(int team) noexcept
{
    m_team = team; 
}

void Bot::setHealth(int health) noexcept
{
    m_health = health; 
}

void Bot::setName(const char* name) noexcept
{
    // clear the array and create an empty string
    if (name == nullptr) 
    {
        m_name.fill('\0');
        return;
    }

    // copy name from source and reserve a byte for the null terminator 
    std::strncpy(m_name.data(), name, m_name.size() - 1); 
    m_name.back() = '\0'; 
}

void Bot::setHeadPos(const Vector3& pos) noexcept
{
    m_headPos = pos; 
} 

void Bot::setFeetPos(const Vector3& pos) noexcept
{
    m_feetPos = pos; 
}