#include "UserInterFace.h"
#include <misc/cpp/imgui_stdlib.h>

#include "imgLoader.h"
#include "ColorConverter.h"


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
    
    bool zmianaUstawien=0;
    /// Menu
 
    ImGui::Begin("Menu");
    
    zmianaUstawien |= ImGui::Checkbox("PreView", &setting.preView);
    /*if (setting.preView) {
        ImGui::SameLine();
        ImGui::Checkbox("Multi-window", &setting.multiWin);
    }*/
    
    ImGui::InputText("sciezka", &setting.sciezka);   
    ImGui::Combo("formats", &setting.rozszerzenie, Settings::items, 8);
    //zmianaUstawien |= ImGui::Button("Save");
    zmianaUstawien |= ImGui::Button("Import image")&& imgLoader::load(setting.getSciezka());
    ImGui::SameLine();
    ImGui::Button("Save")& setting.saveSeting() && ColorConverter::SaveConvImage(imgLoader::img, setting, expandSeting);
    zmianaUstawien |= ImGui::SliderFloat("RedRatio", &setting.RedRatio, -2.0f, 2.0f, "ratio = %.3f");
    zmianaUstawien |= ImGui::SliderFloat("BlueRatio", &setting.BlueRatio, -2.0f, 2.0f, "ratio = %.3f");
    zmianaUstawien |= ImGui::SliderFloat("GreanRatio", &setting.GreanRatio, -2.0f, 2.0f, "ratio = %.3f");
    zmianaUstawien |= ImGui::Checkbox("Hue", &setting.hue);
    ImGui::SameLine();
    zmianaUstawien |= ImGui::Checkbox("Expand", &setting.expand);
    ImGui::End();
   
     /// Hue Panel 
    
    if (setting.hue) {
        zmianaUstawien |= ImGui::Begin("Hue Panel", &setting.hue);
        zmianaUstawien |= ImGui::ColorEdit3("Bright side", setting.colBright);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        zmianaUstawien |= ImGui::ColorEdit3("Dark side", setting.colDark);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        ImGui::End();
    }
    if (setting.expand) {
        zmianaUstawien |= ImGui::Begin("Expand Panel", &setting.expand);
        zmianaUstawien |= ImGui::ColorEdit3("Saved color", expandSeting.saveColor);
        zmianaUstawien |= ImGui::SliderFloat("PowerOfDisapiring", &expandSeting.Ratio, 0.0f, 1.0f, "ratio = %.3f");
        
        ImGui::End();
    }
    return zmianaUstawien;

    /// Save panel
}