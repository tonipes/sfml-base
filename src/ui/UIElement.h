//
// Created by Toni on 8/28/16.
//
#pragma once
#include "imgui.h"

class UIElement {
public:
    bool visible = true;
    void draw(){ if(visible){ beginDraw(); drawInside(); endDraw(); }}
protected:
    UIElement() {}
    virtual void drawInside(){}
private:
    virtual void beginDraw(){}
    virtual void endDraw(){}
};
