#include "botmanager.h"

std::vector<Bot>& BotManager::getBotList() 
{
    return m_botList; 
}

void BotManager::readBotData(HANDLE procID, Bot& bot, int botAddr)
{
    // temp variables
    int team = 0; 
    int health = 0; 
    char name[32]{};
    Vector3 headPos{};
    Vector3 feetPos{}; 

    ReadProcessMemory(procID, LPCVOID(botAddr + TEAM), &team, sizeof(team), nullptr); 
    ReadProcessMemory(procID, LPCVOID(botAddr + HEALTH), &health, sizeof(health), nullptr); 
    ReadProcessMemory(procID, LPCVOID(botAddr + NAME), name, sizeof(name), nullptr);
    ReadProcessMemory(procID, LPCVOID(botAddr + HEAD), &headPos, sizeof(headPos), nullptr); 

    bot.setTeam(team);
    bot.setHealth(health); 
    bot.setName(name); 
    bot.setHeadPos(headPos);
}

void BotManager::loadBotData(HANDLE procID)
{
    // temp variables
    int botAmount = 0; 
    int botBaseAddress = 0;
    int botAddress = 0; // singular bot

    ReadProcessMemory(procID, LPCVOID(BOTAMOUNT), &botAmount, sizeof(botAmount), nullptr); 
    ReadProcessMemory(procID, LPCVOID(BOTBASEADDRESS), &botBaseAddress, sizeof(botBaseAddress), nullptr); 
    
    m_botList.clear();
    m_botList.resize(botAmount);  

    for (int i = 0; i < botAmount; ++i)
    {
        ReadProcessMemory(procID, LPCVOID(botBaseAddress + 0x4 * i), &botAddress, sizeof(botAddress), nullptr);

        if (botAddress != 0)
            readBotData(procID, m_botList[i], botAddress);
    }
}
