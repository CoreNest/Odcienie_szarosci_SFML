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

    if (ImGui::Button("Import image"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseImgLoc", "Choose File", ".png,.jpg,.jpeg,.bmp", setting.sciezka + '.' + setting.items[setting.rozszerzenie]);
    ImGui::SameLine();
    if (ImGui::Button("Export image"))
        ImGuiFileDialog::Instance()->OpenDialog("ChooseSaveLoc", "Choose File", ".png,.jpg,.jpeg,.bmp", std::string(setting.sciezka) + "_mono." + setting.items[setting.rozszerzenie]);

    if(ImGui::Button("Load Settings"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseSetLoc", "Choose File", ".txt", setting.setPath);
    }
    ImGui::SameLine();
    if (ImGui::Button("Save Settings"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("ChooseSetSaveLoc", "Choose File", ".txt", setting.setPath);
    }
    
    zmianaUstawien |= ImGui::SliderFloat("RedRatio", &setting.RedRatio, -2.0f, 2.0f, "ratio = %.3f");
    zmianaUstawien |= ImGui::SliderFloat("BlueRatio", &setting.BlueRatio, -2.0f, 2.0f, "ratio = %.3f");
    zmianaUstawien |= ImGui::SliderFloat("GreanRatio", &setting.GreanRatio, -2.0f, 2.0f, "ratio = %.3f");
    zmianaUstawien |= ImGui::Checkbox("Bichromic", &setting.hue);
    ImGui::SameLine();
    zmianaUstawien |= ImGui::Checkbox("Except", &setting.expand);
    ImGui::End();
   
     /// Hue Panel 
    
    if (setting.hue) {
        zmianaUstawien |= ImGui::Begin("Bichromic Panel", &setting.hue);
        zmianaUstawien |= ImGui::ColorEdit3("Bright side", setting.colBright);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        zmianaUstawien |= ImGui::ColorEdit3("Dark side", setting.colDark);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        ImGui::End();
    }
    if (setting.expand) {
        zmianaUstawien |= ImGui::Begin("Except Color Panel", &setting.expand);
        zmianaUstawien |= ImGui::ColorEdit3("Saved color", expandSeting.saveColor);
        zmianaUstawien |= ImGui::SliderFloat("PowerOfDisapiring", &expandSeting.Ratio, 0.0f, 1.0f, "ratio = %.3f");
        
        ImGui::End();
    }


    ////////

    if (ImGuiFileDialog::Instance()->Display("ChooseSaveLoc"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            ColorConverter::SaveConvImage(imgLoader::img, setting, expandSeting, ImGuiFileDialog::Instance()->GetFilePathName());
        }
        ImGuiFileDialog::Instance()->Close();
    }

    //bool zmiana = false;

    if (ImGuiFileDialog::Instance()->Display("ChooseImgLoc"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            imgLoader::load(ImGuiFileDialog::Instance()->GetFilePathName());
            zmianaUstawien = true;
        }
        ImGuiFileDialog::Instance()->Close();
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseSetSaveLoc"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            setting.setPath = ImGuiFileDialog::Instance()->GetFilePathName();
            setting.saveSeting();
        }
        ImGuiFileDialog::Instance()->Close();
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseSetLoc"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            setting.setPath = ImGuiFileDialog::Instance()->GetFilePathName();
            setting.load(expandSeting);
            zmianaUstawien = true;
        }
        ImGuiFileDialog::Instance()->Close();
    }


    return zmianaUstawien;

    /// Save panel
}