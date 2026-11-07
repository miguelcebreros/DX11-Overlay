#include "overlay.h"
#include "imgui.h"
#include "processmanager.h"
#include <windows.h>
#include <winnt.h>

 bool Overlay::worldToScreen(const Vector3& position, Vector4& screen, const std::array<float, 16>& matrix, float screenWidth,float screenHeight)
 {
    screen.x = matrix[0] * position.x + matrix[4] * position.y + matrix[8] * position.z + matrix[12];
    screen.y = matrix[1] * position.x + matrix[5] * position.y + matrix[9] * position.z + matrix[13];
    screen.w = matrix[3] * position.x + matrix[7] * position.y + matrix[11] * position.z + matrix[15];     
    
    if (screen.w < 0.0f)
        return false;    

    screen.x /= screen.w;
    screen.y /= screen.w;    

    screen.x = (screen.x + 1) * (screenWidth / 2.0f);
    screen.y = (1 - screen.y) * (screenHeight / 2.0f);    
    
    return true;
}

void Overlay::drawText(float fontSize, const char* text, float x, float y, unsigned int color) const
{
    ImFont* font = ImGui::GetIO().Fonts->Fonts[0]; 
 
    if (!font)
        font = ImGui::GetFont();
    
    ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text);
 
    ImVec2 textPos; 
    textPos.x = x - textSize.x * 0.5f; 
    textPos.y = y - textSize.y - 5;     

    ImGui::GetForegroundDrawList()->AddText(font, fontSize, textPos, color, text);
}

void Overlay::initialize()
{
    ProcessManager::InitializeGlobalHandle(L"ac_client.exe"); 
}

void Overlay::update()
{
    HANDLE procID = ProcessManager::GetGlobalProcessHandle(); 

    if (procID == nullptr)
        return; 

    m_botManager.loadBotData(procID); 
} 

void Overlay::render() 
{
    HANDLE procID = ProcessManager::GetGlobalProcessHandle();
    
    if (procID == nullptr)
    	return; 

    Vector4 screen;    

    ReadProcessMemory(procID, LPCVOID(VIEWMATRIX), &m_viewMatrix, sizeof(m_viewMatrix), nullptr);    

    for (const Bot& bot : m_botManager.getBotList())
    {
    	if (bot.getHealth() <= 0)
        	continue;
    
        if (worldToScreen(bot.getHeadPos(), screen, m_viewMatrix, ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y))
        {
			drawText(14.0f, bot.getName(), screen.x, screen.y, IM_COL32(255, 255, 255, 255));
        }
    }
}