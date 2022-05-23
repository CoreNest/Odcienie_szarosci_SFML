#include "UserInterFace.h"
#include <misc/cpp/imgui_stdlib.h>
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

bool UserInterFace::RenderUi(Settings& setting, ExpandSeting& expandSeting )
{
    
    
    /// Menu
 
    ImGui::Begin("Menu");
    ImGui::Button("Save")&setting.saveSeting();
    ImGui::SameLine();
    ImGui::Checkbox("PreView", &setting.preView);
    if (setting.preView) {
        ImGui::SameLine();
        ImGui::Checkbox("Multi-window", &setting.multiWin);
    }
    
    ImGui::InputText("sciezka", &setting.sciezka);   
    ImGui::Combo("formats", &setting.rozszerzenie, Settings::items, 8);
    ImGui::SliderFloat("RedRatio", &setting.RedRatio, -2.0f, 2.0f, "ratio = %.3f");
    ImGui::SliderFloat("BlueRatio", &setting.BlueRatio, -2.0f, 2.0f, "ratio = %.3f");
    ImGui::SliderFloat("GreanRatio", &setting.GreanRatio, -2.0f, 2.0f, "ratio = %.3f");
    ImGui::Checkbox("Hue", &setting.hue);  
    ImGui::SameLine();
    ImGui::Checkbox("Expand", &setting.expand);
    ImGui::End();
   
     /// Hue Panel 
    
    if (setting.hue) {
        ImGui::Begin("Hue Panel", &setting.hue);
        ImGui::ColorEdit3("Bright side", setting.colBright);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        ImGui::ColorEdit3("Dark side", setting.colDark);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        ImGui::End();
    }
    if (setting.expand) {
        ImGui::Begin("Expand Panel", &setting.expand);        
        ImGui::ColorEdit3("Saved color", expandSeting.saveColor);        
        ImGui::SliderFloat("PowerOfDisapiring", &expandSeting.Ratio, 0.0f, 1.0f, "ratio = %.3f");
        
        ImGui::End();
    }
    return 1;

    /// Save panel
}