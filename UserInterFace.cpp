#include "UserInterFace.h"

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
void UserInterFace::RenderUi()
{
    

    ImGui::Begin("Menu");
    ImGui::Button("Save");
    ImGui::SliderFloat("RedRatio", &setting.RedRatio, -2.0f, 2.0f, "ratio = %.3f");
    ImGui::SliderFloat("BlueRatio", &setting.BlueRatio, -2.0f, 2.0f, "ratio = %.3f");
    ImGui::SliderFloat("GreanRatio", &setting.GreanRatio, -2.0f, 2.0f, "ratio = %.3f");
    ImGui::Checkbox("Hue", &setting.hue);
    ImGui::End();
    if (setting.hue) {
        ImGui::Begin("Hue", &setting.hue);
        static float col1[3] = { 1.0f, 0.0f, 0.2f };
        ImGui::ColorEdit3("Bright side", setting.colBright);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        ImGui::ColorEdit3("Dark side", setting.colDark);
        ImGui::SameLine(); HelpMarker("Chose the hoe for light part");
        ImGui::End();
    }
}