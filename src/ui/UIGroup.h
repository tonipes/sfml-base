#pragma once
#include "imgui.h"
#include "UIElement.h"


class UIGroup: public UIElement {
public:
    UIGroup(){}
};

class UILambdaGroup: public UIGroup {
private:
    std::function<void(void)>& drawFunc;
public:
    UILambdaGroup(std::function<void(void)>& drawFunc_): UIGroup(), drawFunc(drawFunc_){};
protected:
    void drawInside(){drawFunc();};
};