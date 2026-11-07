#include "bot.h"    
#include <windows.h>
#include <vector>
#include "offsets.h"

class BotManager
{
    std::vector<Bot> m_botList{}; 

    public:

    std::vector<Bot>& getBotList(); 

    void readBotData(HANDLE procID, Bot& bot, int botAddr); 
    void loadBotData(HANDLE procID); 
};