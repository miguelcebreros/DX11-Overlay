#pragma once
#include "botmanager.h"
#include <array>
#include "vectors.h"
#include "imgui.h"
#include "offsets.h"
#include "processmanager.h"
#include <windows.h>

class Overlay
{
    BotManager m_botManager{}; 
    std::array<float, 16> m_viewMatrix{}; 

    bool worldToScreen(const Vector3& position, Vector4& screen, const std::array<float, 16>& matrix, 
                       float screenWidth,float screenHeight);

    void drawText(float fontSize, const char* text, float x, float y, unsigned int color) const; 

    public:
    void initialize(); 
    void update(); 
    void render(); 
};