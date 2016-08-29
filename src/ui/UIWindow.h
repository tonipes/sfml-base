//
// Created by Toni on 8/28/16.
//
#pragma once
#include "imgui.h"
#include "UIGroup.h"
#include "UIElement.h"
#include <string>

class UIWindow: public UIElement {
public:
    std::string name;
protected:
    UIWindow(std::string name): name(name) {}
    virtual void drawInside(){}
private:
    void beginDraw(){ ImGui::Begin(name.c_str()); }
    void endDraw(){ ImGui::End();}
};

class UIGroupWindow: public UIWindow {
public:
    UIGroupWindow(std::string name) : UIWindow(name){}
    std::list<UIGroup*> groups;
protected:
    void drawInside();
};

void UIGroupWindow::drawInside() {
    for(auto group : groups){
        group->draw();
    }
}