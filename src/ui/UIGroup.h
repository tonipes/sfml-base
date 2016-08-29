#pragma once
#include "imgui.h"
#include "UIElement.h"

class UIGroup: public UIElement {
public:
    UIGroup(){}
};

class UIButtonGroup: public UIGroup {
protected:
    void drawInside();
};

void UIButtonGroup::drawInside() {
    ImGui::Button("First");
    ImGui::Button("Second");
}