#pragma once
#include "Setting.h"
#include <imgui.h>
#include <ImGuiFileDialog.h>
#include "imgui-SFML.h"

class UserInterFace
{
public:
	static bool RenderUi(Settings &setting= setting, ExpandSeting &expandSeting = expandSeting);
};

